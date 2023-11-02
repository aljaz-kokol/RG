#ifndef INC_2023_10_12_VAJA_2_PIRAMIDA_OPENGLWINDOW_H
#define INC_2023_10_12_VAJA_2_PIRAMIDA_OPENGLWINDOW_H

#include <memory>
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../io/keyboard/Keyboard.h"

class OpenGLWindow {
private:
    static void handleKeyPress(GLFWwindow* window, int key, int scancode, int action, int mods);
    std::shared_ptr<GLFWwindow> window;
    GLint bufferWidth;
    GLint bufferHeight;
    Keyboard keyboard;
public:
    OpenGLWindow(const std::string &name, GLint width, GLint height);
    ~OpenGLWindow();
    void closeWindow() const;
    void swapBuffers() const;
    void addKeyAction(uint16_t key, const std::function<void()>& action);
    [[nodiscard]] bool shouldClose() const;
    [[nodiscard]] GLint getBufferWidth() const;
    [[nodiscard]] GLint getBufferHeight() const;
};


#endif
