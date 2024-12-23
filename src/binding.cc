#include "napi.h"
#include "DiscordWrapper.h"

Napi::Object Init(Napi::Env env, Napi::Object exports)
{
  return DiscordWrapper::Bind(env, exports);
}

NODE_API_MODULE(NODE_GYP_MODULE_NAME, Init);
