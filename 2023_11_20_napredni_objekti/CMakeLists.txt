cmake_minimum_required(VERSION 3.26)
project(2023_11_20_napredni_objekti)

set(CMAKE_CXX_STANDARD 23)

find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)
find_package(OpenGL REQUIRED)
find_package(assimp REQUIRED)

add_executable(2023_11_20_napredni_objekti main.cpp
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
        object/cuboid/cuboid-shape/CuboidShape.cpp
        object/cuboid/cuboid-shape/CuboidShape.h
        object/cuboid/cuboid-shape/cuboid-shape-element/CuboidShapeElement.cpp
        world/io/keyboard/Keyboard.cpp
        world/camera/Camera.cpp
        world/camera/Camera.h
        world/io/mouse/Mouse.cpp
        world/io/mouse/Mouse.h
        utils/DrawMode.h
        stb_image.h
        texture/Texture.h
        texture/Texture.cpp
        object/texture-mesh/TextureMesh.cpp
        object/texture-mesh/TextureMesh.h
        material/Material.cpp
        material/Material.h
        object/model/Model.cpp
        object/model/Model.h
)

target_link_libraries(2023_11_20_napredni_objekti assimp::assimp glfw glm::glm GLEW::GLEW OpenGL::GL)
