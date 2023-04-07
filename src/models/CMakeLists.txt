set(SRCROOT ${PROJECT_SOURCE_DIR}/src/models)
set(INCROOT ${PROJECT_SOURCE_DIR}/include/models)

set(SRC
    ${SRCROOT}/Parsers/Parser.cpp
    ${SRCROOT}/Parsers/Txtparser.cpp
    ${SRCROOT}/Signal.cpp
)

add_library(models ${SRC})

target_include_directories(models PUBLIC ${PROJECT_SOURCE_DIR}/include/)
target_link_libraries(models PUBLIC ecl)