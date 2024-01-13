#ifndef INC_2023_10_26_VAJA_04_TRANSFORMACIJE_PROJEKCIJE_MOUSE_H
#define INC_2023_10_26_VAJA_04_TRANSFORMACIJE_PROJEKCIJE_MOUSE_H

#include <GL/glew.h>
#include <functional>

class Mouse {
private:
    GLfloat lastX;
    GLfloat lastY;
    GLfloat yChange;
    GLfloat xChange;
    bool firstMove;
    std::function<void()> onClick;
public:
    Mouse();
    void handleOnMove(double xPos, double yPos);
    void setOnClick(const std::function<void()>& onClick);
    void click() const;

    [[nodiscard]] GLfloat getYChangeAndReset();
    [[nodiscard]] GLfloat getXChangeAndReset();
    [[nodiscard]] GLfloat getLastX() const;
    [[nodiscard]] GLfloat getLastY() const;
};

#endif