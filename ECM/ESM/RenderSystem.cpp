#include "RenderSystem.h"
#include <iostream>

RenderSystem::RenderSystem()
{

}

RenderSystem::~RenderSystem()
{

}

void RenderSystem::addEntity(Entity* e)
{
	entities.push_back(e);
}

void RenderSystem::Update()
{
	for (int e = 0; e < entities.size(); e++)
	{
		PositionComponent* positionComp;
		for (int c = 0; c < entities.at(e)->getComponents().size(); c++)
		{
			Component* com = entities.at(e)->getComponents().at(c);
			if (PositionComponent* pc = dynamic_cast<PositionComponent*>(com))
			{
				positionComp = pc;
			}
		}

		//Do Entity Specific Code

		std::cout << "Render "<< e << " Position:" << positionComp->getPosition().x << "," << positionComp->getPosition().y << std::endl;
	}
	//std::cout << "Position System Updating" << std::endl;
}