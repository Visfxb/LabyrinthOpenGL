#include "Entity.h"
#include "Map.h"

bool Entity::isValid(Map& map, int x, int y) const
{
	if (x >= 0 && x < map.getMap()[0].size() && y >= 0 && y < map.getMap().size())
		if (map.getMap()[y][x] != '#')
			return true;
	return false;
}

void Entity::setXY(Map& map, int x, int y)
{
	if (isValid(map, x, y))
	{
		this->x = float(x);
		this->y = float(y);
	}

}

void Entity::setXY(Map& map, int startX, int endX, int startY, int endY)
{
	int randX;
	int randY;
	do {
		randX = rand() % (endX - startX) + startX;
		randY = rand() % (endY - startY) + startY;
	} while (isValid(map, randX, randY));
	x = float(randX);
	y = float(randY);
}