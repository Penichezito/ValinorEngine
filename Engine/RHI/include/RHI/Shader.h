// Engine/RHI/include/RHI/Shader.h

#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <string_view>
#include <vector>

namespace Valinor::RHI {

	enums class ShaderType : uint8_t {
		Vertex, Fragment, Compute
	};



} // namespace Valinor::RHI