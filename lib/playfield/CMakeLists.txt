cmake_minimum_required(VERSION 3.29)

set(Headers
	include/playfield/cell.h
	include/playfield/background.h
	include/playfield/buttonField.h
	)
	
set(Source
	src/cell.cpp
	src/background.cpp
	src/buttonField.cpp
)

add_library(playfield STATIC ${Headers} ${Source})

target_link_libraries(playfield PUBLIC graphics logic)
target_include_directories(playfield PUBLIC include)
