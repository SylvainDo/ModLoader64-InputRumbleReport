#include <Windows.h>
#include <SDL.h>

extern "C" {

static HMODULE hModule;

using pfn_SDL_NumJoysticks_t = int(__cdecl*)();
using pfn_SDL_JoystickOpen_t = SDL_Joystick*(__cdecl*)(int device_index);
using pfn_SDL_JoystickName_t = const char*(__cdecl*)(SDL_Joystick*);
using pfn_SDL_JoystickClose_t = void(__cdecl*)(SDL_Joystick*);
using pfn_SDL_GetError_t = const char*(__cdecl*)();
using pfn_SDL_GetWindowSize_t = void(__cdecl*)(SDL_Window* window, int* w, int* h);
using pfn_SDL_GetKeyboardFocus_t = SDL_Window*(__cdecl*)();
using pfn_SDL_GetKeyboardState_t = const Uint8*(__cdecl*)(int* numkeys);
using pfn_SDL_GetMouseState_t = Uint32(__cdecl*)(int* x, int* y);
using pfn_SDL_WarpMouseInWindow_t = void(__cdecl*)(SDL_Window* window, int x, int y);
using pfn_SDL_SetRelativeMouseMode_t = int(__cdecl*)(SDL_bool enabled);
using pfn_SDL_GetRelativeMouseMode_t = SDL_bool(__cdecl*)();
using pfn_SDL_ShowCursor_t = int(__cdecl*)(int toggle);
using pfn_SDL_JoystickGetAttached_t = SDL_bool(__cdecl*)(SDL_Joystick* joystick);
using pfn_SDL_JoystickUpdate_t = void(__cdecl*)();
using pfn_SDL_JoystickGetAxis_t = Sint16(__cdecl*)(SDL_Joystick* joystick, int axis);
using pfn_SDL_JoystickGetHat_t = Uint8(__cdecl*)(SDL_Joystick* joystick, int hat);
using pfn_SDL_JoystickGetButton_t = Uint8(__cdecl*)(SDL_Joystick* joystick, int button);
using pfn_SDL_PumpEvents_t = void(__cdecl*)();
using pfn_SDL_PeepEvents_t = int(__cdecl*)(SDL_Event* events, int numevents, SDL_eventaction action, Uint32 minType, Uint32 maxType);
using pfn_SDL_HapticOpenFromJoystick_t = SDL_Haptic*(__cdecl*)(SDL_Joystick* joystick);
using pfn_SDL_HapticClose_t = void(__cdecl*)(SDL_Haptic* haptic);
using pfn_SDL_HapticRumbleSupported_t = int(__cdecl*)(SDL_Haptic* haptic);
using pfn_SDL_HapticRumbleInit_t = int(__cdecl*)(SDL_Haptic* haptic);
using pfn_SDL_HapticRumblePlay_t = int(__cdecl*)(SDL_Haptic* haptic, float strength, Uint32 length);
using pfn_SDL_HapticRumbleStop_t = int(__cdecl*)(SDL_Haptic* haptic);
using pfn_SDL_GetTicks_t = Uint32(__cdecl*)();
using pfn_SDL_Delay_t = void(__cdecl*)(Uint32 ms);
using pfn_SDL_Init_t = int(__cdecl*)(Uint32 flags);
using pfn_SDL_InitSubSystem_t = int(__cdecl*)(Uint32 flags);
using pfn_SDL_QuitSubSystem_t = void(__cdecl*)(Uint32 flags);
using pfn_SDL_WasInit_t = Uint32(__cdecl*)(Uint32 flags);

static pfn_SDL_NumJoysticks_t pfn_SDL_NumJoysticks;
static pfn_SDL_JoystickOpen_t  pfn_SDL_JoystickOpen;
static pfn_SDL_JoystickName_t  pfn_SDL_JoystickName;
static pfn_SDL_JoystickClose_t pfn_SDL_JoystickClose;
static pfn_SDL_GetError_t  pfn_SDL_GetError;
static pfn_SDL_GetWindowSize_t pfn_SDL_GetWindowSize;
static pfn_SDL_GetKeyboardFocus_t pfn_SDL_GetKeyboardFocus;
static pfn_SDL_GetKeyboardState_t pfn_SDL_GetKeyboardState;
static pfn_SDL_GetMouseState_t pfn_SDL_GetMouseState;
static pfn_SDL_WarpMouseInWindow_t pfn_SDL_WarpMouseInWindow;
static pfn_SDL_SetRelativeMouseMode_t pfn_SDL_SetRelativeMouseMode;
static pfn_SDL_GetRelativeMouseMode_t pfn_SDL_GetRelativeMouseMode;
static pfn_SDL_ShowCursor_t pfn_SDL_ShowCursor;
static pfn_SDL_JoystickGetAttached_t pfn_SDL_JoystickGetAttached;
static pfn_SDL_JoystickUpdate_t pfn_SDL_JoystickUpdate;
static pfn_SDL_JoystickGetAxis_t pfn_SDL_JoystickGetAxis;
static pfn_SDL_JoystickGetHat_t pfn_SDL_JoystickGetHat;
static pfn_SDL_JoystickGetButton_t pfn_SDL_JoystickGetButton;
static pfn_SDL_PumpEvents_t pfn_SDL_PumpEvents;
static pfn_SDL_PeepEvents_t pfn_SDL_PeepEvents;
static pfn_SDL_HapticOpenFromJoystick_t pfn_SDL_HapticOpenFromJoystick;
static pfn_SDL_HapticClose_t pfn_SDL_HapticClose;
static pfn_SDL_HapticRumbleSupported_t  pfn_SDL_HapticRumbleSupported;
static pfn_SDL_HapticRumbleInit_t pfn_SDL_HapticRumbleInit;
static pfn_SDL_HapticRumblePlay_t pfn_SDL_HapticRumblePlay;
static pfn_SDL_HapticRumbleStop_t pfn_SDL_HapticRumbleStop;
static pfn_SDL_GetTicks_t pfn_SDL_GetTicks;
static pfn_SDL_Delay_t pfn_SDL_Delay;
static pfn_SDL_Init_t pfn_SDL_Init;
static pfn_SDL_InitSubSystem_t  pfn_SDL_InitSubSystem;
static pfn_SDL_QuitSubSystem_t pfn_SDL_QuitSubSystem;
static pfn_SDL_WasInit_t pfn_SDL_WasInit;

#define loadSymbol(x) pfn_##x = reinterpret_cast<pfn_##x##_t>(GetProcAddress(hModule, #x))

void sdl2_loader_init() {
    hModule = LoadLibrary(L"SDL2.dll");

    loadSymbol(SDL_NumJoysticks);
    loadSymbol(SDL_JoystickOpen);
    loadSymbol(SDL_JoystickName);
    loadSymbol(SDL_JoystickClose);
    loadSymbol(SDL_GetError);
    loadSymbol(SDL_GetWindowSize);
    loadSymbol(SDL_GetKeyboardFocus);
    loadSymbol(SDL_GetKeyboardState);
    loadSymbol(SDL_GetMouseState);
    loadSymbol(SDL_WarpMouseInWindow);
    loadSymbol(SDL_SetRelativeMouseMode);
    loadSymbol(SDL_GetRelativeMouseMode);
    loadSymbol(SDL_ShowCursor);
    loadSymbol(SDL_JoystickGetAttached);
    loadSymbol(SDL_JoystickUpdate);
    loadSymbol(SDL_JoystickGetAxis);
    loadSymbol(SDL_JoystickGetHat);
    loadSymbol(SDL_JoystickGetButton);
    loadSymbol(SDL_PumpEvents);
    loadSymbol(SDL_PeepEvents);
    loadSymbol(SDL_HapticOpenFromJoystick);
    loadSymbol(SDL_HapticClose);
    loadSymbol(SDL_HapticRumbleSupported);
    loadSymbol(SDL_HapticRumbleInit);
    loadSymbol(SDL_HapticRumblePlay);
    loadSymbol(SDL_HapticRumbleStop);
    loadSymbol(SDL_GetTicks);
    loadSymbol(SDL_Delay);
    loadSymbol(SDL_Init);
    loadSymbol(SDL_InitSubSystem);
    loadSymbol(SDL_QuitSubSystem);
    loadSymbol(SDL_WasInit);
}

void sdl2_loader_deinit() {
    FreeLibrary(hModule);
}

int SDL_NumJoysticks() { return pfn_SDL_NumJoysticks(); }
SDL_Joystick* SDL_JoystickOpen(int device_index) { return pfn_SDL_JoystickOpen(device_index); }
const char* SDL_JoystickName(SDL_Joystick* joystick) { return pfn_SDL_JoystickName(joystick); }
void SDL_JoystickClose(SDL_Joystick* joystick) { return pfn_SDL_JoystickClose(joystick); }
const char* SDL_GetError() { return pfn_SDL_GetError(); }
void SDL_GetWindowSize(SDL_Window* window, int* w, int* h) { return pfn_SDL_GetWindowSize(window, w, h); }
SDL_Window* SDL_GetKeyboardFocus() { return pfn_SDL_GetKeyboardFocus(); }
const Uint8* SDL_GetKeyboardState(int* numkeys) { return pfn_SDL_GetKeyboardState(numkeys); }
Uint32 SDL_GetMouseState(int* x, int* y) { return pfn_SDL_GetMouseState(x, y); }
void SDL_WarpMouseInWindow(SDL_Window* window, int x, int y) { return pfn_SDL_WarpMouseInWindow(window, x, y); }
int SDL_SetRelativeMouseMode(SDL_bool enabled) { return pfn_SDL_SetRelativeMouseMode(enabled); }
SDL_bool SDL_GetRelativeMouseMode() { return pfn_SDL_GetRelativeMouseMode(); }
int SDL_ShowCursor(int toggle) { return pfn_SDL_ShowCursor(toggle); }
SDL_bool SDL_JoystickGetAttached(SDL_Joystick* joystick) { return pfn_SDL_JoystickGetAttached(joystick); }
void SDL_JoystickUpdate() { return pfn_SDL_JoystickUpdate(); }
Sint16 SDL_JoystickGetAxis(SDL_Joystick* joystick, int axis) { return pfn_SDL_JoystickGetAxis(joystick, axis); }
Uint8 SDL_JoystickGetHat(SDL_Joystick* joystick, int hat) { return pfn_SDL_JoystickGetHat(joystick, hat); }
Uint8 SDL_JoystickGetButton(SDL_Joystick* joystick, int button) { return pfn_SDL_JoystickGetButton(joystick, button); }
void SDL_PumpEvents() { return pfn_SDL_PumpEvents(); }
int SDL_PeepEvents(SDL_Event* events, int numevents, SDL_eventaction action, Uint32 minType, Uint32 maxType) { return pfn_SDL_PeepEvents(events, numevents, action, minType, maxType); }
SDL_Haptic* SDL_HapticOpenFromJoystick(SDL_Joystick* joystick) { return pfn_SDL_HapticOpenFromJoystick(joystick); }
void SDL_HapticClose(SDL_Haptic* haptic) { return pfn_SDL_HapticClose(haptic); }
int SDL_HapticRumbleSupported(SDL_Haptic* haptic) { return pfn_SDL_HapticRumbleSupported(haptic); }
int SDL_HapticRumbleInit(SDL_Haptic* haptic) { return pfn_SDL_HapticRumbleInit(haptic); }
int SDL_HapticRumblePlay(SDL_Haptic* haptic, float strength, Uint32 length) { return pfn_SDL_HapticRumblePlay(haptic, strength, length); }
int SDL_HapticRumbleStop(SDL_Haptic* haptic) { return pfn_SDL_HapticRumbleStop(haptic); }
Uint32 SDL_GetTicks() { return pfn_SDL_GetTicks(); }
void SDL_Delay(Uint32 ms) { return pfn_SDL_Delay(ms); }
int SDL_Init(Uint32 flags) { return pfn_SDL_Init(flags); }
int SDL_InitSubSystem(Uint32 flags) { return pfn_SDL_InitSubSystem(flags); }
void SDL_QuitSubSystem(Uint32 flags) { return pfn_SDL_QuitSubSystem(flags); }
Uint32 SDL_WasInit(Uint32 flags) { return pfn_SDL_WasInit(flags); }

}
