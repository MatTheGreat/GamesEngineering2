#pragma once
#include "Component.h"

struct Position
{
	float x;
	float y;
	Position(float X, float Y) : x(X), y(Y) {};
};

class PositionComponent : public Component
{
public:
	PositionComponent() : pos(0,0)  {};
	Position getPosition() { return pos;};
	void setPosition(Position position) { this->pos = position; };
	~PositionComponent() {};

private:
	Position pos;
};
