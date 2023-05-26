set(SRCROOT ${PROJECT_SOURCE_DIR}/src/models)
set(INCROOT ${PROJECT_SOURCE_DIR}/include/models)

set(SRC
    ${INCROOT}/result.hpp
	${SRCROOT}/result.cpp
	${INCROOT}/time.hpp
	${SRCROOT}/time.cpp
)


if (NOT "${SRC}" STREQUAL "")
	message(STATUS "Models building...")

	add_library(models ${SRC})

	target_include_directories(models PUBLIC ${PROJECT_SOURCE_DIR}/include/)
else()
	message(WARNING "Models have no source files")
endif()