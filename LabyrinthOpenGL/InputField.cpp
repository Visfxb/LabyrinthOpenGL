#include "InputField.h"

void Buttons::InputField::handleInput(string* output)
{
    UINT message = WindowContext::getInstance().getLastMessage();
    WPARAM wParam = WindowContext::getInstance().getLastWParam();
    auto now = high_resolution_clock::now();
    auto ms = duration_cast<milliseconds>(now - lastInputTick).count();

    if (!active) return;

    if (message == WM_CHAR && ms >= delay) { // Enter
        if (wParam == 13)
        {
            active = false;
            *output = inputText;
        }
        else if (wParam == 8 && cursorPos > 0) { // Backspace
            inputText.erase(cursorPos - 1, 1);
            cursorPos--;
        }
        else if (wParam >= 32 && wParam <= 126) {
            inputText.insert(inputText.begin() + cursorPos, char(wParam));
            cursorPos++;
        }
        lastInputTick = now;
    }
    else if (message == WM_KEYDOWN && ms >= delay) {
        switch (wParam) {
        case VK_LEFT:
            if (cursorPos > 0) cursorPos--;
            break;
        case VK_RIGHT:
            if (cursorPos < inputText.size()) cursorPos++;
            break;
        case VK_DELETE:
            if (cursorPos < inputText.size()) {
                inputText.erase(cursorPos, 1);
            }
            break;
        }
        lastInputTick = now;
    }
}

void Buttons::InputField::paint() const
{
    HDC& hDC = WindowContext::getInstance().getHDC();
    HFONT& hFont = WindowContext::getInstance().getFont();
    GLuint& base = WindowContext::getInstance().getFontBase();
    LOGFONT lf;
    GetObject(hFont, sizeof(LOGFONT), &lf);

    glPushMatrix();
    glTranslatef(float(x), float(y), 0);

    glBegin(GL_TRIANGLE_STRIP);
    glColor3f(1, 1, 0);
    glVertex2f(0, 0);
    glVertex2f(width, 0);
    glVertex2f(0, height);
    glVertex2f(width, height);
    glEnd();

    glColor3f(0, 0, 0);
    if (active) {
        glPrintText(5, (height - lf.lfHeight), inputText.c_str(), hDC, base);
        glPrintText(cursorPos * lf.lfHeight / 24.f * 11, (height - lf.lfHeight), "|", hDC, base);
    }
    else
        glPrintText(5, (height - lf.lfHeight), inputText == "" ? text.c_str() : inputText.c_str(), hDC, base);

    glPopMatrix();
}
