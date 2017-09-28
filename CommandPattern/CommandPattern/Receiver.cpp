#include "Receiver.h"

void Receiver::Action(std::string command)
{
	if (command == "Jump")
	{
		Jump();
	}
	if (command == "Fire")
	{
		Fire();
	}
}

void Receiver::Jump()
{
	std::cout << "Jump" << std::endl;
}

void Receiver::Fire()
{
	std::cout << "Fire" << std::endl;
}