#pragma once
#include "Include.h"

void glPrintText(float x, float y, const char* text, HDC hDC, GLuint base);
POINT getMouseXY(HWND hwnd);

class Scene;

namespace Buttons {
	class Button
	{
	protected:
		int x;
		int y;
		int width;
		int height;
		string text;
		Scene* nextScene;
	public:
		Button(int x, int y, int width, int height, string text, Scene* nextScene)
			: x(x), y(y), width(width), height(height), text(text), nextScene(nextScene) {}
		virtual ~Button() {}
		Scene* getNextScene()const;

		virtual void paint() const;

		bool isHovered(int mouseX, int mouseY) const;
	};
}