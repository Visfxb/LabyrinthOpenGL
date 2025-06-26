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

    bool isWallNext(Map& map, int vec) const {
        float newX = x;
        float newY = y;

        if (vec % 2 == 0) newX += vec / 2 * step;
        else newY += vec * step;

        int x1 = floor(newX);
        int y1 = floor(newY);
        int x2 = ceil(newX);
        int y2 = ceil(newY);

        return map.getMap()[y1][x1] == '#' || map.getMap()[y1][x2] == '#' ||
               map.getMap()[y2][x1] == '#' || map.getMap()[y2][x2] == '#';
    }

    void movePlayer(Map& map, int vec) {
        if (isWallNext(map, vec))
        {
            if (vec % 2 == 0) x = int(x + step);
            else y = int(y + step);
            return;
        }

        if (vec % 2 == 0) x += vec / 2 * step;
        else y += vec * step;
    }

    void paintPlayer()const {
        glPushMatrix();
        glTranslatef((x - int(x)) * blockWidth, (y - int(y)) * -blockDepth, 0);
        glBegin(GL_TRIANGLE_STRIP);
        glColor3f(0.8f, 0, 0);
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

