#pragma once

#include "discord/user_manager.h"
#include "napi.h"

/**
 * Converts a discord::User to a JavaScript object.
 */
Napi::Object UserToObject(Napi::Env &env, const discord::User &user);

/**
 * Converts a JavaScript object to a discord::Activity.
 */
discord::Activity ObjectToActivity(Napi::Env &env, const Napi::Object &object);

/**
 * Converts a discord::Activity to a JavaScript object.
 */
Napi::Object ActivityToObject(Napi::Env &env,
                              const discord::Activity &activity);

/**
 * Resolves or rejects a promise depending on the discord result code.
 */
void HandleDeferredDiscordResult(Napi::Env &env,
                                 Napi::Promise::Deferred &promise,
                                 const discord::Result &result,
                                 const std::function<napi_value()> &resolve);

/**
 * Throws an exception if the discord result is not discord::Result::Ok.
 */
void CheckDiscordResult(Napi::Env &env, const discord::Result &result);
