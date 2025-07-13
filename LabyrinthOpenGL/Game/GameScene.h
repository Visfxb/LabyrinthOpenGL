#pragma once
#include "../Scene.h"
#include "Map.h"
#include "Player.h"
#include "Coin.h"
#include "Profile.h"


class GameScene :
    public Scene
{
private:
    Profile profile;
    Map map;
    Entities::Fighters::Player player;
    Entities::Items::Coin coin;

public:
    GameScene(Map& map, Entities::Fighters::Player& player, _List::List<Buttons::Button*> buttons = {});

    void handleInput() override { }

    void update(int mouseX, int mouseY) override;

    void draw() override;
};

