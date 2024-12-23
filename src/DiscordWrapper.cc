#include "DiscordWrapper.h"
#include "DiscordTools.h"
#include "UserWrapper.h"
#include <iostream>

Napi::Object DiscordWrapper::Bind(Napi::Env env, Napi::Object exports) {
  Napi::Function func = DefineClass(
      env, "DiscordNative",
      {InstanceMethod<&DiscordWrapper::RegisterCallback>("on"),
       InstanceMethod<&DiscordWrapper::GetStatus>("getStatus"),
       InstanceMethod<&DiscordWrapper::UpdateActivity>("updateActivity"),
       InstanceMethod<&DiscordWrapper::RunCallbacks>("runCallbacks"),
       InstanceMethod<&DiscordWrapper::GetUserManager>("getUserManager")});
  Napi::FunctionReference *constructor = new Napi::FunctionReference();

  // Create a persistent reference to the class constructor. This will allow
  // a function called on a class prototype and a function
  // called on instance of a class to be distinguished from each other.
  *constructor = Napi::Persistent(func);
  exports.Set("DiscordNative", func);

  // Store the constructor as the add-on instance data. This will allow this
  // add-on to support multiple instances of itself running on multiple worker
  // threads, as well as multiple instances of itself running in different
  // contexts on the same thread.
  //
  // By default, the value set on the environment here will be destroyed when
  // the add-on is unloaded using the `delete` operator, but it is also
  // possible to supply a custom deleter.
  env.SetInstanceData<Napi::FunctionReference>(constructor);

  return exports;
};

DiscordWrapper::DiscordWrapper(const Napi::CallbackInfo &info)
    : Napi::ObjectWrap<DiscordWrapper>(info) {
  auto env = info.Env();

  // Get and verify arguments
  if (info.Length() == 0)
    throw Napi::TypeError::New(
        env, "Expected at least 1 argument in 'Discord.constructor'");

  Napi::Number clientId = info[0].As<Napi::Number>();
  EDiscordCreateFlags flags = DiscordCreateFlags_NoRequireDiscord;
  if (info.Length() > 1 && !info[1].IsUndefined()) {
    if (!info[1].IsObject())
      throw Napi::TypeError::New(
          env, "Expected an object or undefined as 2nd argument");
    auto optional = info[1].As<Napi::Object>();

    if (optional.HasOwnProperty("requireDiscord") &&
        !optional.Get("requireDiscord").IsUndefined()) {
      auto requireDiscord = optional.Get("requireDiscord");
      if (!requireDiscord.IsBoolean())
        throw Napi::TypeError::New(env,
                                   "Expected requireDiscord to be boolean or "
                                   "undefined in 2nd argument");
      flags = requireDiscord.As<Napi::Boolean>()
                  ? DiscordCreateFlags_Default
                  : DiscordCreateFlags_NoRequireDiscord;
    }
  }

  // Initialize the Discord Game SDK Core
  status = (int)discord::Core::Create(clientId, flags, &core);
}

// GENERAL

const std::map<std::string, DiscordWrapper::EventTypes>
    DiscordWrapper::eventsMap = {{"joinRequest", OnActivityJoinRequest},
                                 {"join", OnActivityJoin},
                                 {"spectate", OnActivitySpectate},
                                 {"invite", OnActivityInvite},
                                 {"userUpdate", OnCurrentUserUpdate}};

Napi::Value DiscordWrapper::RegisterCallback(const Napi::CallbackInfo &info) {
  auto env = info.Env();

  // Drop into lower level API to be able to access callback from lambda
  // See https://github.com/nodejs/node-addon-api/issues/772
  napi_ref cb_ref;
  napi_create_reference(env, info[1].As<Napi::Function>(), 1, &cb_ref);

  switch (eventsMap.at(info[0].As<Napi::String>())) {

  case OnActivityJoinRequest:
    return Napi::Number::New(
        env, core->ActivityManager().OnActivityJoinRequest.Connect(
                 [&env, &cb_ref](discord::User user) {
                   Napi::FunctionReference cb(env, cb_ref);
                   cb.Call({UserToObject(env, user)});
                 }));

  case OnActivityJoin:
    return Napi::Number::New(
        env, core->ActivityManager().OnActivityJoin.Connect(
                 [&env, &cb_ref](std::string joinSecret) {
                   Napi::FunctionReference cb(env, cb_ref);
                   cb.MakeCallback(env.Global(),
                                   {Napi::String::New(env, joinSecret)});
                 }));

  case OnActivitySpectate:
    return Napi::Number::New(
        env, core->ActivityManager().OnActivitySpectate.Connect(
                 [&env, &cb_ref](std::string spectateSecret) {
                   Napi::FunctionReference cb(env, cb_ref);
                   cb.Call({Napi::String::New(env, spectateSecret)});
                 }));

  case OnActivityInvite:
    return Napi::Number::New(
        env,
        core->ActivityManager().OnActivityInvite.Connect(
            [&env, &cb_ref](discord::ActivityActionType action,
                            discord::User user, discord::Activity activity) {
              Napi::FunctionReference cb(env, cb_ref);
              cb.Call(
                  {Napi::String::New(env,
                                     action == discord::ActivityActionType::Join
                                         ? "join"
                                         : "spectate"),
                   UserToObject(env, user), ActivityToObject(env, activity)});
            }));

  case OnCurrentUserUpdate:
    return Napi::Number::New(
        env, core->UserManager().OnCurrentUserUpdate.Connect([&env, &cb_ref]() {
          Napi::FunctionReference cb(env, cb_ref);
          cb.Call({Napi::Boolean::New(env, true)});
        }));
  }

  return Napi::Number::New(env, -1);
};

Napi::Value DiscordWrapper::GetStatus(const Napi::CallbackInfo &info) {
  return Napi::Number::New(info.Env(), status);
};

// ACTIVITY

Napi::Value DiscordWrapper::UpdateActivity(const Napi::CallbackInfo &info) {
  auto env = info.Env();
  Napi::Promise::Deferred promise(env);
  discord::Activity activity =
      ObjectToActivity(env, info[0].As<Napi::Object>());

  core->ActivityManager().UpdateActivity(
      activity, [promise, env](discord::Result result) {
        if (result != discord::Result::Ok)
          promise.Reject(Napi::Number::New(env, (int)result));
        else
          promise.Resolve(Napi::Number::New(env, (int)result));
      });

  return promise.Promise();
};

// USER MANAGEMENT
Napi::Value DiscordWrapper::GetUserManager(const Napi::CallbackInfo &info) {
  if (usersManager == nullptr) {
    usersManager = &UserWrapper::Create(info.Env(), *core);
  }
  return *usersManager;
};

// INTERNALS
Napi::Value DiscordWrapper::RunCallbacks(const Napi::CallbackInfo &info) {
  status = (int)core->RunCallbacks();
  return Napi::Number::New(info.Env(), status);
};
