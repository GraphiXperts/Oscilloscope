set(INCROOT ${PROJECT_SOURCE_DIR}/thirdparty/qcustomplot)
set(SRCROOT ${PROJECT_SOURCE_DIR}/thirdparty/qcustomplot)

set(SRC 
    ${INCROOT}/qcustomplot.h
    ${SRCROOT}/qcustomplot.cpp
)

add_library(qcustomplot ${SRC})
target_include_directories(qcustomplot PUBLIC ${INCROOT})
target_link_libraries(qcustomplot PUBLIC Qt6::Core Qt6::Gui Qt6::Widgets Qt6::PrintSupport)