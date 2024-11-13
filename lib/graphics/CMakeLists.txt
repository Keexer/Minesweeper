cmake_minimum_required(VERSION 3.29)

set(Headers
	include/graphics/rectangle.h
	include/graphics/text.h
	include/graphics/fonts.h
)
	
set(Source
	src/rectangle.cpp
	src/text.cpp
	src/fonts.cpp
)

add_subdirectory(../../external/SDL EXCLUDE_FROM_ALL SDL)
add_subdirectory(../../external/SDL_ttf EXCLUDE_FROM_ALL SDL_ttf)

add_library(graphics STATIC ${Headers} ${Source})

target_link_libraries(graphics PUBLIC utils SDL3::SDL3 SDL3_ttf::SDL3_ttf)
target_include_directories(graphics PUBLIC include PRIVATE $<TARGET_PROPERTY:SDL3::SDL3,INTERFACE_INCLUDE_DIRECTORIES> $<TARGET_PROPERTY:SDL3_ttf::SDL3_ttf,INTERFACE_INCLUDE_DIRECTORIES>)

add_custom_command(
	TARGET graphics POST_BUILD
	COMMAND "${CMAKE_COMMAND}" -E copy $<TARGET_FILE:SDL3::SDL3-shared> $<TARGET_FILE_DIR:graphics>
	VERBATIM
)
