# Top-level project configuration
cmake_minimum_required(VERSION 3.11 FATAL_ERROR)

# Set naming scheme 
set(PROJECT_NAME Printer3d)
project(${PROJECT_NAME})

set(EXECUTABLE ${PROJECT_NAME}-program)
set(LIBRARY ${PROJECT_NAME}-lib)

# Add custom cmake modules
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake_modules/finders")
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake_modules")

# Set output directories
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE})

set(OpenGL_GL_PREFERENCE LEGACY)
cmake_policy(SET CMP0072 NEW)

# add external modules
add_subdirectory("submodules")

include_directories("submodules/glm")
include_directories("submodules/glew/include/GL")
include_directories("submodules/glfw/include/GLFW")

# Add 'resources' target - just copy them into build directory
add_custom_target(resources ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/res ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/res
        )
add_custom_target(shaders ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/shaders ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/shaders
        )

# Sources & include files
file(GLOB_RECURSE SRC_FILES "${PROJECT_SOURCE_DIR}/src/*.cpp")
file(GLOB_RECURSE INC_FILES "${PROJECT_SOURCE_DIR}/include/*.h")

include_directories(include)

# Configure Toolchain
if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    # using Clang
    if(USE_THREAD_CONTROL)
        set(CODE_CONTROL_FLAGS ${CODE_CONTROL_FLAGS} -Wthread-safety -fsanitize=thread)
    endif()
    if(USE_CODE_CONTROL)
        set(CODE_CONTROL_FLAGS ${CODE_CONTROL_FLAGS} -fsanitize=memory -fsanitize=address -fsanitize=undefined)
    endif()

    set(CMAKE_CXX_FLAGS_DEBUG   "${CMAKE_CXX_FLAGS_DEBUG}   -O0 -g ${CODE_CONTROL_FLAGS} -Wextra-tokens -Wambiguous-member-template -Wshadow -Wall -pedantic -Wextra -Wold-style-cast")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -finline-functions -fmerge-all-constants -fvectorize -flto")

    include(LLVMtoolchain)

    set(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} -fuse-ld=lld)

    set(CMAKE_C_ARCHIVE_CREATE "<CMAKE_AR> qcs <TARGET> <LINK_FLAGS> <OBJECTS>")
    set(CMAKE_C_ARCHIVE_FINISH   true)
    set(CMAKE_CXX_ARCHIVE_CREATE "<CMAKE_AR> qcs <TARGET> <LINK_FLAGS> <OBJECTS>")
    set(CMAKE_CXX_ARCHIVE_FINISH true)

elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    if(CMAKE_BUILD_TYPE EQUAL Release)
        cmake_policy(SET CMP0069 NEW)
        include(CheckIPOSupported)
        check_ipo_supported(IPO_SUPPORT)
        if(IPO_SUPPORT)
            set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
        endif()
    endif()

    # using GCC
    set(CMAKE_CXX_FLAGS_DEBUG   "${CMAKE_CXX_FLAGS_DEBUG}   -O0 -Og -g -Wshadow -Wall -pedantic -Wextra -Wold-style-cast")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -finline-functions -fdevirtualize -fmerge-constants")

    include(GNUtoolchain)
endif()


add_executable(${EXECUTABLE} main.cpp ${SRC_FILES} ${INC_FILES})

set_target_properties(${EXECUTABLE} PROPERTIES
        CXX_STANDARD 17
        CXX_EXTENSIONS OFF
        )

target_include_directories(${EXECUTABLE}
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        )

target_link_libraries(${EXECUTABLE}
        PRIVATE
        libglew_static
        glfw
        glm
        SOIL_static
        )

add_dependencies(${EXECUTABLE}
        resources
        shaders
        )

# # # Clang Tidy
# setup
function(clangformat_setup)
    if (NOT CLANGFORMAT_EXECUTABLE)
        set(CLANGFORMAT_EXECUTABLE clang-format)
    endif ()

    if (NOT EXISTS ${CLANGFORMAT_EXECUTABLE})
        find_program(clangformat_executable_tmp ${CLANGFORMAT_EXECUTABLE})
        if (clangformat_executable_tmp)
            set(CLANGFORMAT_EXECUTABLE ${clangformat_executable_tmp})
            unset(clangformat_executable_tmp)

            foreach (clangformat_source ${ARGV})
                get_filename_component(clangformat_source ${clangformat_source} ABSOLUTE)
                list(APPEND clangformat_sources ${clangformat_source})
            endforeach ()

            add_custom_target(format
                    COMMAND
                    ${CLANGFORMAT_EXECUTABLE}
                    -style=file
                    -i
                    ${clangformat_sources}
                    WORKING_DIRECTORY
                    ${CMAKE_SOURCE_DIR}
                    COMMENT
                    "Reformating with ${CLANGFORMAT_EXECUTABLE} ..."
                    )

            if (TARGET clangformat)
                add_dependencies(clangformat ${PROJECT_NAME}_clangformat)
            else ()
                add_custom_target(clangformat DEPENDS ${PROJECT_NAME}_clangformat)
            endif ()
        else ()
            message("ClangFormat: ${CLANGFORMAT_EXECUTABLE} not found!")
        endif ()
    endif ()
endfunction()

# util
function(add_clagformat_target target)
    get_target_property(target_sources ${target} SOURCES)
    clangformat_setup(${target_sources})
endfunction()

# setup for targets
clangformat_setup(${SRC_FILES} ${INC_FILES})
