#pragma once
#include "../Scene.h"
#include "../Button.h"


class MainScene :
    public Scene
{
public:
    MainScene(_List::List<Buttons::Button*> buttons = {});

    void handleInput() override { }

    void update(int mouseX, int mouseY) override;

    void draw() override;
};