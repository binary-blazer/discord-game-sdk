#pragma once

#include "discord/discord.h"
#include "napi.h"
#include <map>

/**
 * A wrapper for the Discord APIs that does the necessary convertions between C++ and JavaScript.
 */
class DiscordWrapper : public Napi::ObjectWrap<DiscordWrapper> {
public:
  /**
   * Binds the class to Node.
   */
  static Napi::Object Bind(Napi::Env env, Napi::Object exports);
  DiscordWrapper(const Napi::CallbackInfo &info);

private:
  enum EventTypes {
    OnActivityJoinRequest,
    OnActivityJoin,
    OnActivitySpectate,
    OnActivityInvite,
    OnCurrentUserUpdate
  };
  static const std::map<std::string, EventTypes> eventsMap;

  /**
   * The Discord SDK main object instance.
   */
  discord::Core *core{};

  /**
   * A reference to the current UserWrapper instance.
   */  
  Napi::Object *usersManager = nullptr;

  /**
   * The last status returned by RunCallbacks.
   */
  int status = -1;

  /**
   * Returns `status`.
   */
  Napi::Value GetStatus(const Napi::CallbackInfo &info);

  /**
   * Registers a callback.
   */
  Napi::Value RegisterCallback(const Napi::CallbackInfo &info);
  Napi::Value UpdateActivity(const Napi::CallbackInfo &info);

  /**
   * Returns the UserWrapper instance.
   */
  Napi::Value GetUserManager(const Napi::CallbackInfo &info);
  Napi::Value RunCallbacks(const Napi::CallbackInfo &info);
};
