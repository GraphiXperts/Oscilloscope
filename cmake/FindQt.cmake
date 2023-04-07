# Setting Qt variables
set(QT_MIN_VERSION "5.12.0")
set(QT_COMPONENTS Core Gui Widgets)

# if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
#     set(Qt5_DIR /usr/lib/qt5/)
# endif()

find_package(Qt5 ${QT_MIN_VERSION} COMPONENTS ${QT_COMPONENTS} RQUIRED)

if (NOT Qt5_FOUND)
    message(FATAL_ERROR "Qt5 not found")
endif()

message(STATUS "Found Qt ${Qt5_VERSION}")

set(QT_INCLUDE_DIRS ${Qt5_INCLUDE_DIRS})
set(QT_LIBRARIES ${Qt5_LIBRARIES})
set(QT_DEFINITIONS ${Qt5_DEFINITIONS})