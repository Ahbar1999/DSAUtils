cmake_minimum_required(VERSION 3.5)

project(DSAUtils LANGUAGES C CXX)
# libraries are static by default
# TODO
# 	define a source variable and recursively append all the files in current working directory to this variable
# 	use for loop and special variables 

# 	set flag here to output config_flags.json
add_library(DSA STATIC 
	./dsa/strings/trie.cpp
)

set_target_properties(DSA PROPERTIES LINKER_LANGUAGE CXX)
add_executable(main main.cpp)
target_include_directories(main PRIVATE 
	include
)

target_link_libraries(main PRIVATE DSA)

# target_include_directories(main PRIVATE
# strings
# for_range_queries
# )


