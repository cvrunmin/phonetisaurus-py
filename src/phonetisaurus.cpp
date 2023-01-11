#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "include/PhonetisaurusScript.h"

namespace py = pybind11;

PYBIND11_MODULE(phonetisaurus, m) {
    py::class_<PathData>(m, "PathData")
    .def(py::init<>())
    .def(py::init<float, const std::vector<float>&, const std::vector<int>&, const std::vector<int>&, const std::vector<int>&>())
    .def_readwrite("path_weight", &PathData::PathWeight)
    .def_readwrite("path_weights", &PathData::PathWeights)
    .def_readwrite("input_labels", &PathData::ILabels)
    .def_readwrite("output_labels", &PathData::OLabels)
    .def_readwrite("uniques", &PathData::Uniques);
    py::class_<PhonetisaurusScript>(m, "PhonetisaurusModel")
    .def(py::init<std::string, std::string, std::optional<std::vector<int>>, int, int>(),
        "create an instance of Phonetisaurus wrapper",
        py::arg("model_path"),
        py::arg_v("delim", "", "delimiter"),
        py::arg_v("vetoSet", std::nullopt, "None"),
        py::arg("isym_tie") = 1,
        py::arg("osym_tie") = 1)
    .def("phoneticize", &PhonetisaurusScript::Phoneticize, "phoneticize a given words",
        py::arg("word"),
        py::arg("nbest") = 1,
        py::arg("beam") = 10000,
        py::arg("threshold") = 99,
        py::arg("write_fsts") = false,
        py::arg("accumulate") = false,
        py::arg("pmass") = 99.0
    )
    .def("is_filtering", &PhonetisaurusScript::IsFiltering)
    .def("find_isym", py::overload_cast<int>(&PhonetisaurusScript::FindIsym))
    .def("find_isym", py::overload_cast<const std::string&>(&PhonetisaurusScript::FindIsym))
    .def("find_osym", py::overload_cast<int>(&PhonetisaurusScript::FindOsym))
    .def("find_osym", py::overload_cast<const std::string&>(&PhonetisaurusScript::FindOsym));
}
