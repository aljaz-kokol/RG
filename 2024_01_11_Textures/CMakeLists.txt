cmake_minimum_required(VERSION 3.27)
project(2024_01_11_Textures)

set(CMAKE_CXX_STANDARD 23)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)
find_package(OpenGL REQUIRED)
find_package(assimp REQUIRED)
find_package(Freetype REQUIRED)

add_executable(2024_01_11_Textures main.cpp
        graphics/world/window/OpenGLWindow.cpp
        graphics/world/window/OpenGLWindow.h
        graphics/object/Mesh.cpp
        graphics/object/Mesh.h
        graphics/shader/program/ShaderProgram.cpp
        graphics/shader/program/ShaderProgram.h
        graphics/object/cuboid/Cuboid.cpp
        graphics/object/cuboid/Cuboid.h
        graphics/buffer/Buffer.h
        graphics/buffer/vertex/VertexBuffer.cpp
        graphics/buffer/vertex/VertexBuffer.h
        graphics/buffer/index/IndexBuffer.cpp
        graphics/buffer/index/IndexBuffer.h
        graphics/shader/Shader.h
        graphics/vertex_array/VertexArray.cpp
        graphics/vertex_array/VertexArray.h
        graphics/buffer/layout/BufferLayout.cpp
        graphics/buffer/layout/BufferLayout.h
        graphics/shader/Shader.cpp
        graphics/renderer/Renderer.cpp
        graphics/renderer/Renderer.h
        graphics/object/transformation/Transformation.h
        graphics/object/transformation/scale/Scale.cpp
        graphics/object/transformation/scale/Scale.h
        graphics/object/transformation/translation/Translation.cpp
        graphics/object/transformation/translation/Translation.h
        graphics/object/transformation/rotation/Rotation.cpp
        graphics/object/transformation/rotation/Rotation.h
        graphics/color/Color.cpp
        graphics/color/Color.h
        graphics/world/io/keyboard/Keyboard.cpp
        graphics/world/camera/Camera.cpp
        graphics/world/camera/Camera.h
        graphics/world/io/mouse/Mouse.cpp
        graphics/world/io/mouse/Mouse.h
        graphics/utils/DrawMode.h
        graphics/stb_image.h
        graphics/texture/Texture.h
        graphics/texture/Texture.cpp
        graphics/object/texture-mesh/TextureMesh.cpp
        graphics/object/texture-mesh/TextureMesh.h
        graphics/material/Material.cpp
        graphics/material/Material.h
        graphics/object/model/Model.cpp
        graphics/object/model/Model.h
        graphics/world/light/Light.h
        graphics/world/light/Light.cpp
        toolbar/Toolbar.cpp
        toolbar/Toolbar.h
        graphics/utils/font/Font.cpp
        graphics/utils/font/Font.h
        graphics/utils/font/TextRenderer.cpp
        graphics/utils/font/TextRenderer.h
        graphics/world/light/ambient/AmbientLight.cpp
        graphics/world/light/ambient/AmbientLight.h
        graphics/world/light/diffuse/DiffuseLight.cpp
        graphics/world/light/diffuse/DiffuseLight.h
        graphics/world/light/Lighting.cpp
        graphics/world/light/Lighting.h
        graphics/utils/RotationDirection.h
)

target_link_libraries(2024_01_11_Textures assimp::assimp Freetype::Freetype glfw glm::glm GLEW::GLEW OpenGL::GL)