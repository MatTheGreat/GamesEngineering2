#pragma once
#include "Component.h"

class ControlComponent : public Component
{
public:
	ControlComponent() : keyPressed(false) {};
	bool getKeyPressed() { return keyPressed; };
	void setKeyPressed(bool pressed) { this->keyPressed = pressed; };
	~ControlComponent() {};

private:
	bool keyPressed;
};