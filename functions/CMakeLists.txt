cmake_minimum_required(VERSION 3.11)

find_package(RSMI
    NAMES rocm_smi
    HINTS ${ROCM_DIR}/lib/cmake
    CONFIGURE REQUIRED)
set(RSMI_INC_DIR "${ROCM_SMI_INCLUDE_DIR}" CACHE INTERNAL "ROCm SMI include directory.")
set(RSMI_LIB_DIR "${ROCM_SMI_LIB_DIR}" CACHE INTERNAL "ROCm SMI library directory.")

set(SOURCES functions.hpp functions.cpp ${RSMI_INC_DIR}/rocm_smi.h)

add_library(functions_lib STATIC ${SOURCES})
target_link_libraries(functions_lib rocm_smi64)
target_compile_options(functions_lib PUBLIC -Wall -pedantic -Wextra -Wconversion -Wsign-conversion)
