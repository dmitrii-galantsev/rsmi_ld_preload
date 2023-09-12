/*
 * This file showcases different ways of accessing a variable
 */

#include <string>

#include <dlfcn.h>
#include <unistd.h>
#include <array>
#include <iostream>

#include "functions.hpp"
#include "rocm_smi/rocm_smi_device.h"
#include "rocm_smi/rocm_smi_utils.h"
//#include "rocm_smi/rocm_smi_monitor.h"

#define PUBLIC __attribute__((__visibility__("default")))

// int SameFile(const std::string fileA, const std::string fileB);
int (*same_file_real)(const std::string fileA, const std::string fileB);

void* lookup_symbol(const char* name) {
    void* symbol;
    const char* error;

    // auto my_open = dlopen("/opt/rocm-dev2/lib/librocm_smi64.so", RTLD_LAZY);
    symbol = dlsym(RTLD_NEXT, name);
    if ((error = dlerror())) {
        printf("dlsym(%s) failed: %s", name, error);
        exit(1);
    }

    return symbol;
}

PUBLIC void amd::smi::Device::fillSupportedFuncs(void) {
    printf("FAKE fillSupportedFuncs\n");
    return;
}

PUBLIC int amd::smi::SameFile(
    const std::string fileA,
    const std::string fileB) {
    same_file_real =
        reinterpret_cast<int (*)(const std::string, const std::string)>(
            lookup_symbol("_ZN3amd3smi8SameFileENSt7__cxx1112basic_"
                          "stringIcSt11char_traitsIcESaIcEEES6_"));
    int hm = same_file_real(fileA, fileB);
    printf("ACTUAL RETURN: %d\n", hm);
    printf("FAKE RETURN: %d\n", 42);
    return 42;
}
