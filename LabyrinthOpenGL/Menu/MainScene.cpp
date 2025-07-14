#include "MainScene.h"

MainScene::MainScene(_List::List<Buttons::Button*> buttons)
{
	this->buttons = buttons; nextScene = this;
}

void MainScene::update(int mouseX, int mouseY)
{
    SHORT currentState = GetAsyncKeyState(VK_LBUTTON) & 0x8000;

    if (currentState && !wasLeftPressed) {
        wasLeftPressed = true;
    }
    else if (!currentState && wasLeftPressed) {
        wasLeftPressed = false;
        for (auto item : buttons) {
            if (item->isHovered(mouseX, mouseY))
            {
                nextScene = item->getNextScene();
            }
        }
    }
}

void MainScene::draw()
{
    for (auto item : buttons)
        item->paint();
}