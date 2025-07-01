#pragma once
#include "Player.h"

class Map
{
private:
	vector<string> map;

public:
    Map(vector<string> map) { this->map = map; }

    vector<string> getMap()const { return map; }
    void paintWall(int vec1 = 0, float visiblePart1 = 1.0f, int vec2 = 0, float visiblePart2 = 1.0f) const {
        glPushMatrix();
        int vec;
        float visiblePart;
        float cutW = blockWidth;
        float cutH = blockHeigth;
        float cutD = blockDepth;
        float offsetY = 0.0f;

        for (int i = 0; i < 2; i++)
        {
            if (i == 0) {
                vec = vec1;
                visiblePart = visiblePart1;
            }
            else {
                vec = vec2;
                visiblePart = visiblePart2;
            }

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
        if (vec == -1) glTranslatef(0.0f, cutD - blockDepth, 0.0f);
        else if (vec == 1) glTranslatef(0.0f, -cutH + blockHeigth, 0.0f);
        else if (vec == 2) glTranslatef((1 - visiblePart) * -blockWidth, 0, 0);

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
    void paintFloor(int vec1 = 0, float visiblePart1 = 1.0f, int vec2 = 0, float visiblePart2 = 1.0f, float r = 0.7f, float g = 0.7f, float b = 0)const {
        glPushMatrix();
        int vec;
        float visiblePart;
        float cutW = blockWidth;
        float cutD = blockDepth;

        for (int i = 0; i < 2; i++)
        {
            if (i == 0) {
                vec = vec1;
                visiblePart = visiblePart1;
            }
            else {
                vec = vec2;
                visiblePart = visiblePart2;
            }

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
        glColor3f(r, g, b);
        glVertex2f(0, 0);
        glVertex2f(cutW, 0);
        glVertex2f(0, cutD);
        glVertex2f(cutW, cutD);
        glEnd();

#ifdef debugLines
        if (vec1 == -1 || vec2 == -1) glTranslatef(0, (1 - visiblePart) * -blockDepth, 0);
        if (vec1 == 2 || vec2 == 2) glTranslatef((1 - visiblePart) * -blockWidth, 0, 0);
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
    void paintVoid(int vec1 = 0, float visiblePart1 = 1.0f, int vec2 = 0, float visiblePart2 = 1.0f)const {
        paintFloor(vec1, visiblePart1, vec2, visiblePart2, 0.0f, 0.0f, 0.0f);
    }

    void paintMapf(Player& player) {
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
        player.paintPlayer();
        glPopMatrix();
    }

    void paintMap(Player& player) {
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

                //Углы
                if ((i == 0 || i == dY) && (j == 0 || j == dX))
                {
                    if (outOfMap)
                        paintVoid(1 - (2 * i / dY), i == 0 ? 1 - player.getInBlockY() : player.getInBlockY(), 2 - (4 * j / dX), j == 0 ? 1 - player.getInBlockX() : player.getInBlockX());
                    else if (map[mapY][mapX] == '#')
                        paintWall(1 - (2 * i / dY), i == 0 ? (blockDepth * (1 - player.getInBlockY())) / (blockDepth + blockHeigth) : 1 - (blockDepth * (1 - player.getInBlockY())) / (blockDepth + blockHeigth), 2 - (4 * j / dX), j == 0 ? 1 - player.getInBlockX() : player.getInBlockX());
                    else
                        paintFloor(1 - (2 * i / dY), i == 0 ? 1 - player.getInBlockY() : player.getInBlockY(), 2 - (4 * j / dX), j == 0 ? 1 - player.getInBlockX() : player.getInBlockX());
                }
                // Левый край
                else if (!outOfMap && i == 1 && (j == 0 || j == dX) && map[mapY][mapX] == '#') {
                    paintWall(2 - (4 * j / dX), j == 0 ? 1 - player.getInBlockX() : player.getInBlockX(), 1, (blockDepth + blockDepth * (1 - player.getInBlockY())) / (blockDepth + blockHeigth));
                }
                else if (j == 0 && !outOfMap) {
                    if (map[mapY][mapX] == '#')
                        paintWall(2, 1 - player.getInBlockX());
                    else
                        paintFloor(2, 1 - player.getInBlockX());
                }
                else if (j == 0 && outOfMap)
                    paintVoid(2, 1 - player.getInBlockX());

                // Правый край
                else if (j == dX && !outOfMap) {
                    if (map[mapY][mapX] == '#')
                        paintWall(-2, player.getInBlockX());
                    else
                        paintFloor(-2, player.getInBlockX());
                }
                else if (j == dX && outOfMap)
                    paintVoid(-2, player.getInBlockX());
                // Верхний край
                else if (i == 0 && !outOfMap) {
                    if (player.getInBlockY() != 0)
                        visiblePart = (blockDepth * (1 - player.getInBlockY())) / (blockDepth + blockHeigth);
                    else
                        visiblePart = blockDepth / (blockDepth + blockHeigth);
                    if (map[mapY][mapX] == '#')
                        paintWall(1, visiblePart);
                    else
                        paintFloor(1, 1 - player.getInBlockY());
                }
                else if (i == 0 && outOfMap)
                    paintVoid(1, 1 - player.getInBlockY());
                else if (i == 1 && !outOfMap && map[mapY][mapX] == '#' && player.getInBlockY() != 0)
                    paintWall(1, (blockDepth + blockDepth * (1 - player.getInBlockY())) / (blockDepth + blockHeigth));
                // Нижний край
                else if (i == dY && !outOfMap) {
                    if (player.getInBlockY() != 0)
                        visiblePart = 1 - (blockDepth * (1 - player.getInBlockY())) / (blockDepth + blockHeigth);
                    else
                        visiblePart = blockHeigth / (blockDepth + blockHeigth);

                    if (map[mapY][mapX] == '#')
                        paintWall(-1, visiblePart);
                    else
                        paintFloor(-1, player.getInBlockY());
                    if (mapY + 1 < map.size() && map[mapY + 1][mapX] == '#')
                    {
                        glPushMatrix();
                        glTranslatef(0, -blockDepth, 0);
                        paintWall(-1, 1 - (blockDepth + blockDepth * (1 - player.getInBlockY())) / (blockDepth + blockHeigth));
                        glPopMatrix();
                    }
                }
                else if (i == dY && outOfMap)
                    paintVoid(-1, player.getInBlockY());
                // Внутренние блоки
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
        player.paintPlayer();
        glPopMatrix();
    }
};

