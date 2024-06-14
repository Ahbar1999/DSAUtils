cmake_minimum_required(VERSION 3.5)

project(DSA LANGUAGES C CXX)
# libraries are static by default

add_library(DSA STATIC 
	./strings/trie.cpp
	./strings/suffix_arrays.cpp
	./strings/string_hashing.cpp
	./for_range_queries/fenwick_tree.cpp
	./for_range_queries/segment_tree.cpp
)

# target_include_directories(DSA PUBLIC 
# 	include
# )

# TODO
# 	define a source variable and recursively append all the files in current working directory to this variable
# 	use for loop and special variables like below 

# file( GLOB LIB_SOURCES lib/*.cpp )
# file( GLOB LIB_HEADERS lib/*.h )
# add_library( YourLib ${LIB_SOURCES} ${LIB_HEADERS})


