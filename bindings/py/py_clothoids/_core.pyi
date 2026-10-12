"""
Clothoids Python Bindings. This module provides access to the Clothoids library. It is wrapping the C++ classes and functions using pybind11.
"""
from __future__ import annotations
import collections.abc
import typing
__all__: list[str] = ['ClosestPointInRangeResult', 'ClosestPointResult', 'ClothoidList', 'EvalResult']
class ClosestPointInRangeResult:
    """
    Result of ClothoidList.closest_point_in_s_range_ISO.
    """
    def __getitem__(self, arg0: typing.Any) -> typing.Any:
        ...
    def __iter__(self) -> collections.abc.Iterator:
        """
        Iterate over the fields, allows tuple unpacking.
        """
    def __len__(self) -> int:
        ...
    def __repr__(self) -> str:
        ...
    @property
    def dst(self) -> float:
        """
        Distance from the projected point.
        """
    @property
    def i_curve(self) -> int:
        """
        Index of the segment containing the projected point.
        """
    @property
    def s(self) -> float:
        """
        Curvilinear coordinate of the projection.
        """
    @property
    def success(self) -> int:
        """
        1 orthogonal projection, 0 more than one projection, -1 failed.
        """
    @property
    def t(self) -> float:
        """
        Signed distance (ISO) from the curve.
        """
    @property
    def x(self) -> float:
        """
        x-coordinate of the projected point.
        """
    @property
    def y(self) -> float:
        """
        y-coordinate of the projected point.
        """
class ClosestPointResult:
    """
    Result of ClothoidList.closest_point_ISO.
    """
    def __getitem__(self, arg0: typing.Any) -> typing.Any:
        ...
    def __iter__(self) -> collections.abc.Iterator:
        """
        Iterate over the fields, allows tuple unpacking.
        """
    def __len__(self) -> int:
        ...
    def __repr__(self) -> str:
        ...
    @property
    def dst(self) -> float:
        """
        Distance from the projected point.
        """
    @property
    def n(self) -> int:
        """
        Segment index if >= 0 (orthogonal projection), -(segment + 1) otherwise.
        """
    @property
    def s(self) -> float:
        """
        Curvilinear coordinate of the projection.
        """
    @property
    def t(self) -> float:
        """
        Signed distance (ISO) from the curve.
        """
    @property
    def x(self) -> float:
        """
        x-coordinate of the projected point.
        """
    @property
    def y(self) -> float:
        """
        y-coordinate of the projected point.
        """
class ClothoidList:
    """
    A list of clothoid segments forming a piecewise curve.
    """
    def X(self, s: typing.SupportsFloat | typing.SupportsIndex) -> float:
        """
        x-coordinate at curvilinear coordinate ``s``.
        """
    def X_D(self, s: typing.SupportsFloat | typing.SupportsIndex) -> float:
        """
        x-coordinate derivative at curvilinear coordinate ``s``.
        """
    def X_DD(self, s: typing.SupportsFloat | typing.SupportsIndex) -> float:
        """
        x-coordinate second derivative at curvilinear coordinate ``s``.
        """
    def X_DDD(self, s: typing.SupportsFloat | typing.SupportsIndex) -> float:
        """
        x-coordinate third derivative at curvilinear coordinate ``s``.
        """
    def Y(self, s: typing.SupportsFloat | typing.SupportsIndex) -> float:
        """
        y-coordinate at curvilinear coordinate ``s``.
        """
    def Y_D(self, s: typing.SupportsFloat | typing.SupportsIndex) -> float:
        """
        y-coordinate derivative at curvilinear coordinate ``s``.
        """
    def Y_DD(self, s: typing.SupportsFloat | typing.SupportsIndex) -> float:
        """
        y-coordinate second derivative at curvilinear coordinate ``s``.
        """
    def Y_DDD(self, s: typing.SupportsFloat | typing.SupportsIndex) -> float:
        """
        y-coordinate third derivative at curvilinear coordinate ``s``.
        """
    def __init__(self, name: str) -> None:
        """
        Build an empty clothoid list with the given name.
        """
    @typing.overload
    def build_G1(self, n: typing.SupportsInt | typing.SupportsIndex, x: collections.abc.Sequence[typing.SupportsFloat | typing.SupportsIndex], y: collections.abc.Sequence[typing.SupportsFloat | typing.SupportsIndex]) -> bool:
        """
        Build the clothoid list passing through a list of points, solving a series
        of G1 fitting problems. The angles at the points are estimated automatically.
        
        Args:
            n: Number of points.
            x: x-coordinates of the points.
            y: y-coordinates of the points.
        
        Returns:
            False if the construction fails.
        """
    @typing.overload
    def build_G1(self, n: typing.SupportsInt | typing.SupportsIndex, x: collections.abc.Sequence[typing.SupportsFloat | typing.SupportsIndex], y: collections.abc.Sequence[typing.SupportsFloat | typing.SupportsIndex], theta: collections.abc.Sequence[typing.SupportsFloat | typing.SupportsIndex]) -> bool:
        """
        Build the clothoid list passing through a list of points with the given
        angles, solving a series of G1 fitting problems.
        
        Args:
            n: Number of points.
            x: x-coordinates of the points.
            y: y-coordinates of the points.
            theta: Angles (radians) at the points.
        
        Returns:
            False if the construction fails.
        """
    @typing.overload
    def build_G2(self, n: typing.SupportsInt | typing.SupportsIndex, x: collections.abc.Sequence[typing.SupportsFloat | typing.SupportsIndex], y: collections.abc.Sequence[typing.SupportsFloat | typing.SupportsIndex], theta_init: typing.SupportsFloat | typing.SupportsIndex, theta_end: typing.SupportsFloat | typing.SupportsIndex) -> bool:
        """
        Build a sequence of clothoid arcs interpolating the points with G2
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
        """
    @typing.overload
    def build_G2(self, n: typing.SupportsInt | typing.SupportsIndex, x: collections.abc.Sequence[typing.SupportsFloat | typing.SupportsIndex], y: collections.abc.Sequence[typing.SupportsFloat | typing.SupportsIndex], theta_init: typing.SupportsFloat | typing.SupportsIndex, kappa_init: typing.SupportsFloat | typing.SupportsIndex, theta_end: typing.SupportsFloat | typing.SupportsIndex, kappa_end: typing.SupportsFloat | typing.SupportsIndex) -> bool:
        """
        Build a sequence of clothoid arcs interpolating the points with G2
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
        """
    def build_G2_cyclic(self, n: typing.SupportsInt | typing.SupportsIndex, x: collections.abc.Sequence[typing.SupportsFloat | typing.SupportsIndex], y: collections.abc.Sequence[typing.SupportsFloat | typing.SupportsIndex]) -> bool:
        """
        Build a closed sequence of clothoid arcs interpolating the points with G2
        continuity: position, tangent and curvature are continuous everywhere,
        including between the last and the first point.
        
        Args:
            n: Number of points (at least 3).
            x: x-coordinates of the points.
            y: y-coordinates of the points.
        
        Returns:
            True if the construction succeeds, False otherwise.
        """
    def build_raw(self, x: collections.abc.Sequence[typing.SupportsFloat | typing.SupportsIndex], y: collections.abc.Sequence[typing.SupportsFloat | typing.SupportsIndex], abscissa: collections.abc.Sequence[typing.SupportsFloat | typing.SupportsIndex], theta: collections.abc.Sequence[typing.SupportsFloat | typing.SupportsIndex], kappa: collections.abc.Sequence[typing.SupportsFloat | typing.SupportsIndex]) -> bool:
        """
        Build the clothoid list from raw data. All the lists must have the same
        length.
        
        Args:
            x: x-coordinates of the break points.
            y: y-coordinates of the break points.
            abscissa: Curvilinear abscissa of the break points.
            theta: Angles at the break points.
            kappa: Curvatures at the break points.
        
        Returns:
            False if the construction fails.
        """
    @typing.overload
    def closest_point_ISO(self, qx: typing.SupportsFloat | typing.SupportsIndex, qy: typing.SupportsFloat | typing.SupportsIndex) -> ClosestPointResult:
        """
        Find the point on the curve closest to the point (qx, qy).
        
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
        """
    @typing.overload
    def closest_point_ISO(self, qx: typing.SupportsFloat | typing.SupportsIndex, qy: typing.SupportsFloat | typing.SupportsIndex, offs: typing.SupportsFloat | typing.SupportsIndex) -> ClosestPointResult:
        """
        Find the point on the offset curve (ISO convention) closest to the point
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
        """
    def closest_point_in_s_range_ISO(self, qx: typing.SupportsFloat | typing.SupportsIndex, qy: typing.SupportsFloat | typing.SupportsIndex, s_begin: typing.SupportsFloat | typing.SupportsIndex, s_end: typing.SupportsFloat | typing.SupportsIndex) -> ClosestPointInRangeResult:
        """
        Find the point on the curve closest to the point (qx, qy), searching only
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
        """
    def evaluate(self, s: typing.SupportsFloat | typing.SupportsIndex) -> EvalResult:
        """
        Evaluate the curve at curvilinear coordinate ``s``.
        
        Args:
            s: Curvilinear coordinate.
        
        Returns:
            Angle ``th``, curvature ``k`` and position ``x``, ``y``.
        """
    def evaluate_ISO(self, s: typing.SupportsFloat | typing.SupportsIndex, offs: typing.SupportsFloat | typing.SupportsIndex) -> EvalResult:
        """
        Evaluate the offset curve (ISO convention) at curvilinear coordinate ``s``.
        
        Args:
            s: Curvilinear coordinate.
            offs: Offset from the curve.
        
        Returns:
            Angle ``th``, curvature ``k`` and position ``x``, ``y``.
        """
    def init(self) -> None:
        """
        Reset the clothoid list, removing all segments.
        """
    def is_closed(self) -> bool:
        """
        Return True if the curve is closed.
        """
    def length(self) -> float:
        """
        Length of the curve.
        """
    def length_ISO(self, offs: typing.SupportsFloat | typing.SupportsIndex) -> float:
        """
        Length of the curve with offset ``offs`` (ISO convention).
        """
    def length_SAE(self, offs: typing.SupportsFloat | typing.SupportsIndex) -> float:
        """
        Length of the curve with offset ``offs`` (SAE convention).
        """
    def make_closed(self) -> None:
        """
        Mark the curve as closed.
        """
    def make_open(self) -> None:
        """
        Mark the curve as open.
        """
    def nx_begin_ISO(self) -> float:
        """
        Initial normal x-coordinate (ISO convention).
        """
    def nx_end_ISO(self) -> float:
        """
        Final normal x-coordinate (ISO convention).
        """
    def ny_begin_ISO(self) -> float:
        """
        Initial normal y-coordinate (ISO convention).
        """
    def ny_end_ISO(self) -> float:
        """
        Final normal y-coordinate (ISO convention).
        """
    def reserve(self, n: typing.SupportsInt | typing.SupportsIndex) -> None:
        """
        Reserve memory for ``n`` clothoids.
        """
    def tg(self, s: typing.SupportsFloat | typing.SupportsIndex) -> tuple[float, float]:
        """
        Tangent vector ``(tx, ty)`` at curvilinear coordinate ``s``.
        """
    def tg_D(self, s: typing.SupportsFloat | typing.SupportsIndex) -> tuple[float, float]:
        """
        Tangent derivative ``(tx_D, ty_D)`` at curvilinear coordinate ``s``.
        """
    def tg_DD(self, s: typing.SupportsFloat | typing.SupportsIndex) -> tuple[float, float]:
        """
        Tangent second derivative ``(tx_DD, ty_DD)`` at curvilinear coordinate ``s``.
        """
    def tg_DDD(self, s: typing.SupportsFloat | typing.SupportsIndex) -> tuple[float, float]:
        """
        Tangent third derivative ``(tx_DDD, ty_DDD)`` at curvilinear coordinate ``s``.
        """
    def theta(self, s: typing.SupportsFloat | typing.SupportsIndex) -> float:
        """
        Angle at curvilinear coordinate ``s``.
        """
    def theta_D(self, s: typing.SupportsFloat | typing.SupportsIndex) -> float:
        """
        Angle derivative (curvature) at curvilinear coordinate ``s``.
        """
    def theta_DD(self, s: typing.SupportsFloat | typing.SupportsIndex) -> float:
        """
        Angle second derivative (derivative of curvature) at curvilinear coordinate ``s``.
        """
    def theta_DDD(self, s: typing.SupportsFloat | typing.SupportsIndex) -> float:
        """
        Angle third derivative at curvilinear coordinate ``s``.
        """
    def theta_begin(self) -> float:
        """
        Initial angle of the curve.
        """
    def theta_end(self) -> float:
        """
        Final angle of the curve.
        """
    def tx(self, s: typing.SupportsFloat | typing.SupportsIndex) -> float:
        """
        Tangent x-coordinate at curvilinear coordinate ``s``.
        """
    def tx_D(self, s: typing.SupportsFloat | typing.SupportsIndex) -> float:
        """
        Tangent derivative x-coordinate at curvilinear coordinate ``s``.
        """
    def tx_DD(self, s: typing.SupportsFloat | typing.SupportsIndex) -> float:
        """
        Tangent second derivative x-coordinate at curvilinear coordinate ``s``.
        """
    def tx_DDD(self, s: typing.SupportsFloat | typing.SupportsIndex) -> float:
        """
        Tangent third derivative x-coordinate at curvilinear coordinate ``s``.
        """
    def tx_begin(self) -> float:
        """
        Initial tangent x-coordinate.
        """
    def tx_end(self) -> float:
        """
        Final tangent x-coordinate.
        """
    def ty(self, s: typing.SupportsFloat | typing.SupportsIndex) -> float:
        """
        Tangent y-coordinate at curvilinear coordinate ``s``.
        """
    def ty_D(self, s: typing.SupportsFloat | typing.SupportsIndex) -> float:
        """
        Tangent derivative y-coordinate at curvilinear coordinate ``s``.
        """
    def ty_DD(self, s: typing.SupportsFloat | typing.SupportsIndex) -> float:
        """
        Tangent second derivative y-coordinate at curvilinear coordinate ``s``.
        """
    def ty_DDD(self, s: typing.SupportsFloat | typing.SupportsIndex) -> float:
        """
        Tangent third derivative y-coordinate at curvilinear coordinate ``s``.
        """
    def ty_begin(self) -> float:
        """
        Initial tangent y-coordinate.
        """
    def ty_end(self) -> float:
        """
        Final tangent y-coordinate.
        """
    def x_begin(self) -> float:
        """
        Initial x-coordinate.
        """
    def x_begin_ISO(self, offs: typing.SupportsFloat | typing.SupportsIndex) -> float:
        """
        Initial x-coordinate with offset ``offs`` (ISO convention).
        """
    def x_end(self) -> float:
        """
        Final x-coordinate.
        """
    def x_end_ISO(self, offs: typing.SupportsFloat | typing.SupportsIndex) -> float:
        """
        Final x-coordinate with offset ``offs`` (ISO convention).
        """
    def y_begin(self) -> float:
        """
        Initial y-coordinate.
        """
    def y_begin_ISO(self, offs: typing.SupportsFloat | typing.SupportsIndex) -> float:
        """
        Initial y-coordinate with offset ``offs`` (ISO convention).
        """
    def y_end(self) -> float:
        """
        Final y-coordinate.
        """
    def y_end_ISO(self, offs: typing.SupportsFloat | typing.SupportsIndex) -> float:
        """
        Final y-coordinate with offset ``offs`` (ISO convention).
        """
class EvalResult:
    """
    Result of ClothoidList.evaluate / evaluate_ISO.
    """
    def __getitem__(self, arg0: typing.Any) -> typing.Any:
        ...
    def __iter__(self) -> collections.abc.Iterator:
        """
        Iterate over the fields, allows tuple unpacking.
        """
    def __len__(self) -> int:
        ...
    def __repr__(self) -> str:
        ...
    @property
    def k(self) -> float:
        """
        Curvature.
        """
    @property
    def th(self) -> float:
        """
        Angle (radians).
        """
    @property
    def x(self) -> float:
        """
        x-coordinate.
        """
    @property
    def y(self) -> float:
        """
        y-coordinate.
        """
