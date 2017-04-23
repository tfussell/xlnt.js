if(DEFINED ENV{EMSCRIPTEN})
    set(CMAKE_TOOLCHAIN_FILE "$ENV{EMSCRIPTEN}/cmake/Modules/Platform/Emscripten.cmake"
        CACHE PATH "emscripten toolchain" FORCE)
else()
    message(FATAL_ERROR "Emscritpen not found. Set EMSCRIPTEN environment variable to point to the emscripten root directory")
endif()

cmake_minimum_required(VERSION 3.2)
project(xlnt.js VERSION 0.9.0)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PROJECT_VENDOR "Thomas Fussell")
set(PROJECT_CONTACT "thomas.fussell@gmail.com")
set(PROJECT_URL "https://github.com/tfussell/xlnt.js")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --bind")
set(XLNT_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/xlnt)
set(STATIC ON)
add_subdirectory(${XLNT_ROOT_DIR}/source ${CMAKE_CURRENT_BINARY_DIR}/xlnt)

set(XLNTJS_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/source)

file(GLOB XLNTJS_HEADERS ${XLNTJS_SOURCE_DIR}/*.hpp)
file(GLOB XLNTJS_SOURCES ${XLNTJS_SOURCE_DIR}/*.cpp)

add_executable(xlnt.js ${XLNTJS_HEADERS} ${XLNTJS_SOURCES})
target_link_libraries(xlnt.js PRIVATE xlnt)
target_include_directories(xlnt.js PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/source)
set_target_properties(xlnt.js PROPERTIES SUFFIX "")

source_group(xlnt.js FILES ${XLNTJS_HEADERS} ${XLNTJS_SOURCES})

add_custom_command(TARGET xlnt.js POST_BUILD 
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    $<TARGET_FILE:xlnt.js>
    ${CMAKE_CURRENT_SOURCE_DIR}/dist)

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    add_custom_command(TARGET xlnt.js POST_BUILD 
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:xlnt.js>.mem
        ${CMAKE_CURRENT_SOURCE_DIR}/dist)
endif()
