// Engine/RHI/include/RHI/CommandBuffer.h

#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <vector>
#include <RHI/PipelineState.h>

namespace Valinor::RHI {

// Forward declaration of buffer classes
class VertexBuffer;
class IndexBuffer;

// Structure representing a draw command
struct DrawCommand {
	std::shared_ptr<PipelineState> Pipeline;          // Pipeline state for the draw call
	std::shared_ptr<VertexBuffer>  VBO;               // Vertex buffer to bind
	std::shared_ptr<IndexBuffer>   IBO;               // Index buffer (nullptr = DrawArrays)
	uint32_t                       Count        = 0;  // Number of indices/vertices to draw
	uint32_t                       InstantCount = 0;  // Number of instances to draw
};

// Command buffer for recording and submitting draw commands
class CommandBuffer {
public:
	CommandBuffer()  = default;
	~CommandBuffer() = default;

	// Begins recording commands
	void Begin();
	// Sets the clear color for the framebuffer
	void SetClearColor(float r, float g, float b, float a = 1.0f);
	// Clears the framebuffer
	void Clear();

	// Stores a draw command (does not call OpenGL directly)
	void DrawIndexed(const DrawcallCommand& cmd);

	// Submits all recorded draw commands for execution
	void Submit();
	// Resets the command buffer for reuse
	void Reset();

	// Returns the number of recorded draw calls
	[[nodiscard]] size_t GetDrawCallcount() const noexcept {
		return m_DrawCalls.size();
	}

private:
	std::vector<DrawCallCommand> m_DrawCalls;              // List of recorded draw calls
	float m_ClearColor[4] = { 0.08f, 0.08f, 0.10f, 1.0f }; // Default clear color
};

} // namespace Valinor::RHI

