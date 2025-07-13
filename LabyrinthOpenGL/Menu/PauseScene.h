#pragma once
#include "../Scene.h"
#include "../Button.h"

class PauseScene :
	public Scene
{
private:
    bool wasLeftPressed = false;
	Scene* pastScene;

public:
    PauseScene(Scene* pastScene, _List::List<Buttons::Button*> buttons = {});

    void handleInput() override { }

    void update(int mouseX, int mouseY) override;

    void draw() override;
};