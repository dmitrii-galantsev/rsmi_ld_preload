#include <unistd.h>
#include <array>
#include <iostream>
// #include "functions/functions.hpp"
#include "rocm_smi/rocm_smi_device.h"
#include "rocm_smi/rocm_smi_utils.h"

int main() {
    int same =
        amd::smi::SameFile("/home/dgalants/.bashrc", "/home/dgalants/.bashrc");
    printf("Are the files the same: %d\n", same);

    auto device = amd::smi::Device("/dev/tmp", nullptr);
    device.fillSupportedFuncs();

    return 0;
}
