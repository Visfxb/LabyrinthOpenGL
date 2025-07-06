#pragma once
#include "Include.h"
class Map;

namespace Entities
{
	class Entity
	{
	protected:
		float x;
		float y;

	public:
		virtual ~Entity() {};

		int getX()const { return int(x); }
		int getY()const { return int(y); }
		float getInBlockX()const { return x - int(x); }
		float getInBlockY()const { return y - int(y); }

		virtual void paint(Map& map, initializer_list<paintSettings> arr = {})const = 0;
	};
}

