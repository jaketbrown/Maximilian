cmake_minimum_required (VERSION 3.15)

project (maximilian)

set(CMAKE_CXX_STANDARD 17)

include_directories(../../src)
include_directories(../../src/libs)

add_executable(maximilian main.cpp player.cpp RtAudio.cpp ../../src/maximilian.cpp)
target_compile_options(maximilian PUBLIC -Wall)
target_link_libraries(maximilian PUBLIC -lpthread)

if (LINUX)
  MESSAGE(STATUS "Linux build")
  target_link_libraries(maximilian PUBLIC -lasound)
  add_definitions(-D__LINUX_ALSA__)
endif()

if (OSX)
  MESSAGE(STATUS "OSX build")
  target_link_libraries(maximilian PUBLIC -lasound)
  add_definitions(-D__MACOSX_CORE__)
  #incomplete - need to add frameworks -framework CoreAudio -framework CoreFoundation
endif()


if(MAXI_BUILD_FUZZER)
  if(NOT CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    message(FATAL_ERROR "Fuzzer is only supported on Clang")
  endif()
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=fuzzer-no-link,address,undefined")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-sanitize-recover=undefined")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-omit-frame-pointer")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O1")
  add_link_options(-fsanitize=fuzzer-no-link,address,undefined)
  add_subdirectory(../../mayhem ${CMAKE_CURRENT_BINARY_DIR}/mayhem_binaries)
endif()
