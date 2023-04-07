include(FetchContent)

FetchContent_Declare(
    ec
    GIT_REPOSITORY  https://github.com/TheMusicBoy/EventController.git
    GIT_TAG         in_dev
)

FetchContent_GetProperties(ec)

if(NOT ec_POPULATED)
    message("Event Controller populating...")

    FetchContent_Populate(ec)
    add_subdirectory(${ec_SOURCE_DIR} ${ec_BINARY_DIR})
endif()