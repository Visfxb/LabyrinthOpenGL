#include "PauseScene.h"

PauseScene::PauseScene(Scene* pastScene, _List::List<Buttons::Button*> buttons)
{
	this->buttons = buttons; this->pastScene = pastScene;
}

void PauseScene::update(int mouseX, int mouseY)
{
    SHORT currentState = GetAsyncKeyState(VK_LBUTTON) & 0x8000;

    if (currentState && !wasLeftPressed) {
        //  нопка нажата
        wasLeftPressed = true;
    }

    else if (!currentState && wasLeftPressed) {
        //  нопка отпущена
        wasLeftPressed = false;
        for (auto item : buttons) {
            if (item->isHovered(mouseX, mouseY))
            {
                nextScene = item->getNextScene();
            }
        }
    }
}

void PauseScene::draw()
{
    WindowContext::getInstance().updateSize();

    WindowContext& ctx = WindowContext::getInstance();
    int width = ctx.getWidth();
    int height = ctx.getHeight();

    pastScene->draw();
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBegin(GL_TRIANGLE_STRIP);
    glColor4f(0, 0, 0, 0.5f);
    glVertex2f(0, 0); glVertex2f(0, height);
    glVertex2f(width, 0); glVertex2f(width, height);
    glEnd();
    for (auto item : buttons)
        item->paint();
}