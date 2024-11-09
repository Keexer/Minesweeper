cmake_minimum_required(VERSION 3.29)

set(Headers
	include/utils/types.h
	)

add_library(utils INTERFACE ${Headers})

target_include_directories(utils INTERFACE include)
