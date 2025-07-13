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
            time_point<high_resolution_clock> lastInputTick;
            int delay;
        public:
            Player() {}
            Player(Map& map) { randXY(map); }
            Player(int x, int y, float step, Map& map, int delay);
            float getStep()const { return step; }
            void setStep(float step) { this->step = step; }
            int getCoins()const { return coins; }
            time_point<high_resolution_clock> getLastInputTick()const { return lastInputTick; }
            void setLastInputTick(time_point<high_resolution_clock> lit) { lastInputTick = lit; }
            int getDelay()const { return delay; }

            void randXY(Map& map);
            bool isWallNext(Map& map, int vec) const;
            void movePlayer(Map& map, Entities::Items::Coin& coin, int vec);
            void paint(Map& map, initializer_list<paintSettings> arr = {})const override;
            void loadFromFile(ifstream& file) override;
            void saveToFile(ofstream& file) override;
        };

    }
}
