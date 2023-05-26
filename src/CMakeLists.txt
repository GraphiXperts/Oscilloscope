add_subdirectory(models)
add_subdirectory(controllers)
add_subdirectory(views)

set(SRCROOT ${PROJECT_SOURCE_DIR}/src)

set(SRC
	
)

if (NOT "${SRC}" STREQUAL "")
	message(STATUS "Building main executable...")

	add_executable(main ${SRC})

	if (TARGET models)
		message(STATUS "Executable linked to models")
		target_link_libraries(main PUBLIC models)
	endif()

	if (TARGET controllers)
		message(STATUS "Executable linked to controllers")
		target_link_libraries(main PUBLIC controllers)
	endif()

	if (TARGET views)
		message(STATUS "Executable linked to views")
		target_link_libraries(main PUBLIC views)
	endif()

	target_link_libraries(main PUBLIC Qt6::Core Qt6::Gui Qt6::Widgets)
	target_link_libraries(main PUBLIC qcustomplot)
else()
	message(WARNING "Executable not built")
endif()