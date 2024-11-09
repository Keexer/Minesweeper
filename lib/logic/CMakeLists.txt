cmake_minimum_required(VERSION 3.29)

set(Headers
	include/logic/board.h
	)
	
set(Source
	src/board.cpp
)

add_library(logic STATIC ${Headers} ${Source})

target_link_libraries(logic PUBLIC utils)
target_include_directories(logic PUBLIC include)
