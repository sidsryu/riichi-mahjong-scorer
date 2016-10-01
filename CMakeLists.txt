project(riichi-mahjong-scorer)

cmake_minimum_required(VERSION 2.4)


# build configuration
set(CMAKE_CONFIGURATION_TYPES Debug Release)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")


# install cpputest
set(cpputest_home ${PROJECT_SOURCE_DIR}/lib/cpputest)

include(ExternalProject)

set(cpputest_cmake_args
	-DCMAKE_INSTALL_PREFIX=${cpputest_home}
    -DCMAKE_BUILD_TYPE=Release
	-DTESTS=OFF
)
ExternalProject_Add(CppUTest
	PREFIX cpputest-master
	GIT_REPOSITORY https://github.com/cpputest/cpputest.git    
    GIT_TAG v3.8
	CMAKE_ARGS ${cpputest_cmake_args}
)


# richi-mahjong-scorer projects
add_subdirectory(src)
add_subdirectory(test)
add_dependencies(riichi-mahjong-scorer-tests CppUTest)
