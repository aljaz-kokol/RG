cmake_minimum_required(VERSION 3.26)
project(2023_10_26_vaja_04_Transformacije_Projekcije)

set(CMAKE_CXX_STANDARD 20)

find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)
find_package(OpenGL REQUIRED)

add_executable(2023_10_26_vaja_04_Transformacije_Projekcije main.cpp
        world/window/OpenGLWindow.cpp
        world/window/OpenGLWindow.h
        object/Mesh.cpp
        object/Mesh.h
        shader/program/ShaderProgram.cpp
        shader/program/ShaderProgram.h
        object/cuboid/Cuboid.cpp
        object/cuboid/Cuboid.h
        buffer/Buffer.h
        buffer/vertex/VertexBuffer.cpp
        buffer/vertex/VertexBuffer.h
        buffer/index/IndexBuffer.cpp
        buffer/index/IndexBuffer.h
        shader/Shader.h
        vertex_array/VertexArray.cpp
        vertex_array/VertexArray.h
        buffer/layout/BufferLayout.cpp
        buffer/layout/BufferLayout.h
        shader/Shader.cpp
        renderer/Renderer.cpp
        renderer/Renderer.h
        object/transformation/Transformation.h
        object/transformation/scale/Scale.cpp
        object/transformation/scale/Scale.h
        object/transformation/translation/Translation.cpp
        object/transformation/translation/Translation.h
        object/transformation/rotation/Rotation.cpp
        object/transformation/rotation/Rotation.h
        color/Color.cpp
        color/Color.h
)

target_link_libraries(2023_10_26_vaja_04_Transformacije_Projekcije glfw glm::glm GLEW::GLEW OpenGL::GL)
