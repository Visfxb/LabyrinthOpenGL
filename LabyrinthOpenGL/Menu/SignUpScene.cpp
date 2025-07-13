#include "SignUpScene.h"

SignUpScene::SignUpScene(string fileName, _List::List<Buttons::Button*> buttons)
{
    profilesName = fileName;
    this->buttons = buttons;
    nextScene = this;
}

void SignUpScene::handleInput()
{
    if (activeInputField) {
        string target = activeInputField->getTarget();
        if (target == "nickname")
            activeInputField->handleInput(&bufProfile.nickname);
        else if (target == "password")
            activeInputField->handleInput(&bufProfile.password);
        else if (target == "confirm password")
            activeInputField->handleInput(&confirmPassword);
    }
}

void SignUpScene::update(int mouseX, int mouseY)
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
                    checkAndSaveProfile();
                else
                    nextScene = item->getNextScene();
            }
        }
    }
}

void SignUpScene::draw()
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

void SignUpScene::checkAndSaveProfile()
{
    if (bufProfile.nickname.empty() || bufProfile.password.empty()) {
        message = "Fill in all fields!";
        return;
    }
    if (bufProfile.password != confirmPassword) {
        message = "Passwords do not match!";
        return;
    }

    ofstream profiles(profilesName, ios::app);
    if (profiles.is_open()) {
        bufProfile.saveToFile(profiles);
        message = "Profile saved!";
    }
    else {
        message = "Failed to save!";
    }
    resetInputFields();
}

void SignUpScene::resetInputFields()
{
    bufProfile = Profile();
    confirmPassword = "";
    for (auto* item : buttons) {
        if (auto* input = dynamic_cast<Buttons::InputField*>(item)) {
            input->deactivate();
        }
    }
}
