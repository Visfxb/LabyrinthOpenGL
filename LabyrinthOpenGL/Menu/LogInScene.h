#pragma once
#include "../Scene.h"
#include "../InputField.h"
#include "../Game/Profile.h"

class LogInScene : public Scene {
private:
    Buttons::InputField* activeInputField = nullptr;
    Profile profile;
    string nickname;
    string password;
    string profilesName;
    string message;

public:
    LogInScene(string fileName, _List::List<Buttons::Button*> buttons = {});

    void handleInput() override;
    void update(int mouseX, int mouseY) override;
    void draw() override;
    bool checkLogin(const string& name, const string& pass);
};
