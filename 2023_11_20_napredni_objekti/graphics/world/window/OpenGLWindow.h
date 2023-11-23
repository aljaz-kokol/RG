#ifndef INC_2023_10_12_VAJA_2_PIRAMIDA_OPENGLWINDOW_H
#define INC_2023_10_12_VAJA_2_PIRAMIDA_OPENGLWINDOW_H

#include <memory>
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../io/keyboard/Keyboard.h"
#include "../io/mouse/Mouse.h"
#include "../camera/Camera.h"
#include "../../shader/program/ShaderProgram.h"
#include "../../object/model/Model.h"

class OpenGLWindow {
private:
    static void handleKeyPress(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void handeMouseMove(GLFWwindow* window, double xPos, double yPos);
    static void handeMouseClick(GLFWwindow* window, int button, int action, int mods);

    Keyboard keyboard;
    Mouse mouse;
    Camera camera;

    glm::mat4 projection;
    GLint bufferWidth;
    GLint bufferHeight;
    GLfloat deltaTime;

    uint32_t selectedModel;

    std::shared_ptr<GLFWwindow> window;
    std::vector<std::shared_ptr<Model>> drawModels;
public:
    OpenGLWindow(std::string_view name, GLint width, GLint height);
    ~OpenGLWindow();
    void closeWindow() const;
    void swapBuffers() const;
    void setProjectionToPerspective();
    void setProjectionToOrthographic();
    void addKeyAction(uint16_t key, const std::function<void(GLfloat)>& action);
    void setKeyActions(const std::vector<std::pair<uint16_t, const std::function<void(GLfloat)>>>& actions);
    void run(const ShaderProgram& program, const std::function<void()>& func);
    void moveCamera(Direction direction);
    void addDrawModel(const std::shared_ptr<Model>& model);
    void setOnClick(const std::function<void()>& onClick);
    void selectNextModel();
    void moveSelectedModel(const Direction& direction) const;

    [[nodiscard]] bool shouldClose() const;
    [[nodiscard]] const Camera& getCamera() const;
    [[nodiscard]] const Mouse& getMouse() const;
    [[nodiscard]] GLint getBufferWidth() const;
    [[nodiscard]] GLint getBufferHeight() const;

};


#endif
