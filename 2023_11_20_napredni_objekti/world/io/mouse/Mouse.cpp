#include "Mouse.h"

Mouse::Mouse()
: lastX(0), lastY(0), yChange(0), xChange(0), firstMove(true) {}

void Mouse::handleOnMove(double xPos, double yPos) {
    if (firstMove) {
        lastX = xPos;
        lastY = yPos;
        firstMove = false;
    }
    xChange = xPos - lastX;
    yChange = yPos - lastY;

    lastX = xPos;
    lastY = yPos;
}

GLfloat Mouse::getYChangeAndReset() {
    GLfloat yChange = this->yChange;
    this->yChange = 0;
    return yChange;
}

GLfloat Mouse::getXChangeAndReset() {
    GLfloat xChange = this->xChange;
    this->xChange = 0;
    return xChange;
}
