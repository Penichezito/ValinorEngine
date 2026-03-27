// Engine/Platform_SDL/src/SDLWindow.cpp
#include <Platform_SDL/SDLWindow.h>
#include <SDL2/SDL.h> // SDL just appears here
#include <stdexcept>

namespace Valinor::Platform {

// Constructor: Initializes SDL, creates window and OpenGL context
SDLWindow::SDLWindow(const ApplicationConfig& cfg) {
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		throw std::runtime_error(SDL_GetError());

	// Set OpenGL attributes (version 4.6 core profile)
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); // Enable double buffering

	m_Window = SDL_CreateWindow(
		cfg.Title.c_str(),
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		static_cast<int>(cfg.Width),
		static_cast<int>(cfg.Height),
		SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN
	);
	if (!m_Window)
		throw std::runtime_error(SDL_GetError());

	m_GLContext = SDL_GL_CreateContext(m_Window);
	if (!m_GLContext)
		throw std::runtime_error(SDL_GetError());

	SDL_GL_SetSwapInterval(1); // Enable VSync
}

// Destructor: Cleans up SDL resources
SDLWindow::~SDLWindow() {
	if (m_GLContext) SDL_GL_DeleteContext(m_GLContext);
	if (m_Window)    SDL_DestroyWindow(m_Window);
	SDL_Quit();
}

// Polls for window and keyboard events
void SDLWindow::PollEvents() {
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT)
			m_ShouldClose = true;
		if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)
			m_ShouldClose = true;
	}
}

// Swaps the OpenGL buffers
void SDLWindow::SwapBuffers() {
	SDL_GL_SwapWindow(m_Window);
}

// Returns whether the window should close
bool SDLWindow::ShouldClose() const { return m_ShouldClose; }

// Returns the native SDL window handle
void* SDLWindow::GetNativeHandle() const { return m_Window; }

} // namespace Valinor::Platform