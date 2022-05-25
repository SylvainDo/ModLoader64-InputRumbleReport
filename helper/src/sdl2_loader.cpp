#include <Windows.h>
#include <SDL.h>

extern "C" {

static HMODULE hModule;

using pfn_SDL_GetTicks_t = Uint32(__cdecl*)();

static pfn_SDL_GetTicks_t pfn_SDL_GetTicks;

#define loadSymbol(x) pfn_##x = reinterpret_cast<pfn_##x##_t>(GetProcAddress(hModule, #x))

void sdl2_loader_init() {
    hModule = LoadLibrary(L"SDL2.dll");

    loadSymbol(SDL_GetTicks);
}

void sdl2_loader_deinit() {
    FreeLibrary(hModule);
}

Uint32 SDL_GetTicks() { return pfn_SDL_GetTicks(); }

}
