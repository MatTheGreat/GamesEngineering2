#include "ControlSystem.h"
#include <string>
#include <iostream>

ControlSystem::ControlSystem()
{

}

ControlSystem::~ControlSystem()
{

}

void ControlSystem::addEntity(Entity* e)
{
	entities.push_back(e);
}

void ControlSystem::Update()
{
	for (int e = 0; e < entities.size(); e++)
	{
		ControlComponent* control;
		PositionComponent* position;
		for (int c = 0; c < entities.at(e)->getComponents().size(); c++)
		{
			Component* com = entities.at(e)->getComponents().at(c);
			if (ControlComponent* cc = dynamic_cast<ControlComponent*>(com))
			{
				control = cc;
			}
			else if (PositionComponent* pc = dynamic_cast<PositionComponent*>(com))
			{
				position = pc;
			}
		}

		//Do Entity Specific Code

		std::cout << "Control  " << e << " KeyPressed:" << control->getKeyPressed() << " Position:" << position->getPosition().x << "," << position->getPosition().y << std::endl;
	}
}