// Engine/Core/include/Core/Application.h

#pragma once
#include <memory>
#include <string>
#include <RHI/CommandBuffer.h>

namespace Valinor {

struct ApplicationConfig {
	std::string		Title  = "Valinor Engine";
	uint32_t		Width  = 1280;
	uint32_t		Height = 720;
	bool			VSync = true;
};

// Window contract - Core don't know about the windowing system (GLFW, SDL, etc.)
class IWindow {
public:
	virtual ~IWindow() = default;
	virtual void PollEvents() = 0;
	virtual void SwapBuffers() = 0;
	[[nodiscard]] virtual bool ShouldClose()       const = 0;
	[[nodiscard]] virtual void* GetNativeHandle() const = 0;
};

class Application {
public:
	Application(ApplicationConfig config,
				std::unique_ptr<IWindow> window,
				std::shared_ptr<RHI::CommandBuffer> cmdBuffer);

	virtual ~Application() = default;
	Application(const application)            = delete;            // Disable copy constructor
	Application& operator=(const Application) = delete;            // Disable copy assignment

	void Run();

protected:
	virtual void OnUpdate(float dt) {}
	virtual void OnRender() {}

private:
	void InternalUpdate(float dt);
	void InternalRender();

	ApplicationConfig                   m_Config;
	std::unique_ptr<IWindow>            m_Window;
	std::shared_ptr<RHI::CommandBuffer> m_CmdBuffer;
	bool                                m_Running = false;
};

} // namespace Valinor