#include "Player.h"
#include "Map.h"

bool Player::isWallNext(Map& map, int vec) const
{
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

void Player::movePlayer(Map& map, int vec)
{
    if (isWallNext(map, vec))
    {
        if (vec % 2 == 0) x = int(x + step);
        else y = int(y + step);
        return;
    }

    if (vec % 2 == 0) x += vec / 2 * step;
    else y += vec * step;
}
