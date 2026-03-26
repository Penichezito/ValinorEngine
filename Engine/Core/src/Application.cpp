// Engine/Core/src/Application.cpp

#include <Core/Application.h>
#include <chrono>
#include <algorithm>

namespace Valinor {

Application::Aplication(ApplicationConfig config,
						std::unique_ptr<IWindow> window,
						std::shared_ptr<RHI::CommandBuffer> cmd)
	: m_Config(std::move(config))
	, m_Window(std::move(window))
	, m_CmdBuffer(std::move(cmd))
{}





} // namespace Valinor