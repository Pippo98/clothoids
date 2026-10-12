if(CLOTHOIDS_BUILD_PYTHON_BINDINGS)
  set(PYBIND11_FINDPYTHON ON)
  add_subdirectory(py/pybind11)
  pybind11_add_module(py_clothoids MODULE py/bindings.cpp)
  target_link_libraries(py_clothoids PUBLIC clothoids)
  target_compile_options(py_clothoids PUBLIC -std=c++17)
  # Compiled module lives inside the py_clothoids package (py/py_clothoids)
  set_target_properties(py_clothoids PROPERTIES OUTPUT_NAME _core)

  # Used by scikit-build-core (pip install .) to place the module in the wheel
  install(TARGETS py_clothoids LIBRARY DESTINATION py_clothoids COMPONENT python)
endif()
