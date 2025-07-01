#pragma once
#include "Entity.h"

class Player :
    public Entity
{
private:
    //int coins;
    float step;
public:
    void setStep(float step) { this->step = step; }
    float getStep()const { return step; }

    bool isWallNext(Map& map, int vec) const;
    void movePlayer(Map& map, int vec);

    void paintPlayer()const {
        glPushMatrix();
        glTranslatef((x - int(x)) * blockWidth, (y - int(y)) * -blockDepth, 0);
        glBegin(GL_TRIANGLE_STRIP);
        glColor3f(0.7f, 0, 0);
        glVertex2f(0, 0);
        glVertex2f(blockWidth, 0);
        glVertex2f(0, blockHeigth);
        glVertex2f(blockWidth, blockHeigth);
        glEnd();
        glTranslatef(0, blockHeigth, 0);

        glBegin(GL_TRIANGLE_STRIP);
        glColor3f(1, 0, 0);
        glVertex2f(0, 0);
        glVertex2f(blockWidth, 0);
        glVertex2f(0, blockDepth);
        glVertex2f(blockWidth, blockDepth);
        glEnd();
        glPopMatrix();
    }
};

