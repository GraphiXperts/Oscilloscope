set(SRCROOT ${PROJECT_SOURCE_DIR}/src/models)

set(SRC

)

add_library(models ${SRC})

target_include_directories(models PUBLIC ${PROJECT_SOURCE_DIR}/include/)
target_link_libraries(models PUBLIC ecl)