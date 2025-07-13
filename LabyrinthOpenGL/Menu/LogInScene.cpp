#include "LogInScene.h"

LogInScene::LogInScene(string fileName, _List::List<Buttons::Button*> buttons)
{
    profilesName = fileName;
    this->buttons = buttons;
    nextScene = this;
}

void LogInScene::handleInput()
{
    if (activeInputField) {
        string target = activeInputField->getTarget();
        if (target == "nickname")
            activeInputField->handleInput(&nickname);
        else if (target == "password")
            activeInputField->handleInput(&password);
    }
}

void LogInScene::update(int mouseX, int mouseY)
{
    SHORT currentState = GetAsyncKeyState(VK_LBUTTON) & 0x8000;

    if (currentState && !wasLeftPressed) {
        wasLeftPressed = true;
    }
    else if (!currentState && wasLeftPressed) {
        wasLeftPressed = false;
        activeInputField = nullptr;

        for (auto item : buttons) {
            if (item->isHovered(mouseX, mouseY)) {
                if (auto* input = dynamic_cast<Buttons::InputField*>(item)) {
                    input->activate();
                    activeInputField = input;
                }
                else if (item->getNextScene() == this)
                    checkLogin(nickname, password);
                else
                    nextScene = item->getNextScene();
            }
        }
    }
}

void LogInScene::draw()
{
    HDC& hDC = WindowContext::getInstance().getHDC();
    GLuint& base = WindowContext::getInstance().getFontBase();

    for (auto item : buttons)
        item->paint();

    if (!message.empty()) {
        glColor3f(0, 0, 0);
        glPrintText(400, 500, message.c_str(), hDC, base);
    }
}

bool LogInScene::checkLogin(const string& name, const string& pass)
{
    ifstream file(profilesName);
    Profile p;
    while (file.peek() != EOF) {
        p.loadFromFile(file);
        if (nickname.empty() || password.empty()) {
            message = "Fill in all fields!";
        }
        else if ((!nickname.empty() || !password.empty()) && (nickname != p.nickname || password != p.password)) {
            message = "Incorrect login or password!";
        }
        else
        {
            message = "Login successful!";
            return true;
        }
    }
    return false;
}
