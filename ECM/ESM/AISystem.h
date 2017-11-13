#pragma once
#include "Entity.h"
#include "HealthComponent.h"
#include "PositionComponent.h"
#include <vector>
#include <memory>

class AISystem
{
	std::vector<Entity*> entities;
public:

	AISystem();
	~AISystem();
	void addEntity(Entity* e);
	void Update();

private:

};

