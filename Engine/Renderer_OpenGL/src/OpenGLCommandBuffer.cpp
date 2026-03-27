// Engine/Renderer_OpenGL/src/OpenGLCommandBuffer.cpp
#include <RHI/CommandBuffer.h>
#include <GL/glew.h>  // OpenGL functions only appear here inside .cpp
#include <cassert>

namespace Valinor::RHI{

// Begins recording commands; clears previous draw calls
void CommandBuffer::Begin() {
	m_DrawCalls.clear();
}

// Sets the clear color for the framebuffer
void CommandBuffer::SetClearColor(float r, float g, float b, float a) {
	m_ClearColor[0] = r; 	m_ClearColor[1] = g;
	m_ClearColor[2] = b; 	m_ClearColor[3] = a;
}

// Clears the framebuffer using the set clear color
void CommandBuffer::Clear() {
	// We record the intent — glClear is executed in Submit
	// (simplification: for Phase 1 you can call it directly)
	glClearColor(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2], m_ClearColor[3]);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

// Queues a draw call for indexed drawing
void CommandBuffer::DrawIndexed(const DrawCallCommand& cmd) {
	// Phase 1: Queue for later execution in Submit
	m_DrawCalls.push_back(cmd);
}

// Submits all queued draw calls to the GPU
void CommandBuffer::Submit() {
	for (const auto& cmd : m_DrawCalls) {
		if (cmd.Pipeline) cmd.Pipeline->Bind();

		// Bind the Vertex Array Object (VAO) using the VBO handle
		glBindVertexArray(
			static_cast<GLuint>(cmd.VBO->GetHandle())
		);

		if (cmd.IBO) {
			// Indexed draw call
			glDrawElementsInstanced(
				GL_TRIANGLES,
				static_cast<GLsizei>(cmd.Count),
				GL_UNSIGNED_INT,
				nullptr, // Offset in the index buffer
				static_cast<GLsizei>(cmd.InstanceCount)
			);
		}
		else {
			// Non-indexed draw call
			glDrawArraysInstanced(
				GL_TRIANGLES,
				0, // Starting vertex
				static_cast<GLsizei>(cmd.Count),
				static_cast<GLsizei>(cmd.InstanceCount)
			);

		}
	}
	m_DrawCalls.clear(); // Clear after submission
}

// Resets the command buffer by clearing all queued draw calls
void CommandBuffer::Reset() {
	m_DrawCalls.clear();
}

} // namespace Valinor::RHI
