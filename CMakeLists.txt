cmake_minimum_required(VERSION 3.22)
project(ValinorEngine VERSION 0.1.0 LANGUAGES CXX)
 
# ── C++20 required ────────────────────────────────────────────
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ── Mandatory shared configuration modules ─────────────────────
include(cmake/CompilerOptions.cmake)
include(cmake/FindDependencies.cmake)

# ── GLSL to SPIR-V shader compilation (pre-build) ───────────────
find_program(GLSLC glslc REQUIRED)

file(GLOB_RECURSE GLSL_FILES
	"${CMAKE_SOURCE_DIR}/Shaders/glsl/*.vert"
	"${CMAKE_SOURCE_DIR}/Shaders/glsl/*.frag"
)

foreach(GLSL_FILE ${GLSL_FILES})
	get_filename_component(FILE_NAME ${GLSL_FILE} NAME)
	set(SPV_OUT "${CMAKE_SOURCE_DIR}/Shaders/compiled/${FILE_NAME}.spv")
	add_custom_command(
		OUTPUT  ${SPV_OUT}
		COMMAND ${GLSL} ${GLSL_FILE} -o ${SPV_OUT}
		DEPENDS ${GLSL_FILE}
		COMMENT "[Valinor Engine] Compiling shader: ${FILE_NAME}"
	)
	list(APPEND SPV_FILES $(SPV_OUT))
endforeach()
 
# ── Auxiliary modules ───────────────────────────────────────────
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
 
# ── ThirdParty (header-only for now) ──────────────────────────
add_subdirectory(ThirdParty/glm      EXCLUDE_FROM_ALL)
add_subdirectory(ThirdParty/entt     EXCLUDE_FROM_ALL)
 
# ── Engine modules ────────────────────────────────────────────
add_subdirectory(Engine/Core)
add_subdirectory(Engine/RHI)
add_subdirectory(Engine/Renderer_OpenGL)
add_subdirectory(Engine/Platform_SDL)
add_subdirectory(Engine/ECS)
add_subdirectory(Engine/Assets)
 
# ── Test application ───────────────────────────────────────────
add_subdirectory(Sandbox)
add_subdirectory(Editor)