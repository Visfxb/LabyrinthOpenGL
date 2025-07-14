#pragma once
#include "../Include.h"

namespace Entities {
    namespace Fighters { class Player; }
    namespace Items { class Coin; }
}

class Map
{
private:
	vector<string> map;

public:
    Map() {}
    Map(vector<string> map);
    Map(ifstream& file);

    vector<string> getMap()const;

    bool outOfMap(int x, int y)const;
    void paintWall(initializer_list<paintSettings> arr = {}) const;
    void paintFloor(initializer_list<paintSettings> arr = {}, rgb rgb = rgb(0.7, 0.7, 0))const;
    void paintVoid(initializer_list<paintSettings> arr = {})const;
    void paintMapf(Entities::Fighters::Player& player);
    void paintMap(Entities::Fighters::Player& player, Entities::Items::Coin& coin);

    void loadFromFile(ifstream& file);
    void saveToFile(ofstream& file);
};

