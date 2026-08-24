cmake_minimum_required(VERSION 3.21)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
if ("${CMAKE_SYSTEM_NAME}" STREQUAL "iOS" OR IOS)
    set(CMAKE_OSX_ARCHITECTURES "arm64")
else()
    set(CMAKE_OSX_ARCHITECTURES "arm64;x86_64")
endif()
set(CMAKE_CXX_VISIBILITY_PRESET hidden)

# btw i replaced line 403-406 in the CMakeLists.txt file (of the SDK) to:
#[[
message(STATUS "the worst hack ever")
target_link_libraries(${PROJECT_NAME} INTERFACE "$ENV{GEODE_SDK}/bin/win/Geode.lib")
]]
# because for SOME reason it says to install the binaries EVEN IF i have them??? hello??? (PLEASE fix linux support)

if (CMAKE_BUILD_TYPE MATCHES "RelWithDebInfo" OR CMAKE_CONFIGURATION_TYPES MATCHES "RelWithDebInfo")
    add_compile_definitions(DEBUG_MODE=1)
else()
    add_compile_definitions(DEBUG_MODE=0)
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # intellisense
set(GEODE_TARGET_PLATFORM Win64)
project(Webview VERSION 1.0.0)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp)
add_library(${PROJECT_NAME} SHARED ${SOURCES})

if (NOT DEFINED ENV{GEODE_SDK})
    message(FATAL_ERROR "Unable to find Geode SDK! Please define GEODE_SDK environment variable to point to Geode (idiot)")
else()
    message(STATUS "Found Geode: $ENV{GEODE_SDK}")
endif()

add_subdirectory($ENV{GEODE_SDK} ${CMAKE_CURRENT_BINARY_DIR}/geode)
setup_geode_mod(${PROJECT_NAME})
