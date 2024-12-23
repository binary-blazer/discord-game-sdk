#include "DiscordTools.h"

Napi::Object UserToObject(Napi::Env &env, const discord::User &user) {
  auto result = Napi::Object::New(env);
  result.Set("isBot", Napi::Boolean::New(env, user.GetBot()));
  result.Set("username", Napi::String::New(env, user.GetUsername()));
  result.Set("avatar", Napi::String::New(env, user.GetAvatar()));
  result.Set("discriminator", Napi::String::New(env, user.GetDiscriminator()));
  result.Set("id", Napi::Number::New(env, user.GetId()));
  return result;
};

Napi::Object ActivityToObject(Napi::Env &env,
                              const discord::Activity &activity) {
  auto result = Napi::Object::New(env);
  result.Set("appId", Napi::Number::New(env, activity.GetApplicationId()));
  result.Set("name", Napi::String::New(env, activity.GetName()));
  result.Set("state", Napi::String::New(env, activity.GetState()));
  result.Set("details", Napi::String::New(env, activity.GetDetails()));
  result.Set("instance", Napi::Boolean::New(env, activity.GetInstance()));

  auto assets = Napi::Object::New(env);
  assets.Set("largeImage",
             Napi::String::New(env, activity.GetAssets().GetLargeImage()));
  assets.Set("largeText",
             Napi::String::New(env, activity.GetAssets().GetLargeText()));
  assets.Set("smallImage",
             Napi::String::New(env, activity.GetAssets().GetSmallImage()));
  assets.Set("smallText",
             Napi::String::New(env, activity.GetAssets().GetSmallText()));
  result.Set("assets", assets);

  auto timestamps = Napi::Object::New(env);
  timestamps.Set("start",
                 Napi::Number::New(env, activity.GetTimestamps().GetStart()));
  timestamps.Set("end",
                 Napi::Number::New(env, activity.GetTimestamps().GetEnd()));
  result.Set("timestamps", timestamps);

  auto party = Napi::Object::New(env);
  party.Set("id", Napi::String::New(env, activity.GetParty().GetId()));

  auto partySize = Napi::Object::New(env);
  partySize.Set(
      "currentSize",
      Napi::Number::New(env, activity.GetParty().GetSize().GetCurrentSize()));
  partySize.Set(
      "maxSize",
      Napi::Number::New(env, activity.GetParty().GetSize().GetCurrentSize()));
  party.Set("size", partySize);

  result.Set("party", party);

  auto secrets = Napi::Object::New(env);
  secrets.Set("join", Napi::String::New(env, activity.GetSecrets().GetJoin()));
  secrets.Set("match",
              Napi::String::New(env, activity.GetSecrets().GetMatch()));
  secrets.Set("spectate",
              Napi::String::New(env, activity.GetSecrets().GetSpectate()));
  result.Set("secrets", secrets);

  return result;
};

discord::Activity ObjectToActivity(Napi::Env &env, const Napi::Object &object) {
  discord::Activity activity{};

  if (object.HasOwnProperty("details"))
    activity.SetDetails(
        object.Get("details").As<Napi::String>().Utf8Value().c_str());

  if (object.HasOwnProperty("state"))
    activity.SetState(
        object.Get("state").As<Napi::String>().Utf8Value().c_str());

  if (object.HasOwnProperty("instance"))
    activity.SetInstance(object.Get("instance").As<Napi::Boolean>());

  if (object.HasOwnProperty("assets")) {
    auto assets = object.Get("assets").As<Napi::Object>();

    if (assets.HasOwnProperty("largeImage"))
      activity.GetAssets().SetLargeImage(
          assets.Get("largeImage").As<Napi::String>().Utf8Value().c_str());

    if (assets.HasOwnProperty("largeText"))
      activity.GetAssets().SetLargeText(
          assets.Get("largeText").As<Napi::String>().Utf8Value().c_str());

    if (assets.HasOwnProperty("smallImage"))
      activity.GetAssets().SetSmallImage(
          assets.Get("smallImage").As<Napi::String>().Utf8Value().c_str());

    if (assets.HasOwnProperty("smallText"))
      activity.GetAssets().SetSmallText(
          assets.Get("smallText").As<Napi::String>().Utf8Value().c_str());
  }

  if (object.HasOwnProperty("timestamps")) {
    auto timestamps = object.Get("timestamps").As<Napi::Object>();

    if (timestamps.HasOwnProperty("start"))
      activity.GetTimestamps().SetStart(
          timestamps.Get("start").As<Napi::Number>());

    if (timestamps.HasOwnProperty("end"))
      activity.GetTimestamps().SetEnd(timestamps.Get("end").As<Napi::Number>());
  }

  if (object.HasOwnProperty("party")) {
    auto party = object.Get("party").As<Napi::Object>();

    if (party.HasOwnProperty("id"))
      activity.GetParty().SetId(
          party.Get("id").As<Napi::String>().Utf8Value().c_str());

    if (party.HasOwnProperty("size")) {
      auto partySize = party.Get("size").As<Napi::Object>();

      if (partySize.HasOwnProperty("currentSize"))
        activity.GetParty().GetSize().SetCurrentSize(
            partySize.Get("currentSize").As<Napi::Number>());

      if (partySize.HasOwnProperty("maxSize"))
        activity.GetParty().GetSize().SetMaxSize(
            partySize.Get("maxSize").As<Napi::Number>());
    }
  }

  if (object.HasOwnProperty("secrets")) {
    auto secrets = object.Get("secrets").As<Napi::Object>();

    if (secrets.HasOwnProperty("join"))
      activity.GetSecrets().SetJoin(
          secrets.Get("join").As<Napi::String>().Utf8Value().c_str());

    if (secrets.HasOwnProperty("match"))
      activity.GetSecrets().SetMatch(
          secrets.Get("match").As<Napi::String>().Utf8Value().c_str());

    if (secrets.HasOwnProperty("spectate"))
      activity.GetSecrets().SetSpectate(
          secrets.Get("spectate").As<Napi::String>().Utf8Value().c_str());
  }

  return activity;
};

void HandleDeferredDiscordResult(Napi::Env &env,
                                 Napi::Promise::Deferred &promise,
                                 const discord::Result &result,
                                 const std::function<napi_value()> &resolve) {
  if (result != discord::Result::Ok)
    promise.Reject(Napi::String::New(env, "Discord error! " +
                                              std::to_string((int)result)));
  else {
    promise.Resolve(resolve());
  }
};

void CheckDiscordResult(Napi::Env &env, const discord::Result &result) {
  if (result != discord::Result::Ok)
    throw Napi::Error::New(env,
                           "Discord error! " + std::to_string((int)result));
};
