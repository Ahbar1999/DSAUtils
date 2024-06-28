cmake_minimum_required(VERSION 3.5)

project(DSAUtils LANGUAGES C CXX)
set (CMAKE_CXX_FLAGS "-std=c++17")
# libraries are static by default
# TODO : set flag here to output config_flags.json

add_subdirectory(dsa)	# our library, has its won cmake build
add_executable(main main.cpp)

# target_include_directories(main PRIVATE 
	# include
	# )
# link main target and DSA library
target_link_libraries(main PRIVATE DSA)

# TODO
# 	define a source variable and recursively append all the files in current working directory to this variable
# 	use for loop and special variables like below 

# file( GLOB LIB_SOURCES lib/*.cpp )
# file( GLOB LIB_HEADERS lib/*.h )
# add_library( YourLib ${LIB_SOURCES} ${LIB_HEADERS})


