cmake_minimum_required(VERSION 3.23)
project(search_engine)

set(CMAKE_CXX_STANDARD 14)

set(JSON_BuildTests OFF CACHE INTERNAL "")

set(CMAKE_CXX_FLAGS "-fopenmp")


add_subdirectory(nlohmann_json)

add_executable(search_engine main.cpp InvertedIndex.h ConverterJSON.h SearchServer.h)

target_link_libraries(search_engine PRIVATE nlohmann_json::nlohmann_json)




