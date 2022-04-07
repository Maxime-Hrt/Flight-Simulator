cmake_minimum_required(VERSION 3.21)
project(Swimming_pool)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp aeroport.cpp avion.cpp Classes.h sous_programmes.cpp Graphique.cpp Carte.cpp)

add_executable(HelloSFML ${SOURCE_FILES})

include_directories(/usr/local/include)

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
include_directories(${SFML_INCLUDE_DIRS})
target_link_libraries(HelloSFML sfml-system sfml-window sfml-graphics sfml-audio sfml-network)