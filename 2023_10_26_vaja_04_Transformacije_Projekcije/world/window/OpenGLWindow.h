#ifndef INC_2023_10_12_VAJA_2_PIRAMIDA_OPENGLWINDOW_H
#define INC_2023_10_12_VAJA_2_PIRAMIDA_OPENGLWINDOW_H

#include <memory>
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class OpenGLWindow {
private:
    std::shared_ptr<GLFWwindow> window;
    GLint bufferWidth;
    GLint bufferHeight;
public:
    OpenGLWindow(const std::string &name, GLint width, GLint height);
    ~OpenGLWindow();
    void closeWindow() const;
    void swapBuffers() const;
    [[nodiscard]] bool shouldClose() const;
    [[nodiscard]] GLint getBufferWidth() const;
    [[nodiscard]] GLint getBufferHeight() const;
};


#endif
