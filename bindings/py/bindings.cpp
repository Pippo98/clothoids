#include <pybind11/detail/common.h>
#include <pybind11/eigen.h>
#include <pybind11/iostream.h>
#include <pybind11/pytypes.h>
#include <pybind11/stl.h>

#include <sstream>
#include <iterator>
#include <stdexcept>
#include <string>
#include <utility>

#include "Clothoids.hh"

namespace py = pybind11;
using namespace pybind11::literals;

using namespace G2lib;
typedef ClothoidList CL;
typedef std::vector<double> vecd;

// ================================= //
// Result types
//
// Plain structs exposed as read-only classes so that IDEs and type checkers
// know their fields. They also behave like tuples, so they can be unpacked:
//   th, k, x, y = cl.evaluate(s)

struct EvalResult {
  static constexpr const char *name = "EvalResult";
  static constexpr const char *fields[] = {"th", "k", "x", "y"};
  real_type th, k, x, y;
  py::tuple as_tuple() const { return py::make_tuple(th, k, x, y); }
};

struct ClosestPointResult {
  static constexpr const char *name = "ClosestPointResult";
  static constexpr const char *fields[] = {"x", "y", "s", "t", "dst", "n"};
  real_type x, y, s, t, dst;
  integer n;
  py::tuple as_tuple() const { return py::make_tuple(x, y, s, t, dst, n); }
};

struct ClosestPointInRangeResult {
  static constexpr const char *name = "ClosestPointInRangeResult";
  static constexpr const char *fields[] = {"x",   "y",       "s",      "t",
                                           "dst", "i_curve", "success"};
  real_type x, y, s, t, dst;
  integer i_curve, success;
  py::tuple as_tuple() const {
    return py::make_tuple(x, y, s, t, dst, i_curve, success);
  }
};

template <typename T> void add_tuple_protocol(py::class_<T> &cls) {
  cls.def(
         "__iter__",
         [](const T &r) { return py::iter(r.as_tuple()); },
         "Iterate over the fields, allows tuple unpacking.")
      .def("__len__", [](const T &) { return std::size(T::fields); })
      .def("__getitem__",
           [](const T &r, const py::object &i) {
             return r.as_tuple().attr("__getitem__")(i);
           })
      .def("__repr__", [](const T &r) {
        std::ostringstream os;
        py::tuple values = r.as_tuple();
        os << T::name << "(";
        for (size_t i = 0; i < std::size(T::fields); ++i) {
          os << (i ? ", " : "") << T::fields[i] << "="
             << py::repr(values[i]).cast<std::string>();
        }
        os << ")";
        return os.str();
      });
}

// ================================= //
// Wrappers

// The C++ API takes raw pointers plus a size: make sure we never read past
// the end of the Python sequences.
void check_size(const integer n, const vecd &v, const char *name) {
  if (n < 0 || static_cast<size_t>(n) > v.size()) {
    throw py::value_error("n = " + std::to_string(n) + " but len(" + name +
                          ") = " + std::to_string(v.size()));
  }
}

bool build_G1_xy(CL &cl, const integer n, const vecd &x, const vecd &y) {
  check_size(n, x, "x");
  check_size(n, y, "y");
  return cl.build_G1(n, x.data(), y.data());
}
bool build_G1_xy_theta(CL &cl, const integer n, const vecd &x, const vecd &y,
                       const vecd &theta) {
  check_size(n, x, "x");
  check_size(n, y, "y");
  check_size(n, theta, "theta");
  return cl.build_G1(n, x.data(), y.data(), theta.data());
}

bool build_G2_xy_theta(CL &cl, integer const n, const vecd &x, const vecd &y,
                       const real_type theta_init, const real_type theta_end) {
  check_size(n, x, "x");
  check_size(n, y, "y");
  return cl.build_G2(n, x.data(), y.data(), theta_init, theta_end);
}
bool build_G2_xy_theta_kappa(CL &cl, const integer n, const vecd &x,
                             const vecd &y, const real_type theta_init,
                             const real_type kappa_init,
                             const real_type theta_end,
                             const real_type kappa_end) {
  check_size(n, x, "x");
  check_size(n, y, "y");
  return cl.build_G2(n, x.data(), y.data(), theta_init, kappa_init, theta_end,
                     kappa_end);
}
bool build_G2_cyclic(CL &cl, const integer n, const vecd &x, const vecd &y) {
  check_size(n, x, "x");
  check_size(n, y, "y");
  return cl.build_G2_cyclic(n, x.data(), y.data());
}

bool build_raw(CL &cl, const vecd &x, const vecd &y, const vecd &abscissa,
               const vecd &theta, const vecd &kappa) {
  return cl.build_raw(x, y, abscissa, theta, kappa);
}

EvalResult evaluate(const CL &cl, const real_type s) {
  EvalResult r;
  cl.evaluate(s, r.th, r.k, r.x, r.y);
  return r;
}
EvalResult evaluate_ISO(const CL &cl, const real_type s, const real_type offs) {
  EvalResult r;
  cl.evaluate_ISO(s, offs, r.th, r.k, r.x, r.y);
  return r;
}

using Vec2 = std::pair<real_type, real_type>;
Vec2 tg(const CL &cl, const real_type s) {
  Vec2 v;
  cl.tg(s, v.first, v.second);
  return v;
}
Vec2 tg_D(const CL &cl, const real_type s) {
  Vec2 v;
  cl.tg_D(s, v.first, v.second);
  return v;
}
Vec2 tg_DD(const CL &cl, const real_type s) {
  Vec2 v;
  cl.tg_DD(s, v.first, v.second);
  return v;
}
Vec2 tg_DDD(const CL &cl, const real_type s) {
  Vec2 v;
  cl.tg_DDD(s, v.first, v.second);
  return v;
}

ClosestPointResult closest_point_ISO(const CL &cl, const real_type qx,
                                     const real_type qy) {
  ClosestPointResult r;
  r.n = cl.closest_point_ISO(qx, qy, r.x, r.y, r.s, r.t, r.dst);
  return r;
}
ClosestPointResult closest_point_ISO_off(const CL &cl, const real_type qx,
                                         const real_type qy,
                                         const real_type offs) {
  ClosestPointResult r;
  r.n = cl.closest_point_ISO(qx, qy, offs, r.x, r.y, r.s, r.t, r.dst);
  return r;
}

ClosestPointInRangeResult
closest_point_in_s_range_ISO(const CL &cl, real_type const qx,
                             real_type const qy, real_type const s_begin,
                             real_type const s_end) {
  ClosestPointInRangeResult r;
  r.success = cl.closest_point_in_s_range_ISO(qx, qy, s_begin, s_end, r.x, r.y,
                                              r.s, r.t, r.dst, r.i_curve);
  return r;
}

// ================================= //
// Docstrings

static const char *DOC_BUILD_G1_XY = R"doc(Build the clothoid list passing through a list of points, solving a series
of G1 fitting problems. The angles at the points are estimated automatically.

Args:
    n: Number of points.
    x: x-coordinates of the points.
    y: y-coordinates of the points.

Returns:
    False if the construction fails.
)doc";

static const char *DOC_BUILD_G1_XY_THETA = R"doc(Build the clothoid list passing through a list of points with the given
angles, solving a series of G1 fitting problems.

Args:
    n: Number of points.
    x: x-coordinates of the points.
    y: y-coordinates of the points.
    theta: Angles (radians) at the points.

Returns:
    False if the construction fails.
)doc";

static const char *DOC_BUILD_G2 = R"doc(Build a sequence of clothoid arcs interpolating the points with G2
(curvature) continuity. The curve starts and ends with the given angles.

Args:
    n: Number of points to interpolate.
    x: x-coordinates of the points.
    y: y-coordinates of the points.
    theta_init: Initial angle (radians).
    theta_end: Final angle (radians).

Returns:
    True if the construction succeeds, False otherwise (e.g. degenerate or
    inconsistent input data).
)doc";

static const char *DOC_BUILD_G2_KAPPA = R"doc(Build a sequence of clothoid arcs interpolating the points with G2
(curvature) continuity. The curve starts and ends with the given angles and
curvatures.

Args:
    n: Number of points to interpolate.
    x: x-coordinates of the points.
    y: y-coordinates of the points.
    theta_init: Initial angle (radians).
    kappa_init: Initial curvature (1/length units).
    theta_end: Final angle (radians).
    kappa_end: Final curvature (1/length units).

Returns:
    True if the construction succeeds, False otherwise (e.g. degenerate or
    inconsistent input data).
)doc";

static const char *DOC_BUILD_G2_CYCLIC = R"doc(Build a closed sequence of clothoid arcs interpolating the points with G2
continuity: position, tangent and curvature are continuous everywhere,
including between the last and the first point.

Args:
    n: Number of points (at least 3).
    x: x-coordinates of the points.
    y: y-coordinates of the points.

Returns:
    True if the construction succeeds, False otherwise.
)doc";

static const char *DOC_BUILD_RAW = R"doc(Build the clothoid list from raw data. All the lists must have the same
length.

Args:
    x: x-coordinates of the break points.
    y: y-coordinates of the break points.
    abscissa: Curvilinear abscissa of the break points.
    theta: Angles at the break points.
    kappa: Curvatures at the break points.

Returns:
    False if the construction fails.
)doc";

static const char *DOC_EVALUATE = R"doc(Evaluate the curve at curvilinear coordinate ``s``.

Args:
    s: Curvilinear coordinate.

Returns:
    Angle ``th``, curvature ``k`` and position ``x``, ``y``.
)doc";

static const char *DOC_EVALUATE_ISO = R"doc(Evaluate the offset curve (ISO convention) at curvilinear coordinate ``s``.

Args:
    s: Curvilinear coordinate.
    offs: Offset from the curve.

Returns:
    Angle ``th``, curvature ``k`` and position ``x``, ``y``.
)doc";

static const char *DOC_CLOSEST_POINT_ISO = R"doc(Find the point on the curve closest to the point (qx, qy).

Args:
    qx: x-coordinate of the point.
    qy: y-coordinate of the point.

Returns:
    ``x``, ``y``: the projected point on the curve.
    ``s``: curvilinear coordinate of the projection.
    ``t``: signed distance (ISO) of (qx, qy) from the curve, if the
    projection is orthogonal.
    ``dst``: distance between (qx, qy) and the projected point.
    ``n``: if >= 0 the projection is orthogonal and ``n`` is the index of the
    segment at minimum distance, otherwise the projection is not orthogonal
    and the segment is ``-(n + 1)``.
)doc";

static const char *DOC_CLOSEST_POINT_ISO_OFF = R"doc(Find the point on the offset curve (ISO convention) closest to the point
(qx, qy).

Args:
    qx: x-coordinate of the point.
    qy: y-coordinate of the point.
    offs: Offset of the curve.

Returns:
    ``x``, ``y``: the projected point on the curve.
    ``s``: curvilinear coordinate of the projection.
    ``t``: signed distance (ISO) of (qx, qy) from the curve, if the
    projection is orthogonal.
    ``dst``: distance between (qx, qy) and the projected point.
    ``n``: if >= 0 the projection is orthogonal and ``n`` is the index of the
    segment at minimum distance, otherwise the projection is not orthogonal
    and the segment is ``-(n + 1)``.
)doc";

static const char *DOC_CLOSEST_POINT_IN_S_RANGE_ISO = R"doc(Find the point on the curve closest to the point (qx, qy), searching only
for curvilinear coordinates between ``s_begin`` and ``s_end``.

Args:
    qx: x-coordinate of the point.
    qy: y-coordinate of the point.
    s_begin: Initial curvilinear coordinate of the search range.
    s_end: Final curvilinear coordinate of the search range.

Returns:
    ``x``, ``y``: the projected point on the curve.
    ``s``: curvilinear coordinate of the projection.
    ``t``: signed distance (ISO) of (qx, qy) from the curve, if the
    projection is orthogonal.
    ``dst``: distance between (qx, qy) and the projected point.
    ``i_curve``: index of the segment containing the projected point.
    ``success``: 1 if the projection is orthogonal, 0 if there is more than
    one projection (the first is returned), -1 if the projection failed.
)doc";

// ================================= //

PYBIND11_MODULE(_core, m) {
  m.doc() =
      "Clothoids Python Bindings. This module provides access to the Clothoids "
      "library. It is wrapping the C++ classes and functions using pybind11.";

  py::class_<EvalResult> eval_result(
      m, "EvalResult", "Result of ClothoidList.evaluate / evaluate_ISO.");
  eval_result.def_readonly("th", &EvalResult::th, "Angle (radians).")
      .def_readonly("k", &EvalResult::k, "Curvature.")
      .def_readonly("x", &EvalResult::x, "x-coordinate.")
      .def_readonly("y", &EvalResult::y, "y-coordinate.");
  add_tuple_protocol(eval_result);

  py::class_<ClosestPointResult> closest_point_result(
      m, "ClosestPointResult", "Result of ClothoidList.closest_point_ISO.");
  closest_point_result
      .def_readonly("x", &ClosestPointResult::x,
                    "x-coordinate of the projected point.")
      .def_readonly("y", &ClosestPointResult::y,
                    "y-coordinate of the projected point.")
      .def_readonly("s", &ClosestPointResult::s,
                    "Curvilinear coordinate of the projection.")
      .def_readonly("t", &ClosestPointResult::t,
                    "Signed distance (ISO) from the curve.")
      .def_readonly("dst", &ClosestPointResult::dst,
                    "Distance from the projected point.")
      .def_readonly("n", &ClosestPointResult::n,
                    "Segment index if >= 0 (orthogonal projection), "
                    "-(segment + 1) otherwise.");
  add_tuple_protocol(closest_point_result);

  py::class_<ClosestPointInRangeResult> closest_point_in_range_result(
      m, "ClosestPointInRangeResult",
      "Result of ClothoidList.closest_point_in_s_range_ISO.");
  closest_point_in_range_result
      .def_readonly("x", &ClosestPointInRangeResult::x,
                    "x-coordinate of the projected point.")
      .def_readonly("y", &ClosestPointInRangeResult::y,
                    "y-coordinate of the projected point.")
      .def_readonly("s", &ClosestPointInRangeResult::s,
                    "Curvilinear coordinate of the projection.")
      .def_readonly("t", &ClosestPointInRangeResult::t,
                    "Signed distance (ISO) from the curve.")
      .def_readonly("dst", &ClosestPointInRangeResult::dst,
                    "Distance from the projected point.")
      .def_readonly("i_curve", &ClosestPointInRangeResult::i_curve,
                    "Index of the segment containing the projected point.")
      .def_readonly("success", &ClosestPointInRangeResult::success,
                    "1 orthogonal projection, 0 more than one projection, "
                    "-1 failed.");
  add_tuple_protocol(closest_point_in_range_result);

  py::class_<CL>(m, "ClothoidList",
                 "A list of clothoid segments forming a piecewise curve.")
      .def(py::init<std::string>(), "name"_a,
           "Build an empty clothoid list with the given name.")
      .def("init", &CL::init, "Reset the clothoid list, removing all segments.")
      .def("reserve", &CL::reserve, "n"_a,
           "Reserve memory for ``n`` clothoids.")
      .def("is_closed", &CL::is_closed, "Return True if the curve is closed.")
      .def("make_closed", &CL::make_closed, "Mark the curve as closed.")
      .def("make_open", &CL::make_open, "Mark the curve as open.")
      // BUILD
      .def("build_G1", build_G1_xy, "n"_a, "x"_a, "y"_a, DOC_BUILD_G1_XY)
      .def("build_G1", build_G1_xy_theta, "n"_a, "x"_a, "y"_a, "theta"_a,
           DOC_BUILD_G1_XY_THETA)
      .def("build_G2", build_G2_xy_theta, "n"_a, "x"_a, "y"_a, "theta_init"_a,
           "theta_end"_a, DOC_BUILD_G2)
      .def("build_G2", build_G2_xy_theta_kappa, "n"_a, "x"_a, "y"_a,
           "theta_init"_a, "kappa_init"_a, "theta_end"_a, "kappa_end"_a,
           DOC_BUILD_G2_KAPPA)
      .def("build_G2_cyclic", build_G2_cyclic, "n"_a, "x"_a, "y"_a,
           DOC_BUILD_G2_CYCLIC)
      .def("build_raw", build_raw, "x"_a, "y"_a, "abscissa"_a, "theta"_a,
           "kappa"_a, DOC_BUILD_RAW)
      // LENGTH
      .def("length", &CL::length, "Length of the curve.")
      .def("length_ISO", &CL::length_ISO, "offs"_a,
           "Length of the curve with offset ``offs`` (ISO convention).")
      .def("length_SAE", &CL::length_SAE, "offs"_a,
           "Length of the curve with offset ``offs`` (SAE convention).")
      // BEGIN-END
      .def("theta_begin", &CL::theta_begin, "Initial angle of the curve.")
      .def("theta_end", &CL::theta_end, "Final angle of the curve.")
      .def("x_begin", &CL::x_begin, "Initial x-coordinate.")
      .def("y_begin", &CL::y_begin, "Initial y-coordinate.")
      .def("x_end", &CL::x_end, "Final x-coordinate.")
      .def("y_end", &CL::y_end, "Final y-coordinate.")
      .def("x_begin_ISO", &CL::x_begin_ISO, "offs"_a,
           "Initial x-coordinate with offset ``offs`` (ISO convention).")
      .def("y_begin_ISO", &CL::y_begin_ISO, "offs"_a,
           "Initial y-coordinate with offset ``offs`` (ISO convention).")
      .def("x_end_ISO", &CL::x_end_ISO, "offs"_a,
           "Final x-coordinate with offset ``offs`` (ISO convention).")
      .def("y_end_ISO", &CL::y_end_ISO, "offs"_a,
           "Final y-coordinate with offset ``offs`` (ISO convention).")
      .def("tx_begin", &CL::tx_begin, "Initial tangent x-coordinate.")
      .def("ty_begin", &CL::ty_begin, "Initial tangent y-coordinate.")
      .def("tx_end", &CL::tx_end, "Final tangent x-coordinate.")
      .def("ty_end", &CL::ty_end, "Final tangent y-coordinate.")
      .def("nx_begin_ISO", &CL::nx_begin_ISO,
           "Initial normal x-coordinate (ISO convention).")
      .def("ny_begin_ISO", &CL::ny_begin_ISO,
           "Initial normal y-coordinate (ISO convention).")
      .def("nx_end_ISO", &CL::nx_end_ISO,
           "Final normal x-coordinate (ISO convention).")
      .def("ny_end_ISO", &CL::ny_end_ISO,
           "Final normal y-coordinate (ISO convention).")
      // THETA
      .def(
          "theta",
          [](CL &cl, const real_type &s) -> real_type { return cl.theta(s); },
          "s"_a, "Angle at curvilinear coordinate ``s``.")
      .def("theta_D", &CL::theta_D, "s"_a,
           "Angle derivative (curvature) at curvilinear coordinate ``s``.")
      .def("theta_DD", &CL::theta_DD, "s"_a,
           "Angle second derivative (derivative of curvature) at curvilinear "
           "coordinate ``s``.")
      .def("theta_DDD", &CL::theta_DDD, "s"_a,
           "Angle third derivative at curvilinear coordinate ``s``.")
      // TX-TY
      .def(
          "tx", [](CL &cl, const real_type &s) -> real_type { return cl.tx(s); },
          "s"_a, "Tangent x-coordinate at curvilinear coordinate ``s``.")
      .def(
          "ty", [](CL &cl, const real_type &s) -> real_type { return cl.ty(s); },
          "s"_a, "Tangent y-coordinate at curvilinear coordinate ``s``.")
      .def("tx_D", &CL::tx_D, "s"_a,
           "Tangent derivative x-coordinate at curvilinear coordinate ``s``.")
      .def("ty_D", &CL::ty_D, "s"_a,
           "Tangent derivative y-coordinate at curvilinear coordinate ``s``.")
      .def("tx_DD", &CL::tx_DD, "s"_a,
           "Tangent second derivative x-coordinate at curvilinear coordinate "
           "``s``.")
      .def("ty_DD", &CL::ty_DD, "s"_a,
           "Tangent second derivative y-coordinate at curvilinear coordinate "
           "``s``.")
      .def("tx_DDD", &CL::tx_DDD, "s"_a,
           "Tangent third derivative x-coordinate at curvilinear coordinate "
           "``s``.")
      .def("ty_DDD", &CL::ty_DDD, "s"_a,
           "Tangent third derivative y-coordinate at curvilinear coordinate "
           "``s``.")
      // TG
      .def("tg", tg, "s"_a,
           "Tangent vector ``(tx, ty)`` at curvilinear coordinate ``s``.")
      .def("tg_D", tg_D, "s"_a,
           "Tangent derivative ``(tx_D, ty_D)`` at curvilinear coordinate "
           "``s``.")
      .def("tg_DD", tg_DD, "s"_a,
           "Tangent second derivative ``(tx_DD, ty_DD)`` at curvilinear "
           "coordinate ``s``.")
      .def("tg_DDD", tg_DDD, "s"_a,
           "Tangent third derivative ``(tx_DDD, ty_DDD)`` at curvilinear "
           "coordinate ``s``.")
      // EVALUATE
      .def("evaluate", evaluate, "s"_a, DOC_EVALUATE)
      .def("evaluate_ISO", evaluate_ISO, "s"_a, "offs"_a, DOC_EVALUATE_ISO)
      // X-Y
      .def(
          "X", [](CL &cl, const real_type &s) -> real_type { return cl.X(s); },
          "s"_a, "x-coordinate at curvilinear coordinate ``s``.")
      .def(
          "Y", [](CL &cl, const real_type &s) -> real_type { return cl.Y(s); },
          "s"_a, "y-coordinate at curvilinear coordinate ``s``.")
      .def("X_D", &CL::X_D, "s"_a,
           "x-coordinate derivative at curvilinear coordinate ``s``.")
      .def("Y_D", &CL::Y_D, "s"_a,
           "y-coordinate derivative at curvilinear coordinate ``s``.")
      .def("X_DD", &CL::X_DD, "s"_a,
           "x-coordinate second derivative at curvilinear coordinate ``s``.")
      .def("Y_DD", &CL::Y_DD, "s"_a,
           "y-coordinate second derivative at curvilinear coordinate ``s``.")
      .def("X_DDD", &CL::X_DDD, "s"_a,
           "x-coordinate third derivative at curvilinear coordinate ``s``.")
      .def("Y_DDD", &CL::Y_DDD, "s"_a,
           "y-coordinate third derivative at curvilinear coordinate ``s``.")
      // CLOSEST POINT
      .def("closest_point_ISO", closest_point_ISO, "qx"_a, "qy"_a,
           DOC_CLOSEST_POINT_ISO)
      .def("closest_point_ISO", closest_point_ISO_off, "qx"_a, "qy"_a,
           "offs"_a, DOC_CLOSEST_POINT_ISO_OFF)
      .def("closest_point_in_s_range_ISO", closest_point_in_s_range_ISO,
           "qx"_a, "qy"_a, "s_begin"_a, "s_end"_a,
           DOC_CLOSEST_POINT_IN_S_RANGE_ISO);
}
