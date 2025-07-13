#include "Button.h"

void glPrintText(float x, float y, const char* text, HDC hDC, GLuint base)
{
    glRasterPos2f(x, y);
    glColor3f(0, 0, 0);
    glListBase(base);
    glCallLists(strlen(text), GL_UNSIGNED_BYTE, text);
}
POINT getMouseXY(HWND hwnd) {
    POINT mouse;
    GetCursorPos(&mouse);
    ScreenToClient(hwnd, &mouse);

    RECT rect;
    GetClientRect(hwnd, &rect);
    int clientHeight = rect.bottom - rect.top;

    mouse.y = clientHeight - mouse.y;
    return mouse;
}

Scene* Buttons::Button::getNextScene() const
{
    return nextScene;
}

void Buttons::Button::paint() const
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
	glPrintText((width - text.size() * lf.lfHeight / 24.f * 11) / 2, (height - lf.lfHeight), text.c_str(), hDC, base);
	glPopMatrix();
}

bool Buttons::Button::isHovered(int mouseX, int mouseY) const
{
	return mouseX >= x && mouseX <= x + width &&
		mouseY >= y && mouseY <= y + height;
}
