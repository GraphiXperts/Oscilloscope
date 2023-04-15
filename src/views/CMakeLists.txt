set(INCROOT ${PROJECT_SOURCE_DIR}/include/views)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/views)

set(SRC
    ${INCROOT}/plot.hpp
    ${SRCROOT}/plot.cpp
    ${INCROOT}/main_interface.hpp
    ${SRCROOT}/main_interface.cpp
)

add_library(views ${SRC})

target_include_directories(views PUBLIC ${PROJECT_SOURCE_DIR}/include/)
target_link_libraries(views PUBLIC ecl)
target_link_libraries(views PUBLIC models)
target_link_libraries(views PUBLIC Qt6::Core Qt6::Widgets)
target_link_libraries(views PUBLIC qcustomplot)
