# Engine/RHI/CMakeLists.txt
# Module for the RHI (Rendering Hardware Interface) component of the Valinor Engine.
# Modulule INTERFACE => header-only, no compiled sources

add_library(ValinorRHI INTERFACE)

target_include_directories(Engine_RHI
	INTERFACE
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	$<INSTALL_INTERFACE:include>
)

# RHI depends nothing else - it's pure contract.

