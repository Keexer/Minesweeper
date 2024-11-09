cmake_minimum_required(VERSION 3.29)

set(Headers
	include/graphics/rectangle.h
	)
	
set(Source
	src/rectangle.cpp
)

add_subdirectory(../../external/SDL EXCLUDE_FROM_ALL SDL)

add_library(graphics STATIC ${Headers} ${Source})

target_link_libraries(graphics PUBLIC utils SDL3::SDL3)
target_include_directories(graphics PUBLIC include PRIVATE $<TARGET_PROPERTY:SDL3::SDL3,INTERFACE_INCLUDE_DIRECTORIES>)

add_custom_command(
	TARGET graphics POST_BUILD
	COMMAND "${CMAKE_COMMAND}" -E copy $<TARGET_FILE:SDL3::SDL3-shared> $<TARGET_FILE_DIR:graphics>
	VERBATIM
)
