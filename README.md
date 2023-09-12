# This is a WIP C++ template repository

### How to compile
1. `cmake -B build`
2. `make -C build -j $(nproc)`

### How to run
- `./build/main`
- `LD_PRELOAD='build/functions/libfunctions_lib.so' ./build/main`
