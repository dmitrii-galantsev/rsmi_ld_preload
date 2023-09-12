cmake_minimum_required(VERSION 3.11)

set(SOURCES functions.hpp functions.cpp
    #${ROCM_SMI_INCLUDE_DIR}/rocm_smi/rocm_smi.h
    ${RSMI_SRC_DIR}/rocm_smi/rocm_smi_utils.h
    )

add_library(functions_lib SHARED ${SOURCES})
target_link_libraries(functions_lib rocm_smi64)
target_include_directories(functions_lib PUBLIC "${RSMI_SRC_DIR}" "${RSMI_SRC_DIR}/../third_party/shared_mutex/")
target_compile_options(functions_lib PUBLIC -Wall -pedantic -Wextra -Wconversion -Wsign-conversion)
