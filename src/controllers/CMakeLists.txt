set(INCROOT ${PROJECT_SOURCE_DIR}/include/controllers)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/controllers)

set(SRC
	${INCROOT}/signal_list.hpp
	${SRCROOT}/signal_list.cpp
	${INCROOT}/use_cases.hpp
	${SRCROOT}/use_cases.cpp
)


if (NOT "${SRC}" STREQUAL "")
	message(STATUS "Controller building...")

	add_library(controllers ${SRC})

	target_include_directories(controllers PUBLIC ${PROJECT_SOURCE_DIR}/include/)

	if (TARGET models)
		message(STATUS "Controllers linked to models")
		target_link_libraries(controllers PUBLIC models)
	endif()

else()
	message(WARNING "Controller have no source files")
endif()