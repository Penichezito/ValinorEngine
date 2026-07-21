# Engine/Core/CmakeLists.txt

add_library(Engine_Core STATIC)

target_sources(Engine_Core PRIVATE
	src/Application.cpp
	src/LayersStack.cpp
)

target_include_directories(Engine_Core
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(Engine_Core 
	PUBLIC Engine_RHI # Core know interfaces, not impls
	PUBLIC            #	no SDL, no OpenGl here
)