#pragma once
#include <string>
#include <iostream>

class Receiver
{
public:
	void Action(std::string command);

private:
	void Jump();
	void Fire();
};

