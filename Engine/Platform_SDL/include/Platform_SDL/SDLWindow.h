// Engine/Platform_SDL/include/Platform_SDL/SDLWindow.h
// SDLWindow.h - SDL implementation of the IWindow interface
#pragma once
#include <Core/Application.h> // IWindow interface

// Dont' include SDL headers in the header file to avoid polluting the global namespace

struct SDL_Window; // Forward declaration of SDL_Window
using SDL_GLContext = void*; // Placeholder for SDL_GLContext