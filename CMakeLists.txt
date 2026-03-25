cmake_minimum_required(VERSION 3.22)
project(ValinorEngine VERSION 0.1.0 LANGUAGES CXX)
 
# ── C++20 required ────────────────────────────────────────────
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
 
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
 
# ── Test application ───────────────────────────────────────────
add_subdirectory(Sandbox)