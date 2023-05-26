set(INCROOT ${PROJECT_SOURCE_DIR}/include)
set(SRCROOT ${PROJECT_SOURCE_DIR}/test)

set(AUTOGEN_BUILD_LIST ON)

if (${AUTOGEN_BUILD_LIST})
	file(GLOB TEST_SOURCES "${SRCROOT}/*.cpp")
else()
	set(TEST_SOURCES 
		
	)
endif()

if (NOT "${TEST_SOURCES}" STREQUAL "")
	message(STATUS "Test building...")
	set(TESTS_CREATED)

	set(TEST_NUMBER 0)

	foreach(TEST_SRC ${TEST_SOURCES})
		math(EXPR TEST_NUMBER "${TEST_NUMBER} + 1")
		set(TEST_NAME "test${TEST_NUMBER}")

		message(STATUS "------------${TEST_NAME}------------")
		message(STATUS "File name: ${TEST_SRC}")

		add_executable(${TEST_NAME} ${TEST_SRC})

		if (TARGET models)
			message(STATUS "${TEST_NAME} linked to models")
			target_link_libraries(${TEST_NAME} PUBLIC models)
		endif()

		if (${CONTROLLERS_CREATED})
			message(STATUS "${TEST_NAME} linked to controllers")
			target_link_libraries(${TEST_NAME} PUBLIC controllers)
		endif()

		if (${VIEWS_CREATED})
			message(STATUS "${TEST_NAME} linked to views")
			target_link_libraries(${TEST_NAME} PUBLIC views)
		endif()
		
		target_include_directories(${TEST_NAME} PUBLIC ${INCROOT})
		message(STATUS "${TEST_NAME} built successfully!")
		message(STATUS "--------------------------------\n")

	endforeach()
else()
	message(WARNING "Tests not found")
endif()