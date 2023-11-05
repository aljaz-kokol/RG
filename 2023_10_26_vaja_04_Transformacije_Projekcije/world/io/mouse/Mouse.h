#ifndef INC_2023_10_26_VAJA_04_TRANSFORMACIJE_PROJEKCIJE_MOUSE_H
#define INC_2023_10_26_VAJA_04_TRANSFORMACIJE_PROJEKCIJE_MOUSE_H

#include <GL/glew.h>

class Mouse {
private:
    GLfloat lastX;
    GLfloat lastY;
    GLfloat yChange;
    GLfloat xChange;
    bool firstMove;
public:
    Mouse();
    void handleOnMove(double xPos, double yPos);
    [[nodiscard]] GLfloat getYChangeAndReset();
    [[nodiscard]] GLfloat getXChangeAndReset();
};

#endif