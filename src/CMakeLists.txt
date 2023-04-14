add_subdirectory(models)
add_subdirectory(controllers)
add_subdirectory(views)

add_executable(main main.cpp)

target_link_libraries(main PUBLIC models controllers views)
target_link_libraries(main PUBLIC Qt6::Core Qt6::Gui Qt6::Widgets)
target_link_libraries(main PUBLIC qcustomplot)
target_link_libraries(main PUBLIC ecl)
