cmake_minimum_required(VERSION 3.26)
project(2023_10_12_vaja_2_piramida)

set(CMAKE_CXX_STANDARD 17)

find_package(glfw3 3.3 REQUIRED)
find_package(glm REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

add_executable(2023_10_12_vaja_2_piramida main.cpp
        world/window/OpenGLWindow.cpp
        world/window/OpenGLWindow.h
        object/Mesh.cpp
        object/Mesh.h
        shader/ShaderProgram.cpp
        shader/ShaderProgram.h
        object/Cuboid/Cuboid.cpp
        object/Cuboid/Cuboid.h
        world/io/keyboard/Keyboard.cpp
        world/io/keyboard/Keyboard.h
        world/camera/Camera.cpp
        world/camera/Camera.h
)

target_link_libraries(2023_10_12_vaja_2_piramida glfw glm::glm GLEW::GLEW OpenGL::GL)