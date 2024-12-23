#pragma once

#include "./DiscordTools.h"
#include "discord/discord.h"
#include "napi.h"

class UserWrapper : public Napi::ObjectWrap<UserWrapper> {
public:
  static Napi::Object Create(Napi::Env env, discord::Core &core);
  UserWrapper(const Napi::CallbackInfo &info);

private:
  discord::UserManager *manager;
  bool initialized = false;

  Napi::Value GetCurrentUser(const Napi::CallbackInfo &info);
  Napi::Value GetUser(const Napi::CallbackInfo &info);
  Napi::Value GetCurrentUserPremiumType(const Napi::CallbackInfo &info);
  Napi::Value CurrentUserHasFlag(const Napi::CallbackInfo &info);
};
