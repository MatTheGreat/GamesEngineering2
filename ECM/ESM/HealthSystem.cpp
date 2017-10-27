#include "HealthSystem.h"
#include <iostream>

HealthSystem::HealthSystem()
{

}

HealthSystem::~HealthSystem()
{

}

void HealthSystem::addEntity(Entity e)
{
	entities.push_back(e);
}

void HealthSystem::Update()
{
	std::cout << "Health System Updating" << std::endl;
}