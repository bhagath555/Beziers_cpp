#include<pybind11/pybind11.h>
#include<pybind11/stl.h>
#include "bezier.h"

namespace py = pybind11;

PYBIND11_MODULE(bezier, m) {

    m.def("VectDotProduct", &VectDotProduct);
    m.def("RandomMatrix", &RandomMatrix, 
        "Generates the random matrix of size n*m");

    py::class_<bezier>(m, "bezier")
        .def(py::init())
        .def(py::init([](int p) {return new bezier(p); }))
        .def(py::init([](const matrix& cps_in) {return new bezier(cps_in);}))

        .def("ith_basis", &bezier::ith_basis)

        .def("basis", static_cast<vect (bezier::*) (float)>
             (&bezier::basis))

        .def("basis", static_cast<matrix (bezier::*) (float, float, int)>
             (&bezier::basis))

        .def("evaluate", static_cast<vect (bezier::*) (float)> 
            (&bezier::evaluate))
        
        .def("evaluate", static_cast<matrix (bezier::*) (float, float, int)>
            (&bezier::evaluate))

        .def("evaluate_crv", &bezier::evaluate_crv) 
        .def("get_ctrl_pnts", &bezier::get_ctrl_pnts)
        
        .def("display", &bezier::display)
   
    ;

}