# Engine/Renderer_OpenGL/CMakeLists.txt

add_library(Engine_OpenGL STATIC)

target_sources(Engine_OpenGL PRIVATE 
	src/OpenGLContext.cpp
	src/OpenGLTexture2D.cpp
	src/OpenGLShader.cpp
	src/OpenGLCommandeBuffer.cpp
	src/OpenGLPipelineState.cpp
)

target_include_directories(Engine_OpenGL PRIVATE 
	PUBLIC	
		# OpenGL implementation headers become available to those who link against it
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	PRIVATE 
		# OpenGL and GLEW remain PRIVATE — they do not leak upwards.
		${OPENGL_INCLUDE_DIR}
		${GLEW_INLCUDE_DIRS}
)

target_link_libraries(Engine_OpenGL 
	PUBLIC  Engine_RHI			# Exports the RHI interface (contracts) 
	PRIVATE ${OPENGL_LIBRARIES} # OpenGL PRIVATE — does not leak
	PRIVATE GLEW::GLEW		    # GLEW PRIVATE
)		