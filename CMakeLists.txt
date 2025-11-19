set(CDIR  ${CMAKE_CURRENT_LIST_DIR})

add_subdirectory(eigen)

file(
  GLOB 
  clothoids_main_headers
  clothoids/src/*.hh
  clothoids/src/Clothoids/*.hxx
)
file(
  GLOB
  sub_sources
  clothoids/submodules/quarticRootsFlocke/src/*.cc
  clothoids/submodules/GenericContainer/src/*.cc
)
file(
  GLOB
  utils_sources
  clothoids/submodules/UtilsLite/src/*.hh
)

add_library(
  clothoids
  STATIC
	clothoids/src/BBox.cc
  clothoids/src/Biarc.cc
  clothoids/src/BiarcList.cc
  clothoids/src/Circle.cc
  clothoids/src/Clothoid.cc
  clothoids/src/ClothoidDistance.cc
  clothoids/src/ClothoidG2.cc
  clothoids/src/ClothoidList.cc
  clothoids/src/ClothoidListG2.cc
  clothoids/src/ClothoidListG2_P1P2.cc
	clothoids/src/ClothoidList_LBFGS.cc
  clothoids/src/Dubins3p.cc
  clothoids/src/Dubins3p_ellipse.cc
  clothoids/src/Dubins3p_pattern.cc
  clothoids/src/Dubins.cc
  clothoids/src/Fresnel.cc
  clothoids/src/G2lib.cc
  clothoids/src/G2lib_intersect.cc
  clothoids/src/Line.cc
  clothoids/src/PolyLine.cc
  clothoids/src/Triangle2D.cc

  ${sub_sources}

  clothoids/submodules/UtilsLite/src/Utils.cc
  clothoids/submodules/UtilsLite/src/Malloc.cc
  clothoids/submodules/UtilsLite/src/Console.cc
  clothoids/submodules/UtilsLite/src/Utils_Trace.cc
  clothoids/submodules/UtilsLite/src/Utils_AABB_tree.cc
	clothoids/submodules/UtilsLite/src/Utils_AlgoBracket.cc
)
set(PIPAL_EIGEN_EXTERNAL ON CACHE BOOL "Use external Eigen3 for Pipal")
add_subdirectory(pipal)
target_link_libraries(clothoids
	PUBLIC
		Eigen3::Eigen
)

target_include_directories(clothoids
    PUBLIC
    $<BUILD_INTERFACE:${CDIR}/clothoids/src>
    $<BUILD_INTERFACE:${CDIR}/clothoids/src/Clothoids>
    $<BUILD_INTERFACE:${CDIR}/clothoids/submodules/UtilsLite/src>
    $<BUILD_INTERFACE:${CDIR}/clothoids/submodules/UtilsLite/src/Utils>
		$<BUILD_INTERFACE:${CDIR}/clothoids/submodules/UtilsLite/ThirdParties/Eigen/eigen-5.0.0/>
    $<BUILD_INTERFACE:${CDIR}/clothoids/submodules/GenericContainer/include/>
    $<BUILD_INTERFACE:${CDIR}/clothoids/lib3rd/include/>
		$<BUILD_INTERFACE:${CDIR}/pipal/include/>
    $<BUILD_INTERFACE:${CDIR}/clothoids/submodules/quarticRootsFlocke/src/>
    $<INSTALL_INTERFACE:inc>
)
target_compile_options(
  clothoids
  PRIVATE
  -w
)
