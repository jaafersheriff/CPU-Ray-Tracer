set(CMAKE_LEGACY_CYGWIN_WIN32 0) # Remove when CMake >= 2.8.4 is required

cmake_minimum_required(VERSION 2.8)

# Name of the project
project(raytrace)

# Use glob to get the list of all source files.
file(GLOB_RECURSE SOURCES "src/*.cpp")

# We don't really need to include header and resource files to build, but it's nice to have them show up in IDEs.
file(GLOB_RECURSE HEADERS "src/*.h")
file(GLOB_RECURSE HEADERS "src/*.hpp")

set(GLM_INCLUDE_DIR "$ENV{GLM_INCLUDE_DIR}")
if(NOT GLM_INCLUDE_DIR)
  MESSAGE(FATAL_ERROR "Please point the environment variable GLM_INCLUDE_DIR to the include directory of your GLM installation.")
endif()
include_directories(${GLM_INCLUDE_DIR})

# Set the executable.
add_executable(${CMAKE_PROJECT_NAME} ${SOURCES} ${HEADERS})

# OS specific options and libraries
if(WIN32)
  # c++0x is enabled by default.
  # -Wall produces way too many warnings.
  # -pedantic is not supported.
  # Disable warning 4996.
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4996")
else()
  # Enable all pedantic warnings.
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -Wall -pedantic")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")