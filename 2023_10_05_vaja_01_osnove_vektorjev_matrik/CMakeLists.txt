cmake_minimum_required(VERSION 3.26)
project(2023_10_05_vaja_1_osnove_vektorjev_matrik)

set(CMAKE_CXX_STANDARD 17)

find_package(glfw3 3.3 REQUIRED)
find_package(glm REQUIRED)

add_executable(2023_10_05_vaja_1_osnove_vektorjev_matrik main.cpp)

target_link_libraries(2023_10_05_vaja_1_osnove_vektorjev_matrik glfw glm::glm)