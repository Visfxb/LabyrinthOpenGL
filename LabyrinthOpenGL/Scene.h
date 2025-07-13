#pragma once
#include "Button.h"

class Scene
{
protected:
	_List::List<Buttons::Button*> buttons;
	//vector<Buttons::Button*> buttons;
	bool wasLeftPressed = false;
	Scene* nextScene;

public:
	virtual void handleInput() = 0;
	virtual void update(int mouseX, int mouseY) = 0;
	virtual void draw() = 0;
	void resetNextScene() {
		nextScene = this;
	}

	void addNewButton(Buttons::Button* button) { buttons.push_back(button); }
	Scene* getNextScene() const { return nextScene; }
	~Scene() {}
};

