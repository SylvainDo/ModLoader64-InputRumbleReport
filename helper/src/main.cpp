#include <napi.h>

#include <filesystem>
#include <memory>

#include <Windows.h>
#include <SDL.h>
#include <SFML/Audio.hpp>

extern "C" {
void sdl2_loader_init();
void sdl2_loader_deinit();
}

static HMODULE hModule;
using pfn_Report_IsRumbling_t = int(*)();
static pfn_Report_IsRumbling_t pfn_Report_IsRumbling;

static std::unique_ptr<sf::SoundBuffer> soundBuffer;
static std::unique_ptr<sf::Sound> sound;

Napi::Value initialize(const Napi::CallbackInfo& info) {
    sdl2_loader_init();

    const std::filesystem::path inputPluginDll = info[0].As<Napi::String>().Utf16Value();
    const std::filesystem::path soundFile = info[1].As<Napi::String>().Utf8Value();

    hModule = LoadLibrary(inputPluginDll.wstring().c_str());
    if (!hModule) return Napi::Number::New(info.Env(), -1);
    const FARPROC proc = GetProcAddress(hModule, "Report_IsRumbling");
    if (!proc) return Napi::Number::New(info.Env(), -2);
    pfn_Report_IsRumbling = reinterpret_cast<pfn_Report_IsRumbling_t>(proc);

    soundBuffer = std::make_unique<sf::SoundBuffer>();
    soundBuffer->loadFromFile(soundFile.string());
    sound = std::make_unique<sf::Sound>(*soundBuffer.get());

    return Napi::Number::New(info.Env(), 0);
}

Napi::Value deinitialize(const Napi::CallbackInfo& info) {
    FreeLibrary(hModule);
    sdl2_loader_deinit();

    return info.Env().Undefined();
}

Napi::Value isRumbling(const Napi::CallbackInfo& info) {
    return Napi::Boolean::New(info.Env(), pfn_Report_IsRumbling && pfn_Report_IsRumbling());
}

Napi::Value getTicks(const Napi::CallbackInfo& info) {
    return Napi::Number::New(info.Env(), SDL_GetTicks());
}

Napi::Value playSound(const Napi::CallbackInfo& info) {
    sound->stop();
    sound->play();

    return info.Env().Undefined();
}

Napi::Value getVolume(const Napi::CallbackInfo& info) {
    return Napi::Number::New(info.Env(), sound->getVolume());
}

Napi::Value setVolume(const Napi::CallbackInfo& info) {
    sound->setVolume(info[0].As<Napi::Number>().FloatValue());

    return info.Env().Undefined();
}

Napi::Object moduleEntryPoint(Napi::Env env, Napi::Object exports) {
    exports.Set("initialize", Napi::Function::New(env, initialize));
    exports.Set("deinitialize", Napi::Function::New(env, deinitialize));
    exports.Set("isRumbling", Napi::Function::New(env, isRumbling));
    exports.Set("getTicks", Napi::Function::New(env, getTicks));
    exports.Set("playSound", Napi::Function::New(env, playSound));
    exports.Set("getVolume", Napi::Function::New(env, getVolume));
    exports.Set("setVolume", Napi::Function::New(env, setVolume));

    return exports;
}

NODE_API_MODULE(helper_addon, moduleEntryPoint)
