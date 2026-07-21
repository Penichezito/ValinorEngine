# cmake/CompilerOptions.cmake

# Interface library for flags propagation
add_library(ValinorCompilerOptions INTERFACE)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang" )
	target_compile_options(ValinorCompilerOptions INTERFACE
		-Wall -Wextra -wpedantic
		-Wno-unused-parameter
		$<$<CONFIG:Debug>:-fsanitize-address, undefined>
		$<$<CONFIG:Release>:-03 -march-native>
	)
	target_link_options(ValinorCompilerOptions INTERFACE 
		$<$<CONFIG:Debug>:-fsanitize-address, undefined>
	)
elseif(MSVC)
	target_compile_options(ValinorCompilerOptions INTERFACE
		/W4 /permissive-
		$<$<CONFIG:Release>:/02 /GL>
	)
endif()

# C++20 Mandatory Features 
target_compile_features(ValinorCompilerOptions INTERFACE cxx_std_20)