// Engine/Core/src/Application.cpp

#include <Core/Application.h>
#include <chrono>
#include <algorithm>

namespace Valinor {
// Application constructor initializes the application with the given configuration, window, and command buffer
Application::Application(ApplicationConfig config,
						std::unique_ptr<IWindow> window,
						std::shared_ptr<RHI::CommandBuffer> cmd)
	: m_Config(std::move(config))
	, m_Window(std::move(window))
	, m_CmdBuffer(std::move(cmd))
{}

void Application::Run() {
	using Clock = std::chrono::steady_clock;
	auto last = Clock::now();

	while (m_Running && !m_Window->ShouldClose()) {
		// DeltaTime with capping of 50ms to avoid spiral of death
		auto now = Clock::now();
		float dt = std::chrono::duration<float>(now - last).count();
		last = now;
		dt = std::min(dt, 0.05f);  // Cap at 50ms

		m_Window->PollEvents();    // 1.Input
		Internalupdate(dt);		   // 2.Update
		OnUpdate(dt);			   

		m_CmdBuffer->Begin();	   // 3.Render
		m_CmdBuffer->Clear();	   // Clear screen (placeholder)
		InternalRender();
		OnRender();
		m_CmdBuffer->Submit();

		m_Window->SwapBuffers();   // 4.Present
	}
}

void Application::InternalUpdate(float) {}
void Application::InternalRender()		{}

} // namespace Valinor