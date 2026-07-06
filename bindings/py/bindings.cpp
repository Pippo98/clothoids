#include <pybind11/detail/common.h>
#include <pybind11/eigen.h>
#include <pybind11/iostream.h>
#include <pybind11/pytypes.h>
#include <pybind11/stl.h>

#include "Clothoids.hh"

namespace py = pybind11;

using namespace G2lib;
typedef ClothoidList CL;
typedef std::vector<double> vecd;

bool build_G1_xy(CL &cl, const integer n, const vecd x, const vecd y) {
  return cl.build_G1(n, x.data(), y.data());
}
bool build_G1_xy_theta(CL &cl, const integer n, const vecd x, const vecd y,
                       const vecd theta) {
  return cl.build_G1(n, x.data(), y.data(), theta.data());
}

bool build_G2_xy_theta(CL &cl, integer const n, const vecd x, const vecd y,
                       const real_type theta_init, const real_type theta_end) {
  return cl.build_G2(n, x.data(), y.data(), theta_init, theta_end);
}
bool build_G2_xy_theta_kappa(CL &cl, const integer n, const vecd x,
                             const vecd y, const real_type theta_init,
                             const real_type kappa_init,
                             const real_type theta_end,
                             const real_type kappa_end) {
  return cl.build_G2(n, x.data(), y.data(), theta_init, kappa_init, theta_end,
                     kappa_end);
}
bool build_G2_cyclic(CL &cl, const integer n, const vecd x, const vecd y) {
  return cl.build_G2_cyclic(n, x.data(), y.data());
}

bool build_raw(CL &cl, const vecd x, const vecd y, const vecd abscissa,
               const vecd theta, const vecd kappa) {
  return cl.build_raw(x, y, abscissa, theta, kappa);
}

const auto evaluate_ISO = [](CL &cl, const real_type s, const real_type offs) {
  static py::object Result =
      py::module_::import("collections")
          .attr("namedtuple")("Result", py::make_tuple("th", "k", "x", "y"));
  real_type th, k, x, y;
  cl.evaluate_ISO(s, offs, th, k, x, y);
  return Result(th, k, x, y);
};
const auto evaluate = [](CL &cl, const real_type s) {
  static py::object Result =
      py::module_::import("collections")
          .attr("namedtuple")("Result", py::make_tuple("th", "k", "x", "y"));
  real_type th, k, x, y;
  cl.evaluate(s, th, k, x, y);
  return Result(th, k, x, y);
};

const auto closest_point_ISO = [](CL &cl, const real_type qx,
                                  const real_type qy) {
  static py::object Result =
      py::module_::import("collections")
          .attr("namedtuple")("Result",
                              py::make_tuple("x", "y", "s", "t", "dst", "n"));
  real_type x, y, s, t, dst, n;
  n = cl.closest_point_ISO(qx, qy, x, y, s, t, dst);
  return Result(x, y, s, t, dst, n);
};
const auto closest_point_ISO_off = [](CL &cl, const real_type qx,
                                      const real_type qy, const real_type off) {
  static py::object Result =
      py::module_::import("collections")
          .attr("namedtuple")("Result",
                              py::make_tuple("x", "y", "s", "t", "dst", "n"));
  real_type x, y, s, t, dst, n;
  n = cl.closest_point_ISO(qx, qy, off, x, y, s, t, dst);
  return Result(x, y, s, t, dst, n);
};

const auto closest_point_in_s_range_ISO =
    [](CL &cl, real_type const qx, real_type const qy, real_type const s_begin,
       real_type const s_end) {
      static py::object Result =
          py::module_::import("collections")
              .attr("namedtuple")("Result",
                                  py::make_tuple("x", "y", "s", "t", "dst",
                                                 "i_curve", "success"));
      real_type x, y, s, t, dst;
      integer i_curve, success;
      success = cl.closest_point_in_s_range_ISO(qx, qy, s_begin, s_end, x, y, s,
                                                t, dst, i_curve);
      return Result(x, y, s, t, dst, i_curve, success);
    };

PYBIND11_MODULE(py_clothoids, m) {
  m.doc() =
      "TireX Python Bindings. This module provides access to the TireX "
      "library. It is wrapping the C++ classes and functions using pybind11.";
  py::class_<CL>(m, "ClothoidList")
      .def(py::init<std::string>())
      .def("init", &CL::init, "Initialize the clothoid list")
      .def("reserve", &CL::reserve, "Reverve memory for n clothoids")
      .def("is_closed", &CL::is_closed, "Return true if curve is closed")
      .def("make_closed", &CL::make_closed, "Set closed flag to true")
      .def("make_open", &CL::make_open, "Set closure flag to false")
      // BUILD
      .def("build_G1", build_G1_xy,
           "Build G1 clothoid passing a list of xy coordinates")
      .def("build_G1", build_G1_xy_theta,
           "Build G1 clothoid passing a list of xy coordinates and the "
           "corresponding angle at that point")
      .def("build_G2", build_G2_xy_theta,
           "Constructs a smooth open curve passing through the specified "
           "points, starting with a given orientation and curvature, and "
           "ending with the prescribed final orientation and curvature. The "
           "resulting clothoid list ensures continuous position, tangent, and "
           "curvature along the entire path.")
      .def("build_G2", build_G2_xy_theta_kappa,
           "Constructs a smooth open curve passing through the specified "
           "points, starting with a given orientation and curvature, and "
           "ending with the prescribed final orientation and curvature. The "
           "resulting clothoid list ensures continuous position, tangent, "
           "and curvature along the entire path.")
      .def("build_G2_cyclic", build_G2_cyclic,
           "Creates a closed sequence of clothoid segments ensuring continuous "
           "position, tangent, and curvature between consecutive points.")
      .def("build_raw", build_raw, "Build clothoid list using raw data")
      // LENGTH
      .def("length", &CL::length)
      .def("length_ISO", &CL::length_ISO)
      .def("length_SAE", &CL::length_SAE)
      // BEGIN-END
      .def("theta_begin", &CL::theta_begin)
      .def("theta_end", &CL::theta_end)
      .def("x_begin", &CL::x_begin)
      .def("y_begin", &CL::y_begin)
      .def("x_end", &CL::x_end)
      .def("y_end", &CL::y_end)
      .def("x_begin_ISO", &CL::x_begin_ISO)
      .def("y_begin_ISO", &CL::y_begin_ISO)
      .def("x_end_ISO", &CL::x_end_ISO)
      .def("y_end_ISO", &CL::y_end_ISO)
      .def("tx_begin", &CL::tx_begin)
      .def("ty_begin", &CL::ty_begin)
      .def("tx_end", &CL::tx_end)
      .def("ty_end", &CL::ty_end)
      .def("nx_begin_ISO", &CL::nx_begin_ISO)
      .def("ny_begin_ISO", &CL::ny_begin_ISO)
      .def("nx_end_ISO", &CL::nx_end_ISO)
      .def("ny_end_ISO", &CL::ny_end_ISO)
      // THETA
      .def("theta",
           [](CL &cl, const real_type &s) -> real_type { return cl.theta(s); })
      .def("theta_D", &CL::theta_D)
      .def("theta_DD", &CL::theta_DD)
      .def("theta_DDD", &CL::theta_DDD)
      // TX-TY
      .def("tx",
           [](CL &cl, const real_type &s) -> real_type { return cl.tx(s); })
      .def("ty",
           [](CL &cl, const real_type &s) -> real_type { return cl.ty(s); })
      .def("tx_D", &CL::tx_D)
      .def("ty_D", &CL::ty_D)
      .def("tx_DD", &CL::tx_DD)
      .def("ty_DD", &CL::ty_DD)
      .def("tx_DDD", &CL::tx_DDD)
      .def("ty_DDD", &CL::ty_DDD)
      // TG
      .def("tg", &CL::tg)
      .def("tg_D", &CL::tg_D)
      .def("tg_DD", &CL::tg_DD)
      .def("tg_DDD", &CL::tg_DDD)
      // EVALUATE
      .def("evaluate", evaluate)
      .def("evaluate_ISO", evaluate_ISO)
      // X-Y
      .def("X", [](CL &cl, const real_type &s) -> real_type { return cl.X(s); })
      .def("Y", [](CL &cl, const real_type &s) -> real_type { return cl.Y(s); })
      .def("X_D", &CL::X_D)
      .def("Y_D", &CL::Y_D)
      .def("X_DD", &CL::X_DD)
      .def("Y_DD", &CL::Y_DD)
      .def("X_DDD", &CL::X_DDD)
      .def("Y_DDD", &CL::Y_DDD)
      // CLOSEST POINT
      .def("closest_point_ISO", closest_point_ISO)
      .def("closest_point_ISO", closest_point_ISO_off)
      .def("closest_point_in_s_range_ISO", closest_point_in_s_range_ISO);
}
