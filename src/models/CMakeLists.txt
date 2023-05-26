set(SRCROOT ${PROJECT_SOURCE_DIR}/src/models)
set(INCROOT ${PROJECT_SOURCE_DIR}/include/models)

set(SRC
    ${INCROOT}/result.hpp
	${SRCROOT}/result.cpp
	${INCROOT}/time.hpp
	${SRCROOT}/time.cpp
	${INCROOT}/channel.hpp
	${SRCROOT}/channel.cpp
	${INCROOT}/signal.hpp
	${SRCROOT}/signal.cpp
	${INCROOT}/parser.hpp
	${SRCROOT}/parser.cpp

	${INCROOT}/signal_parsers/istream_wrapper.hpp
	${SRCROOT}/signal_parsers/istream_wrapper.cpp
	${INCROOT}/signal_parsers/txt_parser.hpp
	${SRCROOT}/signal_parsers/txt_parser.cpp
)


if (NOT "${SRC}" STREQUAL "")
	message(STATUS "Models building...")

	add_library(models ${SRC})

	target_include_directories(models PUBLIC ${PROJECT_SOURCE_DIR}/include/)
else()
	message(WARNING "Models have no source files")
endif()