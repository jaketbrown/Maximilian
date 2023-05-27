cmake_minimum_required (VERSION 3.15)

project (maximilian_fuzz)

set(CMAKE_CXX_STANDARD 17)

include_directories(../../src)
include_directories(../../src/libs)


if(MAXI_BUILD_FUZZER)
    if(NOT CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        message(FATAL_ERROR "Fuzzer is only supported on Clang")
    endif()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=fuzzer-no-link,address,undefined")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-sanitize-recover=undefined")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-omit-frame-pointer")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O1")
    add_link_options(-fsanitize=fuzzer-no-link,address,undefined)
    #add_subdirectory(../../mayhem ${CMAKE_CURRENT_BINARY_DIR}/mayhem_binaries)
endif()

add_executable(Maximilian_fuzz Maximilian_fuzz.cpp ../src/maximilian.cpp)
target_compile_options(Maximilian_fuzz PUBLIC -Wall)
target_link_libraries(Maximilian_fuzz PUBLIC -lpthread)



target_compile_options(Maximilian_fuzz PUBLIC -fsanitize=fuzzer,address,undefined)
target_link_options(Maximilian_fuzz PUBLIC -fsanitize=fuzzer,address,undefined)

file (MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/testsuite)
file (COPY testsuite/test-audio.wav DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/testsuite)

