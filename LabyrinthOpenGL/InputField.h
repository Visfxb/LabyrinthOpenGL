#pragma once
#include "Button.h"

namespace Buttons {
    class InputField
        : public Button {
    private:
        bool active = false;
        string inputText;
        int cursorPos = 0;
        string target;
        time_point<high_resolution_clock> lastInputTick;
        int delay = 150;

    public:
        InputField(int x, int y, int width, int height, const std::string& placeholder, string target = "")
            : Button(x, y, width, height, placeholder, nullptr), target(target) {
        }

        string getTarget() const { return target; }

        void handleInput(string* output);

        void activate() { active = true; }
        void deactivate() { active = false; }

        string getInput() const { return inputText; }

        void paint() const override;
    };
}