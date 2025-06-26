#pragma once
#include "Include.h"

class Map
{
private:
	vector<string> map;

public:
    Map(vector<string> map) { this->map = map; }

    vector<string> getMap()const { return map; }

    void paintWall()const {
        glPushMatrix();
        glBegin(GL_TRIANGLE_STRIP);
        glColor3f(0.2f, 0.2f, 0.2f);
        glVertex2f(0, 0);
        glVertex2f(blockWidth, 0);
        glVertex2f(0, blockHeigth);
        glVertex2f(blockWidth, blockHeigth);
        glEnd();
        glTranslatef(0, blockHeigth, 0);

        glBegin(GL_TRIANGLE_STRIP);
        glColor3f(0.5f, 0.5f, 0.5f);
        glVertex2f(0, 0);
        glVertex2f(blockWidth, 0);
        glVertex2f(0, blockDepth);
        glVertex2f(blockWidth, blockDepth);
        glEnd();

#ifdef debugLines
        glLineWidth(1);
        glBegin(GL_LINE_LOOP);
        glColor3f(0, 0, 0);
        glVertex2f(0, -blockHeigth);
        glVertex2f(0, blockDepth);
        glVertex2f(blockWidth, blockDepth);
        glVertex2f(blockWidth, -blockHeigth);
        glEnd();
#endif
        glPopMatrix();
    }

    void paintFloor()const {
        glBegin(GL_TRIANGLE_STRIP);
        glColor3f(0.7f, 0.7f, 0);
        glVertex2f(0, 0);
        glVertex2f(blockWidth, 0);
        glVertex2f(0, blockDepth);
        glVertex2f(blockWidth, blockDepth);
        glEnd();

#ifdef debugLines
        glLineWidth(1);
        glBegin(GL_LINE_LOOP);
        glColor3f(0, 0, 0);
        glVertex2f(0, 0);
        glVertex2f(0, blockDepth);
        glVertex2f(blockWidth, blockDepth);
        glVertex2f(blockWidth, 0);
        glEnd();
#endif
    }

    void paintVoid()const {
        glBegin(GL_TRIANGLE_STRIP);
        glColor3f(0, 0, 0);
        glVertex2f(0, 0);
        glVertex2f(blockWidth, 0);
        glVertex2f(0, blockDepth);
        glVertex2f(blockWidth, blockDepth);
        glEnd();
    }

    /*
    void paintMap(Player& player)const {
        glPushMatrix();
        glTranslatef(50, windowHeigth - blockHeigth - blockDepth - 50, 0);

        for (int i = 0; i < map.size(); i++)
        {
            for (int j = 0; j < map[i].size(); j++)
            {
                if (map[i][j] == '#')
                    paintWall();
                else if (j == player.getX() && i == player.getY())
                {
                    paintFloor();
                    player.paintPlayer();
                }
                else
                    paintFloor();
                glTranslatef(blockWidth, 0, 0);
            }
            glTranslatef(map[i].size() * -blockWidth, -blockDepth, 0);
        }
        glPopMatrix();
    }*/

    /*
    void paintMap(Player player)const {
        glPushMatrix();
        glTranslatef(50, windowHeigth - blockHeigth - blockDepth - 50, 0);
        int r = 7;
        int d = 2 * r + 1;

        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                if (player.getY() - r + i < 0 || player.getX() - r + j < 0 ||
                    player.getY() - r + i >= map.size() || player.getX() - r + j >= map[i].size())
                    paintVoid();

                else if (map[player.getY() - r + i][player.getX() - r + j] == '#')
                    paintWall();

                else if (j == r && i == r)
                {
                    paintFloor();
                    player.paintPlayer();
                }

                else
                    paintFloor();

                glTranslatef(blockWidth, 0, 0);
            }
            glTranslatef(d * -blockWidth, -blockDepth, 0);
        }
        glPopMatrix();
    }
    */
};

