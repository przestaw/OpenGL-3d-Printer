## GLEW
set(glew-cmake_BUILD_STATIC ON CACHE BOOL "Build the static glew library")
set(glew-cmake_BUILD_SHARED OFF CACHE BOOL "Don't build the static glew library")
set(glew-cmake_BUILD_SINGLE_CONTEXT ON CACHE BOOL "Build the single context glew library")
set(glew-cmake_BUILD_MULTI_CONTEXT OFF CACHE BOOL "Don't build the multi context glew library")
add_subdirectory(glew EXCLUDE_FROM_ALL)
add_definitions(-DGLEW_STATIC)

## GLFW
set(BUILD_SHARED_LIBS OFF CACHE BOOL "Don't build shared libs for GLFW")
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "Don't build examples for GLFW")
set(GLFW_BUILD_TESTS OFF CACHE BOOL "Don't build tests for GLFW")
set(GLFW_INSTALL OFF CACHE BOOL "Don't generate install target for GLFW")
set(GLFW_BUILD_DOCS OFF CACHE BOOL "Don't generate docs for GLFW")
add_subdirectory(glfw EXCLUDE_FROM_ALL)

## GLM
set(GLM_TEST_ENABLE_CXX_17 ON CACHE BOOL "Compile GLM with C++17 support")
set(GLM_TEST_ENABLE_FAST_MATH OFF CACHE BOOL "Disable FastMath feature for GLM")
set(GLM_TEST_ENABLE OFF CACHE BOOL "Don't build tests for GLM")
set(GLM_TEST_ENABLE_SIMD_SSE2 ON CACHE BOOL "Enable SSE2 optimizations for GLM")
set(GLM_TEST_ENABLE_SIMD_SSE3 ON CACHE BOOL "Enable SSE3 optimizations for GLM")
set(GLM_TEST_ENABLE_SIMD_SSSE3 ON CACHE BOOL "Enable SSSE3 optimizations for GLM")
set(GLM_TEST_ENABLE_SIMD_SSE4_1 ON CACHE BOOL "Enable SSE 4.1 optimizations for GLM")
set(GLM_TEST_ENABLE_SIMD_SSE4_2 ON CACHE BOOL "Enable SSE 4.2 optimizations for GLM")
set(GLM_TEST_ENABLE_SIMD_AVX ON CACHE BOOL "Enable AVX optimizations for GLM")
set(GLM_TEST_ENABLE_SIMD_AVX2 ON CACHE BOOL "Enable AVX2 optimizations for GLM")
add_subdirectory(glm EXCLUDE_FROM_ALL)
#target_include_directories(glm_static PUBLIC glm/)
#target_include_directories(glm_shared PUBLIC glm/)

## SOIL
if(ANDROID)
	# Android requires GL ES 2.0 package automatically
	set(SOIL_LIBRARIES GLESv2)
else()
	find_package(OpenGL REQUIRED)
	set(SOIL_INCLUDE_DIRS ${OPENGL_INCLUDE_DIR})
	set(SOIL_LIBRARIES ${OPENGL_LIBRARIES})
endif()

file(GLOB SOIL_SOURCES soil/src/*.c)
file(GLOB SOIL_HEADERS soil/src/*.h)
add_library(SOIL_static STATIC
	${SOIL_SOURCES} ${SOIL_HEADERS}
)

target_link_libraries(SOIL_static
	PRIVATE
		${SOIL_LIBRARIES}
)

target_include_directories(SOIL_static
	PRIVATE
		${SOIL_INCLUDE_DIRS}
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/soil/src
) 
