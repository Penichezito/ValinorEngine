// Engine/Platform_SDL/include/Platform_SDL/SDLWindow.h
#pragma once
#include <Core/Application.h> // IWindow interface

// Dont' include SDL headers here - to avoid polluting the global namespace
struct SDL_Window;            // Forward declaration of SDL_Window
using  SDL_GLContext = void*; // Placeholder for SDL_GLContext

namespace Valinor::Platform {

class SDLWindow final : public IWindow {
public:
	explicit SDLWindow(const ApplicationConfig& cfg);
	~SDLWindow() override;

	void PollEvents()  override;
	void SwapBuffers() override;

	[[nodiscard]] bool  ShouldClose()      const override;
	[[nodiscard]] void* GetNativeHandle()  const override;

private:
	SDL_Window*   m_Window       = nullptr; // Pointer to the SDL window
	SDL_GLContext m_GLContext    = nullptr; // OpenGL context for rendering
	bool          m_ShouldClose  = false;   // Flag to indicate if the window should close
};


} // namespace Valinor::Platform