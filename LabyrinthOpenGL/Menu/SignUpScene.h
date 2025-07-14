#pragma once
#include "../Scene.h"
#include "../InputField.h"
#include "../Game/Profile.h"

class SignUpScene : public Scene {
private:
    Buttons::InputField* activeInputField = nullptr;
    Profile bufProfile;
    string confirmPassword;
    string profilesName;
    string message;


public:
    SignUpScene(string fileName, _List::List<Buttons::Button*> buttons = {});

    void handleInput() override;
    void update(int mouseX, int mouseY) override;
    void draw() override;
    void checkAndSaveProfile();
    void resetInputFields();
};
