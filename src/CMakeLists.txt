add_subdirectory(models)
add_subdirectory(controllers)
add_subdirectory(views)

set(SRCROOT ${PROJECT_SOURCE_DIR}/src/)

set(SRC
	
)

if (NOT "${SRC}" STREQUAL "")
	message(STATUS "Building main executable...")
	set(MAIN_CREATED)

	add_executable(main ${SRC})

	if (DEFINED MODELS_CREATED)
		message(STATUS "Executable linked to models")
		target_link_libraries(main PUBLIC models)
	endif()

	if (DEFINED CONTROLLERS_CREATED)
		message(STATUS "Executable linked to controllers")
		target_link_libraries(main PUBLIC controllers)
	endif()

	if (DEFINED VIEWS_CREATED)
		message(STATUS "Executable linked to views")
		target_link_libraries(main PUBLIC views)
	endif()

	target_link_libraries(main PUBLIC Qt6::Core Qt6::Gui Qt6::Widgets)
	target_link_libraries(main PUBLIC qcustomplot)
else()
	message(WARNING "Executable not built")
endif()