#pragma once
#include "Include.h"
class Map;

class Entity
{
protected:
	float x;
	float y;

public:
	bool isValid(Map& map, int x, int y)const;

	void setXY(Map& map, int x, int y);
	void setXY(Map& map, int startX, int endX, int startY, int endY);

	int getX()const { return int(x); }
	int getY()const { return int(y); }
	int getXf()const { return x; }
	int getYf()const { return y; }

	float getInBlockX()const { return x - int(x); }
	float getInBlockY()const { return y - int(y); }
};

