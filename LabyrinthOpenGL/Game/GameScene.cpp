#include "GameScene.h"

GameScene::GameScene(Map& map, Entities::Fighters::Player& player, _List::List<Buttons::Button*> buttons)
{
    this->map = map;
    this->player = player;
    coin.randXY(map);
    nextScene = this;
    this->buttons = buttons;
}

void GameScene::update(int mouseX, int mouseY)
{
    auto now = high_resolution_clock::now();
    auto ms = duration_cast<milliseconds>(now - player.getLastInputTick()).count();
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

    if (ms >= player.getDelay())
    {
        if (GetKeyState('W') < 0) player.movePlayer(map, coin, -1);
        if (GetKeyState('A') < 0) player.movePlayer(map, coin, -2);
        if (GetKeyState('S') < 0) player.movePlayer(map, coin, 1);
        if (GetKeyState('D') < 0) player.movePlayer(map, coin, 2);
        player.setLastInputTick(now);
    }
}

void GameScene::draw()
{
    HDC& hDC = WindowContext::getInstance().getHDC();
    GLuint& base = WindowContext::getInstance().getFontBase();
    glPushMatrix();
    glTranslatef(50, 150, 0);
    map.paintMap(player, coin);
    glTranslatef(blockWidth, map.getMap().size() * blockDepth + blockDepth / 2, 0);
    coin.paint(map);
    glColor3f(0, 0, 0);
    glPrintText(2 * blockWidth, blockDepth / 2, to_string(player.getCoins()).insert(0, "Coins: ").c_str(), hDC, base);
    glPopMatrix();
    for (auto item : buttons)
        item->paint();
}
