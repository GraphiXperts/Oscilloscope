set(INCROOT ${PROJECT_SOURCE_DIR}/include/views)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/views)

set(SRC
    
)

if (NOT "${SRC}" STREQUAL "")
	message(STATUS "Views building...")
	set(VIEWS_CREATED)
	
	add_library(views ${SRC})

	target_include_directories(views PUBLIC ${PROJECT_SOURCE_DIR}/include/)

	if (DEFINED MODELS_CREATED)
		message(STATUS "Views linked to models.")
		target_link_libraries(views PUBLIC models)
	endif()

	if (DEFINED CONROLLERS_CREATED)
		message(STATUS "Views linked to controllers")
		target_link_libraries(views PUBLIC controllers)
	endif()

	target_link_libraries(views PUBLIC Qt6::Core Qt6::Widgets)
	target_link_libraries(views PUBLIC qcustomplot)
else ()
	message(WARNING "Views have no source files")
endif()