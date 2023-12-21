project(testgame)

add_executable(testgame
	main.c)

target_include_directories(testgame PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(testgame engine)