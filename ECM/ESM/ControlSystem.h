#pragma once
#include "Entity.h"

#include "ControlComponent.h"
#include "PositionComponent.h"

#include <vector>
#include <memory>

class ControlSystem
{
	std::vector<Entity*> entities;
public:

	ControlSystem();
	~ControlSystem();
	void addEntity(Entity* e);
	void Update();

private:

};