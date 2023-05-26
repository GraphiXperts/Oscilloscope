set(INCROOT ${PROJECT_SOURCE_DIR}/include/views)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/views)

set(SRC
    
)

if (NOT "${SRC}" STREQUAL "")
	message(STATUS "Views building...")
	
	add_library(views ${SRC})

	target_include_directories(views PUBLIC ${PROJECT_SOURCE_DIR}/include/)

	if (TARGET models)
		message(STATUS "Views linked to models.")
		target_link_libraries(views PUBLIC models)
	endif()

	if (TARGET controllers)
		message(STATUS "Views linked to controllers")
		target_link_libraries(views PUBLIC controllers)
	endif()

	target_link_libraries(views PUBLIC Qt6::Core Qt6::Widgets)
	target_link_libraries(views PUBLIC qcustomplot)
else ()
	message(WARNING "Views have no source files")
endif()