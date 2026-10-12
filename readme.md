# Clothoids
This repo was made to cleanup the compilation process of [Enrico Bertolazzi Clothoids](https://github.com/ebertolazzi/Clothoids).

This repository uses git submodules to keep always a stable version.

## Clone the repo with submodules

```bash
git clone --recurse-submodules https://github.com/Pippo98/clothoids
```

## Install the Python bindings with pip
Directly from GitHub (pip fetches the submodules on its own):
```bash
pip install git+https://github.com/Pippo98/clothoids
```

Or from a local clone (cloned with `--recurse-submodules`):
```bash
pip install .
```

A C++17 compiler is required; CMake is downloaded automatically if the installed one is too old.
```python
import py_clothoids

cl = py_clothoids.ClothoidList("my_curve")
cl.build_G1(4, [0, 1, 2, 3], [0, 1, 0, 1])
print(cl.length(), cl.evaluate(0.5))
```

## Compile this single project
```
cmake -B build
cmake --build build
```

## Compile as external module
If you want to integrate the clothoids in your CMake project, you should add this repository as submodule in your project to make it available to CMake, then:
```cmake
# ...
add_subdirectory(external/clothiods) # this is the case if this repo is placed in the "external" subdirectory
target_link_libraries(
my_executable_or_library
    PUBLIC
    clothoids # this is the name of the library compiled in this repository
)
```

By default this project compiles a static library, however if you want to change the library type you can set the `SET_CLOTHOID_LIB_TYPE` variable in two ways:
1. From command line: `cmake -B build -DSET_CLOTHOID_LIB_TYPE=SHARED`
2. Directly in cmake by adding `set(SET_CLOTHOID_LIB_TYPE SHARED)` before the line `add_subdirectory`.


