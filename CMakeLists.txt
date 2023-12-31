cmake_minimum_required(VERSION 3.11)

set(CMAKE_MODULE_PATH
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake_modules/"
    CACHE INTERNAL "Default module path.")

option(CMAKE_VERBOSE_MAKEFILE "Enable verbose output" ON)
option(CMAKE_EXPORT_COMPILE_COMMANDS "Export compile commands for linters and autocompleters" ON)

project(main LANGUAGES CXX)

option(ADDRESS_SANITIZER "Enable address sanitizer" OFF)

set(CMAKE_CXX_STANDARD
    11
    CACHE STRING "The C++ standard to use")

set(ROCM_DIR "/opt/rocm" CACHE STRING "ROCm directory.")
set(RSMI_SRC_DIR "/home/dgalants/git/repo/external/rocm_smi_lib/include/" CACHE STRING "ROCm directory.")

find_package(RSMI
    NAMES rocm_smi
    HINTS ${ROCM_DIR}/lib/cmake
    CONFIGURE REQUIRED)

# Include CMAKE_INSTALL_* variables
# this must go after project()
include(GNUInstallDirs)

add_subdirectory(functions)
add_executable(main main.cpp)
target_include_directories(main PUBLIC "${RSMI_SRC_DIR}" "${RSMI_SRC_DIR}/../third_party/shared_mutex/")
target_link_libraries(main rocm_smi64)

### Useful debug stuff

### TODO: DELETE
# print variables
include(CMakePrintHelpers)
cmake_print_variables(CMAKE_CXX_STANDARD)
# function to print vars
function(print)
    message("--")
    cmake_print_variables(${ARGN})
endfunction()
function(print_fatal)
    print(${ARGN})
    message(FATAL_ERROR "--- last print")
endfunction()
### TODO: DELETE

# print properties
cmake_print_properties(TARGETS main
    PROPERTIES
    INCLUDE_DIRECTORIES
    LINK_LIBRARIES)
cmake_print_properties(SOURCES main
    PROPERTIES
    LOCATION)

# trace a run
# trace CMakeLists.txt line-by-line:
#       cmake -B build --trace-source=CMakeLists.txt
# add '--trace-expand' to expand the variables

### Finding packages

# add package search paths
#set(CMAKE_PREFIX_PATH
#    ${CMAKE_PREFIX_PATH}
#    /usr/local
#    )
#set(CMAKE_LIBRARY_PATH
#    ${CMAKE_LIBRARY_PATH}
#    /usr/lib64
#    /usr/lib/x86_64-linux-gnu
#    )

# find lib
#find_library(LIB_CAP
#    NAMES cap
#    REQUIRED)

# find package (preferred!)
#find_package(protobuf
#    HINTS ${GRPC_ROOT}
#    CONFIG REQUIRED)
#find_package(gRPC ${GRPC_DESIRED_VERSION}
#    HINTS ${GRPC_ROOT}
#    CONFIG REQUIRED)

