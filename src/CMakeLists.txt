INCLUDE_DIRECTORIES(
	"${PROJECT_SOURCE_DIR}/src"
	"${PROJECT_SOURCE_DIR}/src/app"
	"${PROJECT_SOURCE_DIR}/src/common"
	"${PROJECT_SOURCE_DIR}/src/model"
	"${PROJECT_SOURCE_DIR}/src/model/algorithm"
	"${PROJECT_SOURCE_DIR}/src/view"
	"${PROJECT_SOURCE_DIR}/src/viewmodel"
	"${PROJECT_SOURCE_DIR}/src/window"
)

SET(EXECUTABLE_OUTPUT_PATH "${PROJECT_BINARY_DIR}/bin")
SET(SRC_PCH_LIST "precomp.cc")
SET(SRC_LIST
  "main.cc"
)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/app)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/common)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/model)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/view)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/viewmodel)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/window)

ADD_EXECUTABLE(RayTracing ${SRC_PCH_LIST} ${SRC_LIST})

SET_PCH(RayTracing "exe" "precomp.hpp" ${SRC_PCH_LIST} ${SRC_LIST})

SET_TARGET_PROPERTIES(RayTracing PROPERTIES
	OUTPUT_NAME "RayTracing"
	LINK_FLAGS "${STRING_LINK_FLAGS_TARGET}"
)

TARGET_LINK_LIBRARIES(RayTracing ${STRING_CSL_LIBS} ${STRING_FLTK_LIBS} ${STRING_LINK_EXTRA_LIBS})
