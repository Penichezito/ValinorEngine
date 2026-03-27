// Engine/RHI/include/RHI/PipelineState.h
#pragma once
#include <cstdint>
#include <memory>
#include <string_view>

namespace Valinor::RHI {

// Foward declaration - Shader.h implements the Shader class, but we don't want to include it here.
class Shader;

enum class BlendMode     : uint8_t { None, Alpha, Additive };
enum class CullMode      : uint8_t { None, Back, Front };
enum class DepthTestMode : uint8_t { LessEqual, Less, Always, Never };

struct PipelineStateDescriptor {
	std::shared_ptr<Shader> VertexShader;
	std::shared_ptr<Shader> FragmentShader;

	BlendMode     BlendMode  = BlendMode::None;
	CullMode      CullMode   = CullMode::Back;
	DepthTestMode DepthTest  = DepthTestMode::LessEqual;
	bool		  DepthWrite = true;
	bool		  Wireframe  = false;

	std::string_view DebugName; // Optional debug name
};

class PipelineState {
public:
	virtual ~PipelineState() = default;

	//  Applies ALL states at once. 
	// ⚠ Forbidden in game code: glEnable(GL_BLEND) 
	// ✅ Correct: pipeline->Bind()
	virtual void Bind()  const = 0;
	virtual void Ubind() const = 0;

	[[nodiscard]]
	static std::unique_ptr<PipelineState>
		Create(const PipelineStateDescriptor& desc);
};

} // namespace Valinor::RHI