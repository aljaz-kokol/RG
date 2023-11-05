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

class OpenGLWindow {
private:
    static void handleKeyPress(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void handeMouseMove(GLFWwindow* window, double xPos, double yPos);
    Keyboard keyboard;
    Mouse mouse;
    Camera camera;

    glm::mat4 projection;

    std::shared_ptr<GLFWwindow> window;
    GLint bufferWidth;
    GLint bufferHeight;

    GLfloat deltaTime;
public:
    OpenGLWindow(std::string_view name, GLint width, GLint height);
    ~OpenGLWindow();
    void closeWindow() const;
    void swapBuffers() const;
    [[nodiscard]] bool shouldClose() const;
    void setProjectionToPerspective();
    void setProjectionToOrthographic();
    void addKeyAction(uint16_t key, const std::function<void(GLfloat)>& action);
    void setKeyActions(const std::vector<std::pair<uint16_t, const std::function<void(GLfloat)>>>& actions);
    void run(const ShaderProgram& program, const std::function<void()>& func);
    void moveCamera(Direction direction);
};


#endif
