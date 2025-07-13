#include "Map.h"
#include "Coin.h"
#include "Player.h"
using Entities::Items::Coin;
using Entities::Fighters::Player;

Map::Map(vector<string> map)
{
    this->map = map;
}

Map::Map(ifstream& file)
{
    loadFromFile(file);
}

vector<string> Map::getMap() const
{
    return map;
}

bool Map::outOfMap(int x, int y) const
{
    return y < 0 || y >= map.size() || x < 0 || x < 0 >= map[y].size();
}

void Map::paintWall(initializer_list<paintSettings> arr) const
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
    glColor3f(0.2f, 0.2f, 0.2f);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(cutW, 0.0f);
    glVertex2f(0.0f, cutH);
    glVertex2f(cutW, cutH);
    glEnd();
    glTranslatef(0.0f, cutH, 0.0f);

    glBegin(GL_TRIANGLE_STRIP);
    glColor3f(0.5f, 0.5f, 0.5f);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(cutW, 0.0f);
    glVertex2f(0.0f, cutD);
    glVertex2f(cutW, cutD);
    glEnd();

#ifdef debugLines
    for (const auto& item : arr)
    {
        vec = item.vec;
        if (vec == -1) glTranslatef(0.0f, cutD - blockDepth, 0.0f);
        else if (vec == 1) glTranslatef(0.0f, -cutH + blockHeigth, 0.0f);
        else if (vec == 2) glTranslatef((1 - visiblePart) * -blockWidth, 0, 0);
    }

    glLineWidth(1.0f);
    glBegin(GL_LINE_LOOP);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(0.0f, -blockHeigth);
    glVertex2f(0.0f, blockDepth);
    glVertex2f(blockWidth, blockDepth);
    glVertex2f(blockWidth, -blockHeigth);
    glEnd();
#endif
    glPopMatrix();
}

void Map::paintFloor(initializer_list<paintSettings> arr, rgb rgb) const
{
    glPushMatrix();
    int vec = 0;
    float visiblePart = 1;
    float cutW = blockWidth;
    float cutD = blockDepth;
    for (const auto& item : arr) {
        vec = item.vec;
        visiblePart = item.visiblePart;

        if (visiblePart > 1) visiblePart = 1;

        if (vec == 1)
            cutD = blockDepth * visiblePart;
        else if (vec == -2)
            cutW = blockWidth * visiblePart;
        else if (vec == -1)
        {
            cutD = blockDepth * visiblePart;
            glTranslatef(0, (1 - visiblePart) * blockDepth, 0);
        }
        else if (vec == 2)
        {
            cutW = blockWidth * visiblePart;
            glTranslatef((1 - visiblePart) * blockWidth, 0, 0);
        }
    }

    glBegin(GL_TRIANGLE_STRIP);
    glColor3f(rgb.red, rgb.green, rgb.blue);
    glVertex2f(0, 0);
    glVertex2f(cutW, 0);
    glVertex2f(0, cutD);
    glVertex2f(cutW, cutD);
    glEnd();

#ifdef debugLines
    for (const auto& item : arr) {
        vec = item.vec;
        if (vec == -1) glTranslatef(0, (1 - visiblePart) * -blockDepth, 0);
        if (vec == 2) glTranslatef((1 - visiblePart) * -blockWidth, 0, 0);
    }

    glLineWidth(1);
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex2f(0, 0);
    glVertex2f(0, blockDepth);
    glVertex2f(blockWidth, blockDepth);
    glVertex2f(blockWidth, 0);
    glEnd();
#endif
    glPopMatrix();
}

void Map::paintVoid(initializer_list<paintSettings> arr) const
{
    paintFloor(arr, rgb(0, 0, 0));
}

void Map::paintMapf(Entities::Fighters::Player& player)
{
    glPushMatrix();
    glTranslatef(50, windowHeigth - blockHeigth - blockDepth - 50, 0);

    for (int i = 0; i < map.size(); i++)
    {
        for (int j = 0; j < map[i].size(); j++)
        {
            if (map[i][j] == '#')
                paintWall();
            else
                paintFloor();
            glTranslatef(blockWidth, 0, 0);
        }
        glTranslatef(getMap()[i].size() * -blockWidth, -blockDepth, 0);
    }
    glTranslatef(player.getX() * blockWidth, (map.size() - player.getY()) * blockDepth, 0);
    player.paint(*this);
    glPopMatrix();
}

void Map::paintMap(Entities::Fighters::Player& player, Coin& coin)
{
    glPushMatrix();

    int rX = 9;
    int rY = 7;
    int dX = rX * 2 + 1;
    int dY = rY * 2 + 1;

    glTranslatef(0, dY * blockDepth, 0);
    glTranslatef(player.getInBlockX() * -blockWidth, player.getInBlockY() * blockDepth, 0);

    for (int i = 0; i <= dY; i++) {
        for (int j = 0; j <= dX; j++) {
            float visiblePart;
            int mapY = player.getY() - rY + i;
            int mapX = player.getX() - rX + j;
            bool outOfMap = mapY < 0 || mapY >= map.size() ||
                mapX < 0 || mapX >= map[mapY].size();

            // Монета
            if (mapY == coin.getY() && mapX == coin.getX())
            {
                if ((i == 0 || i == dY) && (j == 0 || j == dX)) {
                    coin.paint(*this, { paintSettings(1 - (2 * i / dY), i == 0 ? (blockDepth * (1 - player.getInBlockY())) / (blockDepth + blockHeigth) : 1 - (blockDepth * (1 - player.getInBlockY())) / (blockDepth + blockHeigth)),
                                        paintSettings(2 - (4 * j / dX), j == 0 ? 1 - player.getInBlockX() : player.getInBlockX()) });
                }
                else if (i == 0) {
                    if (player.getInBlockY() != 0)
                        visiblePart = (blockDepth * (1 - player.getInBlockY())) / (blockDepth + blockHeigth);
                    else
                        visiblePart = blockDepth / (blockDepth + blockHeigth);
                    coin.paint(*this, { paintSettings(1, visiblePart) });
                }
                else if (i == dY) {
                    if (player.getInBlockY() != 0)
                        visiblePart = 1 - (blockDepth * (1 - player.getInBlockY())) / (blockDepth + blockHeigth);
                    else
                        visiblePart = blockHeigth / (blockDepth + blockHeigth);
                    coin.paint(*this, { paintSettings(-1, visiblePart) });
                }
                else if (j == 0)
                    coin.paint(*this, { paintSettings(2, 1 - player.getInBlockX()) });
                else if (j == dX)
                    coin.paint(*this, { paintSettings(-2, player.getInBlockX()) });
                else
                    coin.paint(*this);
            }

            //Углы
            else if ((i == 0 || i == dY) && (j == 0 || j == dX))
            {
                if (outOfMap)
                    paintVoid({ paintSettings(1 - (2 * i / dY), i == 0 ? 1 - player.getInBlockY() : player.getInBlockY()),
                                paintSettings(2 - (4 * j / dX), j == 0 ? 1 - player.getInBlockX() : player.getInBlockX()) });
                else if (map[mapY][mapX] == '#')
                    paintWall({ paintSettings(1 - (2 * i / dY), i == 0 ? (blockDepth * (1 - player.getInBlockY())) / (blockDepth + blockHeigth) : 1 - (blockDepth * (1 - player.getInBlockY())) / (blockDepth + blockHeigth)),
                                paintSettings(2 - (4 * j / dX), j == 0 ? 1 - player.getInBlockX() : player.getInBlockX())});
                else
                    paintFloor({paintSettings(1 - (2 * i / dY), i == 0 ? 1 - player.getInBlockY() : player.getInBlockY()),
                                paintSettings(2 - (4 * j / dX), j == 0 ? 1 - player.getInBlockX() : player.getInBlockX())});
            }

            else if (!outOfMap && i == 1 && (j == 0 || j == dX) && map[mapY][mapX] == '#') {
                paintWall({paintSettings(2 - (4 * j / dX), j == 0 ? 1 - player.getInBlockX() : player.getInBlockX()),
                           paintSettings(1, (blockDepth + blockDepth * (1 - player.getInBlockY())) / (blockDepth + blockHeigth))});
            }
            // Левый край
            else if (j == 0 && !outOfMap) {
                if (map[mapY][mapX] == '#')
                    paintWall({ paintSettings(2, 1 - player.getInBlockX()) });
                else
                    paintFloor({ paintSettings(2, 1 - player.getInBlockX()) });
            }
            else if (j == 0 && outOfMap)
                paintVoid({ paintSettings(2, 1 - player.getInBlockX()) });

            // Правый край
            else if (j == dX && !outOfMap) {
                if (map[mapY][mapX] == '#')
                    paintWall({ paintSettings(-2, player.getInBlockX()) });
                else
                    paintFloor({ paintSettings(-2, player.getInBlockX()) });
            }
            else if (j == dX && outOfMap)
                paintVoid({ paintSettings(-2, player.getInBlockX()) });
            // Верхний край
            else if (i == 0 && !outOfMap) {
                if (player.getInBlockY() != 0)
                    visiblePart = (blockDepth * (1 - player.getInBlockY())) / (blockDepth + blockHeigth);
                else
                    visiblePart = blockDepth / (blockDepth + blockHeigth);
                if (map[mapY][mapX] == '#')
                    paintWall({ paintSettings(1, visiblePart) });
                else
                    paintFloor({ paintSettings(1, 1 - player.getInBlockY()) });
            }
            else if (i == 0 && outOfMap)
                paintVoid({ paintSettings(1, 1 - player.getInBlockY()) });
            else if (i == 1 && !outOfMap && map[mapY][mapX] == '#' && player.getInBlockY() != 0)
                paintWall({ paintSettings(1, (blockDepth + blockDepth * (1 - player.getInBlockY())) / (blockDepth + blockHeigth)) });
            // Нижний край
            else if (i == dY && !outOfMap) {
                if (player.getInBlockY() != 0)
                    visiblePart = 1 - (blockDepth * (1 - player.getInBlockY())) / (blockDepth + blockHeigth);
                else
                    visiblePart = blockHeigth / (blockDepth + blockHeigth);

                if (map[mapY][mapX] == '#')
                    paintWall({ paintSettings(-1, visiblePart) });
                else
                    paintFloor({ paintSettings(-1, player.getInBlockY()) });
                if (mapY + 1 < map.size() && map[mapY + 1][mapX] == '#')
                {
                    glPushMatrix();
                    glTranslatef(0, -blockDepth, 0);
                    paintWall({ paintSettings(-1, 1 - (blockDepth + blockDepth * (1 - player.getInBlockY())) / (blockDepth + blockHeigth)) });
                    glPopMatrix();
                }
            }

            // Внутренние блоки
            else if (i == dY && outOfMap)
                paintVoid({ paintSettings(-1, player.getInBlockY()) });
            else {
                if (outOfMap)
                    paintVoid();
                else if (map[mapY][mapX] == '#')
                    paintWall();
                else
                    paintFloor();
            }
            glTranslatef(blockWidth, 0, 0);
        }
        glTranslatef(-(dX + 1) * blockWidth, -blockDepth, 0);
    }

    glTranslatef(rX * blockWidth, (rY + 2) * blockDepth, 0);
    player.paint(*this);
    glPopMatrix();
}

void Map::loadFromFile(ifstream& file)
{
    string line;
    map.clear();
    while (!file.eof()) {
        getline(file, line);
        if (line.size() == 0) continue;
        map.push_back(line);
    }
}

void Map::saveToFile(ofstream& file)
{
    for (string line : map)
        file << line << endl;
}
