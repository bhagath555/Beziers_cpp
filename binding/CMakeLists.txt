
file(GLOB PYBIND_CPP_SOURCE "../src/*.cpp")

pybind11_add_module(bezier ${PYBIND_CPP_SOURCE})