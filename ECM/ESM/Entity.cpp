#include "Entity.h"
#include <iterator>
#include <algorithm>

Entity::Entity()
{
}

Entity::~Entity()
{

}

void Entity::removeComponent(Component* c)
{
	for (std::vector<Component*>::iterator i = components.begin(); i != components.end(); i++)
	{
		if (c == (*i))
		{
			bool indexBackwards = false;
			if (i != (components.begin()+1) && components.size() > 1)
			{
				indexBackwards = true;
			}
			i = components.erase(std::remove(components.begin(), components.end(), (*i)), components.end());

			if (indexBackwards == true)
			{
				i--;
			}
			else
			{
				i++;
			}

			if (components.size() == 0)
			{
				break;
			}
		}
	}
	
	
}