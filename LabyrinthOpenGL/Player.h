#pragma once
#include "Entity.h"

class Player :
    public Entity
{
private:
    //int coins;
public:
    bool isWallNext(vector<string> map, int vec)const {
        if (vec % 2 == 0)
            return map[y][x + vec / 2] == '#';
        else
            return map[y + vec][x] == '#';
    }

    void movePlayer(vector<string> map, int vec) { //w = -1   a = -2   s = 1   d = 2
        if (isWallNext(map, vec))
            return;

        if (vec % 2 == 0) x += vec / 2;
        else y += vec;
    }

    void paintPlayer()const {
        glPushMatrix();
        glLineWidth(5);
        glBegin(GL_LINES);
            glColor3f(0, 0, 0);
            glVertex2f(blockWidth / 2, 0);
            glVertex2f(blockWidth / 2, blockHeigth / cos(alpha * PI / 180.0) * 0.75);
        glEnd();
        glPopMatrix();
    }
};

