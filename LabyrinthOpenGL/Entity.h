#pragma once
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Entity
{
protected:
	int x;
	int y;

public:
	bool isValid(vector<string> map, int x, int y)const {
		if (x >= 0 && x < map[0].size() && y >= 0 && y < map.size())
			if (map[x][y] != '#')
				return true;
		return false;
	}

	void setXY(vector<string> map, int x, int y) {
		if (isValid(map, x, y))
		{
			this->x = x; this->y = y;
		}

	};

	void setXY(vector<string> map, int startX, int endX, int startY, int endY) {
		int randX;
		int randY;
		do {
			randX = rand() % (endX - startX) + startX;
			randY = rand() % (endY - startY) + startY;
		} while (isValid(map, randX, randY));
		x = randX;
		y = randY;
	};

	int getX()const { return x; };
	int getY()const { return y; };
};

