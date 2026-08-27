cmake_minimum_required(VERSION 3.21)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if ("${CMAKE_SYSTEM_NAME}" STREQUAL "iOS" OR IOS)
    set(CMAKE_OSX_ARCHITECTURES "arm64")
else()
    set(CMAKE_OSX_ARCHITECTURES "arm64;x86_64")
endif()

# i DID use arch btw (ill be more professional i swear (not really))

if (CMAKE_BUILD_TYPE MATCHES "RelWithDebInfo" OR CMAKE_CONFIGURATION_TYPES MATCHES "RelWithDebInfo")
    add_compile_definitions(WEBVIEW_DEBUG_MODE=1)
else()
    add_compile_definitions(WEBVIEW_DEBUG_MODE=0)
endif()

include(FetchContent)
project(Webview VERSION 1.0.0)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp)
add_library(${PROJECT_NAME} SHARED ${SOURCES})
target_include_directories(${PROJECT_NAME}
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
)

if (NOT DEFINED ENV{GEODE_SDK})
    message(FATAL_ERROR "Unable to find Geode SDK! Please define GEODE_SDK environment variable to point to Geode")
else()
    message(STATUS "Found Geode: $ENV{GEODE_SDK}")
endif()

## PACKAGES (Fetch) ##
# Lexbor (HTML, CSS Parser)
FetchContent_Declare(
  lexbor
  GIT_REPOSITORY https://github.com/lexbor/lexbor
  GIT_TAG v3.0.0
)
FetchContent_MakeAvailable(lexbor)
##         ##

add_subdirectory($ENV{GEODE_SDK} ${CMAKE_CURRENT_BINARY_DIR}/geode)
setup_geode_mod(${PROJECT_NAME})

## PACKAGES (Linking) ##
target_link_libraries(${PROJECT_NAME} lexbor_static)
##                    ##