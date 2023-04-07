set(SRCROOT ${PROJECT_SOURCE_DIR}/src/controllers)

set(SRC

)

add_library(controllers ${SRC})

target_include_directories(controllers PUBLIC ${PROJECT_SOURCE_DIR}/include/)
target_link_libraries(controllers PUBLIC ecl)