#include "Player.h"
#include "Coin.h"
#include "Map.h"

using Entities::Items::Coin;
using Entities::Fighters::Player;

Entities::Fighters::Player::Player(int x, int y, float step, Map& map, int delay)
{
    if (y >= 0 && y < map.getMap().size() &&
        x >= 0 && x < map.getMap()[y].size() && map.getMap()[y][x] != '#')
    {
        this->x = float(x);
        this->y = float(y);
        this->step = float(step);
        this->delay = delay;
        coins = 0;
        lastInputTick = high_resolution_clock::now();
    }
    else
        randXY(map);
}
void Entities::Fighters::Player::randXY(Map& map)
{
    int newY = rand() % map.getMap().size();
    int newX = rand() % map.getMap()[newY].size();
    while (map.getMap()[newY][newX] == '#') {
        newY = rand() % map.getMap().size();
        newX = rand() % map.getMap()[newY].size();
    }
    x = float(newX);
    y = float(newY);
    lastInputTick = high_resolution_clock::now();
}
bool Entities::Fighters::Player::isWallNext(Map& map, int vec) const
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
void Entities::Fighters::Player::movePlayer(Map& map, Entities::Items::Coin& coin, int vec)
{
    if (isWallNext(map, vec))
    {
        if (vec % 2 == 0) x = floor(x + step);
        else y = floor(y + step);
        return;
    }
    if (vec % 2 == 0) x += vec / 2 * step;
    else y += vec * step;
    x = round(x * 10.f) / 10;
    y = round(y * 10.f) / 10;

    if ((int(x) == coin.getX() || ceil(x) == coin.getX()) &&
        (int(y) == coin.getY() || ceil(y) == coin.getY()))
    {
        coins++;
        coin.randXY(map);
    }
}
void Entities::Fighters::Player::paint(Map& map, initializer_list<paintSettings> arr) const
{
    (void)arr;
    glPushMatrix();
    glTranslatef((x - int(x)) * blockWidth, (y - int(y)) * -blockDepth, 0);
    glBegin(GL_TRIANGLE_STRIP);
    glColor3f(0.6f, 0, 0);
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
    glPushMatrix();
    if (this->getInBlockY() == 0) glTranslatef(-blockWidth, -blockDepth, 0);
    else glTranslatef(-blockWidth, -2 * blockDepth, 0);
    for (int i = 0; i < 3; i++)
    {
        if (!map.outOfMap(x - 1 + i, ceil(y) + 1) && map.getMap()[ceil(y) + 1][x - 1 + i] == '#')
            if (!map.outOfMap(x - 1 + i, ceil(y) + 2) && map.getMap()[ceil(y) + 2][x - 1 + i] == '#')
                map.paintWall({ { -1, blockDepth / (blockDepth + blockHeigth)} });
            else
                map.paintWall({ {-1, blockHeigth / (blockDepth + blockHeigth)} });
        glTranslatef(blockWidth, 0, 0);
    }
    glPopMatrix();
}

void Entities::Fighters::Player::loadFromFile(ifstream& file)
{
    file >> x >> y >> step >> coins;
}

void Entities::Fighters::Player::saveToFile(ofstream& file)
{
    file << "Player " << x << " " << y << " " << step << " " << coins << endl;
}
