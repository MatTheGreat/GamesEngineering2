#include "AISystem.h"

#include <iostream>

AISystem::AISystem()
{

}

AISystem::~AISystem()
{

}

void AISystem::addEntity(Entity* e)
{
	entities.push_back(e);
}

void AISystem::Update()
{
	for (int e = 0; e < entities.size(); e++)
	{
		HealthComponent* health;
		PositionComponent* position;
		for (int c = 0; c < entities.at(e)->getComponents().size(); c++)
		{
			Component* com = entities.at(e)->getComponents().at(c);
			if (HealthComponent* hc = dynamic_cast<HealthComponent*>(com))
			{
				health = hc;
			}
			else if (PositionComponent* pc = dynamic_cast<PositionComponent*>(com))
			{
				position = pc;
			}
		}

		//Do Entity Specific Code

		std::cout <<"AI  " << e << " Health:" << health->getHealth() << " Position:" << position->getPosition().x << "," << position->getPosition().y << std::endl;
	}
}
