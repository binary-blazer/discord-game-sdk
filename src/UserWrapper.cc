#include "./UserWrapper.h"

static bool *throwaway;

Napi::Object UserWrapper::Create(Napi::Env env, discord::Core &core) {
  Napi::Function func = DefineClass(
      env, "DiscordUserManager",
      {InstanceMethod<&UserWrapper::GetCurrentUser>("getCurrentUser"),
      InstanceMethod<&UserWrapper::GetCurrentUserPremiumType>("getCurrentUserPremiumType"),
      InstanceMethod<&UserWrapper::GetUser>("getUser"),
      InstanceMethod<&UserWrapper::CurrentUserHasFlag>("currentUserHasFlag")},
      &core.UserManager());

  return func.New({});
};

UserWrapper::UserWrapper(const Napi::CallbackInfo &info)
    : Napi::ObjectWrap<UserWrapper>(info) {
  // Extract the discord::UserManager from the data passed by the Factory
  // (see UserWrapper::Create)
  manager = (discord::UserManager *)info.Data();

  // Track the initialization of the UserManager current user, to know whether
  // we need to wait or can return directly the current user data
  int cbId = manager->OnCurrentUserUpdate.Connect([cbId, this]() {
    initialized = true;
    // Remove event listener.
    manager->OnCurrentUserUpdate.Disconnect(cbId);
  });
};

Napi::Value UserWrapper::GetCurrentUser(const Napi::CallbackInfo &info) {
  auto &env = info.Env();
  Napi::Promise::Deferred promise(env);

  if (!initialized) {
    // The user wasn't updated yet, await an user update before resolving the
    // promise to avoid incorrect result
    int cbId =
        manager->OnCurrentUserUpdate.Connect([&env, &promise, &cbId, this]() {
          // Now that the user has been updated, we can get the user
          discord::User *user;
          HandleDeferredDiscordResult(
              env, promise, manager->GetCurrentUser(user),
              [&env, user]() { return UserToObject(env, *user); });

          // Remove the event listener to avoid re-resolving the promise
          manager->OnCurrentUserUpdate.Disconnect(cbId);
        });
  } else {
    discord::User *user;
    HandleDeferredDiscordResult(
        env, promise, manager->GetCurrentUser(user),
        [&env, user]() { return UserToObject(env, *user); });
  }

  return promise.Promise();
};

Napi::Value UserWrapper::GetUser(const Napi::CallbackInfo &info) {
  auto &env = info.Env();
  if (info.Length() == 0)
    throw Napi::TypeError::New(env, "getUser expected at least 1 parameter!");

  // Request the user with a promise resolver as callback
  Napi::Promise::Deferred promise(env);
  manager->GetUser(
      info[0].As<Napi::Number>(),
      [&env, &promise](discord::Result result, const discord::User &user) {
        HandleDeferredDiscordResult(env, promise, result, [&env, &user]() {
          return UserToObject(env, user);
        });
      });

  return promise.Promise();
};

Napi::Value
UserWrapper::GetCurrentUserPremiumType(const Napi::CallbackInfo &info) {
  auto &env = info.Env();

  // Request the premium type
  discord::PremiumType *premiumType = false;
  const auto result = manager->GetCurrentUserPremiumType(premiumType);
  CheckDiscordResult(env, result);

  // Convert to a javascript string
  return Napi::String::New(
      env,
      *premiumType == discord::PremiumType::None
          ? "None"
          : *premiumType == discord::PremiumType::Tier1 ? "Tier1" : "Tier2");
};

Napi::Value UserWrapper::CurrentUserHasFlag(const Napi::CallbackInfo &info) {
  auto &env = info.Env();
  if (info.Length() == 0)
    throw Napi::TypeError::New(env, "getUser expected at least 1 parameter!");

  // Get the flag value
  bool *hasFlag = false;
  CheckDiscordResult(env, manager->CurrentUserHasFlag(
                              discord::UserFlag::HypeSquadEvents, hasFlag));

  return Napi::Boolean::New(env, *hasFlag);
};
