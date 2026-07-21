// Engine/RHI/include/RHI/Shader.h

#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <string_view>
#include <vector>

namespace Valinor::RHI {

// Enum for supported shader types
enum class ShaderType : uint8_t {
	Vertex, Fragment, Compute
};

// Abstract base class for shaders
class Shader {
public:
	virtual ~Shader() = default;
	Shader(const Shader&)            = delete; // Disable copy constructor
	Shader& operator=(const Shader&) = delete; // Disable copy assignment

	[[nodiscard]] virtual ShaderType  GetStage() const noexcept = 0;         // Get shader stage (vertex, fragment, etc.)
	[[nodiscard]] virtual std::string_view GetName() const noexcept = 0;      // Get shader name

	// Loads SPIR-V binary from disk and creates a shader instance
	// OpenGL 4.6: glShaderBinary + GL_ARB_gl_spirv 
	// Vulkan: VkShaderModuleCreateInfo
	[[nodiscard]]
	static std::shared_ptr<Shader>
		Create(std::string_view spirvPath, ShaderType stage,
			   std::string_view debugName = "");

protected:
	explicit Shader(ShaderType s) : m_Stage(s) {} // Protected constructor
	ShaderType m_Stage; // Shader stage type
};

} // namespace Valinor::RHI