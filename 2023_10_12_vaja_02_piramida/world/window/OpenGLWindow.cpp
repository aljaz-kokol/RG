#include "OpenGLWindow.h"
#include <exception>
#include <iostream>

OpenGLWindow::OpenGLWindow(const std::string &name, GLint width, GLint height)
: window(nullptr), bufferHeight(0), bufferWidth(0) {
    if (!glfwInit()) {
        glfwTerminate();
        throw std::runtime_error("GLFW : create error");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    window = std::shared_ptr<GLFWwindow>(glfwCreateWindow(width, height, name.c_str(), nullptr, nullptr), glfwDestroyWindow);

    if (!window) {
        glfwTerminate();
        throw std::runtime_error("GLFW : window creation error");
    }

    glfwGetFramebufferSize(window.get(), &bufferWidth, &bufferHeight);
    glfwMakeContextCurrent(window.get());

    if (glewInit() != GLEW_OK) {
        glfwDestroyWindow(window.get());
        glfwTerminate();
        throw std::runtime_error("GLEW : create error");
    }

    glViewport(0, 0, bufferWidth, bufferHeight);
    glEnable(GL_DEPTH_TEST);
    glewExperimental = GL_TRUE;

    glfwSetWindowUserPointer(window.get(), this);
    glfwSetKeyCallback(window.get(), OpenGLWindow::handleKeys);
    glfwSetInputMode(window.get(), GLFW_CURSOR, GLFW_CURSOR_DISABLED); // hide cursor
}

OpenGLWindow::~OpenGLWindow() {
    glfwDestroyWindow(window.get());
    glfwTerminate();
}

bool OpenGLWindow::shouldClose() const {
    return glfwWindowShouldClose(window.get());
}

void OpenGLWindow::swapBuffers() const {
    glfwSwapBuffers(window.get());
}

GLint OpenGLWindow::getBufferWidth() const {
    return bufferWidth;
}

GLint OpenGLWindow::getBufferHeight() const {
    return bufferHeight;
}

void OpenGLWindow::closeWindow() const {
    glfwSetWindowShouldClose(window.get(), GL_TRUE);
}


void OpenGLWindow::handleKeys(GLFWwindow *targetWindow, int key, int code, int action, int mode) {
    OpenGLWindow* owner = static_cast<OpenGLWindow*>(glfwGetWindowUserPointer(targetWindow));
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        owner->closeWindow();
    }
    owner->keyboard.setKey(key, action);
}