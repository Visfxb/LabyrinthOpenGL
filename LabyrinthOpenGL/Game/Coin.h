#pragma once
#include "Entity.h"

class Map;

namespace Entities {
    namespace Items {

        class Coin :
            public Entities::Entity
        {
        public:
            Coin() {};
            Coin(Map& map);
            Coin(Map& map, int x, int y);

            void randXY(Map& map);
            void paint(Map& map, initializer_list<paintSettings> arr = {})const override;
            void loadFromFile(ifstream& file) override;
            void saveToFile(ofstream& file) override;
        };
    }
}