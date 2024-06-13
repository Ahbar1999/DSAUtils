cmake_minimum_required(VERSION 3.5)

project(DSAUtils LANGUAGES C CXX)
# libraries are static by default
# TODO
# 	define a source variable and recursively append all the files in current working directory to this variable
# 	use for loop and special variables 

# 	set flag here to output config_flags.json  
add_executable(main 
	main.cpp
	strings/trie.h
	strings/suffix_arrays.h
	for_range_queries/fenwick_tree.h)


target_include_directories(main PRIVATE
	strings
	for_range_queries
)



