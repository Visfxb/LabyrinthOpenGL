#include "Coin.h"
#include "Map.h"

Entities::Items::Coin::Coin(Map& map)
{
    randXY(map);
}
Entities::Items::Coin::Coin(Map& map, int x, int y)
{
    if (map.getMap()[y][x] != '#')
    {
        this->x = float(x);
        this->y = float(y);
    }
}
void Entities::Items::Coin::randXY(Map& map)
{
    int newY = rand() % map.getMap().size();
    int newX = rand() % map.getMap()[newY].size();
    while (map.getMap()[newY][newX] == '#') {
        newY = rand() % map.getMap().size();
        newX = rand() % map.getMap()[newY].size();
    }
    x = float(newX);
    y = float(newY);
}
void Entities::Items::Coin::paint(Map& map, initializer_list<paintSettings> arr) const
{
    glPushMatrix();
    int vec = 0;
    float visiblePart = 1;
    float cutW = blockWidth;
    float cutH = blockHeigth;
    float cutD = blockDepth;
    float offsetY = 0.0f;

    for (const auto& item : arr)
    {
        vec = item.vec;
        visiblePart = item.visiblePart;

        if (visiblePart > 1) visiblePart = 1;
        if (vec == -1) {
            visiblePart = 1 - visiblePart;
            offsetY = (blockDepth + blockHeigth) * -vec * visiblePart;
            cutH = blockHeigth - offsetY;
            cutD = blockDepth;
            if (cutH < 0.0f) {
                cutD = max(0.0f, cutD - abs(cutH));
                cutH = 0.0f;
            }
            glTranslatef(0.0f, offsetY, 0.0f);
        }
        else if (vec == 1) {
            visiblePart = 1 - visiblePart;
            offsetY = (blockDepth + blockHeigth) * vec * visiblePart;
            cutD = blockDepth - offsetY;
            cutH = blockHeigth;
            if (cutD < 0.0f) {
                cutH = max(0.0f, cutH - abs(cutD));
                cutD = 0.0f;
            }
        }
        else if (vec == -2) {
            cutW = blockWidth * visiblePart;
        }
        else if (vec == 2) {
            cutW = blockWidth * visiblePart;
            glTranslatef((1 - visiblePart) * blockWidth, 0, 0);
        }
    }

    glBegin(GL_TRIANGLE_STRIP);
    glColor3f(0.5f, 0.5f, 0);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(cutW, 0.0f);
    glVertex2f(0.0f, cutH);
    glVertex2f(cutW, cutH);
    glEnd();
    glTranslatef(0.0f, cutH, 0.0f);

    glBegin(GL_TRIANGLE_STRIP);
    glColor3f(1, 1, 0);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(cutW, 0.0f);
    glVertex2f(0.0f, cutD);
    glVertex2f(cutW, cutD);
    glEnd();
    glPopMatrix();
}

void Entities::Items::Coin::loadFromFile(ifstream& file)
{
    file >> x >> y;
}

void Entities::Items::Coin::saveToFile(ofstream& file)
{
    file << "Coin " << x << " " << y << endl;
}
