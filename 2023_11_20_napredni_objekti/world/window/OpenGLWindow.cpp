#include "OpenGLWindow.h"
#include "../../renderer/Renderer.h"

void OpenGLWindow::handleKeyPress(GLFWwindow *window, int key, int scancode, int action, int mods) {
    OpenGLWindow* owner = static_cast<OpenGLWindow*>(glfwGetWindowUserPointer(window));
    owner->keyboard.handleOnKeyAction(key, action, owner->deltaTime);
}

void OpenGLWindow::handeMouseMove(GLFWwindow *window, double xPos, double yPos) {
    OpenGLWindow* owner = static_cast<OpenGLWindow*>(glfwGetWindowUserPointer(window));
    owner->mouse.handleOnMove(xPos, yPos);
}

OpenGLWindow::OpenGLWindow(std::string_view name, GLint width, GLint height)
        : window(nullptr), bufferHeight(0), bufferWidth(0), camera(-90, 0, 6.0f, 0.15f), deltaTime(0.0) {
    if (!glfwInit()) {
        glfwTerminate();
        throw std::runtime_error("GLFW : create error");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    window = std::shared_ptr<GLFWwindow>(glfwCreateWindow(width, height, name.data(), nullptr, nullptr), glfwDestroyWindow);

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
    glfwSetKeyCallback(window.get(), OpenGLWindow::handleKeyPress);
    glfwSetCursorPosCallback(window.get(), OpenGLWindow::handeMouseMove);
    glfwSetInputMode(window.get(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    projection = glm::perspective(glm::radians(70.0f), (GLfloat)bufferWidth / (GLfloat)bufferHeight, 0.1f, 100.0f);
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

void OpenGLWindow::closeWindow() const {
    glfwSetWindowShouldClose(window.get(), GL_TRUE);
}

void OpenGLWindow::addKeyAction(uint16_t key, const std::function<void(GLfloat)> &action) {
    keyboard.setOnPress(key, action);
}

void OpenGLWindow::setKeyActions(const std::vector<std::pair<uint16_t, const std::function<void(GLfloat)>>> &actions) {
    for (auto & action : actions) {
        addKeyAction(action.first, action.second);
    }
}

void OpenGLWindow::run(const ShaderProgram& program, const std::function<void()> &func) {
    GLfloat lastTime = 0.0f;
    while (!shouldClose()) {
        GLfloat now = glfwGetTime();
        deltaTime = now - lastTime;
        lastTime = now;

        glfwPollEvents();
        program.bind();
        Renderer::clear();

        camera.rotate(mouse.getXChangeAndReset(), mouse.getYChangeAndReset());
        keyboard.handlePressedKeys(deltaTime);

        program.setUniform("view", camera.getViewMatrix());
        program.setUniform("projection", projection);

        func();

        program.unbind();
        swapBuffers();
    }
}

void OpenGLWindow::moveCamera(Direction direction) {
    camera.move(direction, deltaTime);
}

void OpenGLWindow::setProjectionToPerspective() {
    projection = glm::perspective(glm::radians(70.0f), (GLfloat)bufferWidth / (GLfloat)bufferHeight, 0.1f, 100.0f);
}

void OpenGLWindow::setProjectionToOrthographic() {
    float farPlane = 100.0f;

    // Define the size of your viewing volume (e.g., width, height, and depth)
    float left = -2.5f;
    float right = 2.5f;
    float bottom = -2.5f;
    float top = 2.5f;

// Create the orthographic projection matrix
    projection = glm::ortho(left, right, bottom, top, -farPlane, farPlane);
}