set(SRCROOT ${PROJECT_SOURCE_DIR}/src/views)

set(SRC

)

add_library(views ${SRC})

target_include_directories(views PUBLIC ${PROJECT_SOURCE_DIR}/include/)
target_link_libraries(views PUBLIC ecl)
target_link_libraries(views PUBLIC Qt5::Core Qt5::Gui Qt5::Widgets)