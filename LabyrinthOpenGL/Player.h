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
            return map[x][y + vec / 2] == '#';
        else
            return map[x + vec][y] == '#';
    }

    void movePlayer(vector<string> map, int vec) { //w = -1   a = -2   s = 1   d = 2
        if (isWallNext(map, vec))
            return;

        if (vec % 2 == 0)
            y += vec / 2;
        else
            x += vec;
    };
};

