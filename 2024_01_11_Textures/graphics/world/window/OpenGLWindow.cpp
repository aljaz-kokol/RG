#include "OpenGLWindow.h"
#include "../../renderer/Renderer.h"
#include "../../object/cuboid/Cuboid.h"
#include "../../utils/font/Font.h"

void OpenGLWindow::handleKeyPress(GLFWwindow *window, int key, int scancode, int action, int mods) {
    OpenGLWindow* owner = static_cast<OpenGLWindow*>(glfwGetWindowUserPointer(window));
    if (key == GLFW_KEY_TAB && action == GLFW_RELEASE) {
        owner->keyboard.execute(key, GLFW_PRESS);
        owner->keyboard.handleOnKeyAction(key, action, owner->deltaTime);
    } else if (key != GLFW_KEY_TAB) {
        owner->keyboard.handleOnKeyAction(key, action, owner->deltaTime);
    }
}

void OpenGLWindow::handeMouseMove(GLFWwindow *window, double xPos, double yPos) {
    OpenGLWindow* owner = static_cast<OpenGLWindow*>(glfwGetWindowUserPointer(window));
    owner->mouse.handleOnMove(xPos, yPos);
}

void OpenGLWindow::handeMouseClick(GLFWwindow *window, int button, int action, int mods) {
    OpenGLWindow* owner = static_cast<OpenGLWindow*>(glfwGetWindowUserPointer(window));
    if (action == GLFW_RELEASE) {
        owner->mouse.click();
    }
}

OpenGLWindow::OpenGLWindow(std::string_view name, GLint width, GLint height)
: window(nullptr), bufferHeight(0), bufferWidth(0), camera(-90, 0, 6.0f, 0.15f), deltaTime(0.0f), selectedModel(0) {
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
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glewExperimental = GL_TRUE;

    glfwSetWindowUserPointer(window.get(), this);
    glfwSetKeyCallback(window.get(), OpenGLWindow::handleKeyPress);
    glfwSetCursorPosCallback(window.get(), OpenGLWindow::handeMouseMove);
    glfwSetMouseButtonCallback(window.get(), OpenGLWindow::handeMouseClick);
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

void OpenGLWindow::moveSelectedModel(const Direction &direction) const {
    drawModels[selectedModel]->move(direction, 1.5, deltaTime);
}

void OpenGLWindow::rotateSelectedModel(const RotationDirection &direction) const {
    drawModels[selectedModel]->rotate(direction, 10, deltaTime);
}

void OpenGLWindow::run(const ShaderProgram& program, const std::function<void()> &func) {
    GLfloat lastTime = 0.0f;
    Cuboid cursor(program, 0.1, 0.1, 0.1);

    Font font("assets/fonts/Roboto/Roboto-Regular.ttf");

    while (!shouldClose()) {
        GLfloat now = glfwGetTime();
        deltaTime = now - lastTime;
        lastTime = now;
        glfwPollEvents();
        program.bind();
        Renderer::clear();

        cursor.setColor(Color::WHITE);
        cursor.applyTransformationsFixedToCamera("model", camera, {
                std::make_shared<Translation>(glm::vec3{0, 0, -2}),
                std::make_shared<Scale>(0.1),
        });
        Renderer::draw<DrawMode::TRIANGLES>(cursor);

        camera.rotate(mouse.getXChangeAndReset(), mouse.getYChangeAndReset());
        keyboard.handlePressedKeys(deltaTime);
        program.setUniform("view", camera.getViewMatrix());
        program.setUniform("eyePosition", camera.getPosition());
        program.setUniform("projection", projection);

        func();

        for (size_t i = 0; i < drawModels.size(); i++) {
            if (i == selectedModel) {
                drawModels[i]->setColor(Color::RED);
            } else {
                drawModels[i]->setColor(Color::WHITE);
            }
            drawModels[i]->draw();
        }

        program.unbind();
        textRenderer.renderPushed();
        textRenderer.clearPushed();
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
    projection = glm::mat4(1);
}

const Camera &OpenGLWindow::getCamera() const {
    return camera;
}

const Mouse &OpenGLWindow::getMouse() const {
    return mouse;
}

bool OpenGLWindow::selectModel() {
    for (uint32_t i = 0; i < drawModels.size(); i++) {
        if (camera.pointingAtPosition(drawModels[i]->getPositions())) {
            selectedModel = i;
            return true;
        }
    }
    return false;
}

void OpenGLWindow::setTextRenderShader(const std::shared_ptr<ShaderProgram> &textShaderProgram) {
    textRenderer.setTextShaderProgram(textShaderProgram);
}

void OpenGLWindow::addFont(const std::string &name, std::string_view fontPath) {
    textRenderer.addFont(name, fontPath);
}

void OpenGLWindow::renderText(const std::string &font, const std::string &text, float x, float y, float scale, const Color &color) {
    textRenderer.pushRender(font, text, x, y, scale, color);
}

void OpenGLWindow::addDrawModel(const std::shared_ptr<Model> &model) {
    drawModels.push_back(model);
}

void OpenGLWindow::setOnClick(const std::function<void()> &onClick) {
    mouse.setOnClick(onClick);
}

GLint OpenGLWindow::getBufferWidth() const {
    return bufferWidth;
}

GLint OpenGLWindow::getBufferHeight() const {
    return bufferHeight;
}

void OpenGLWindow::selectNextModel() {
    selectedModel = (selectedModel + 1) % drawModels.size();
}