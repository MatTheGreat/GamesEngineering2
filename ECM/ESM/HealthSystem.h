#pragma once
#include "Entity.h"
#include <vector>

class HealthSystem
{
	std::vector<Entity> entities;
public:

	HealthSystem();
	~HealthSystem();
	void addEntity(Entity e);
	void Update();

private:

};

