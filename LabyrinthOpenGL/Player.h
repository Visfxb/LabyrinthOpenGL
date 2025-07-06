#pragma once
#include "Entity.h"

class Map;
namespace Entities {
    namespace Items{ class Coin; }
}

namespace Entities {
    namespace Fighters
    {
        class Player :
            public Entities::Entity
        {
        private:
            int coins;
            float step;
        public:
            Player(int x, int y, float step, Map& map);
            float getStep()const { return step; }
            int getCoins()const { return coins; }

            bool isWallNext(Map& map, int vec) const;
            void movePlayer(Map& map, Entities::Items::Coin& coin, int vec);
            void paint(Map& map, initializer_list<paintSettings> arr = {})const override;
        };

    }
}