add_subdirectory(models)
add_subdirectory(controllers)
add_subdirectory(views)

add_executable(main main.cpp)

target_link_libraries(main PUBLIC models controllers views)
target_link_libraries(main PUBLIC Qt5::Core Qt5::Gui Qt5::Widgets)
target_link_libraries(main PUBLIC ecl)
