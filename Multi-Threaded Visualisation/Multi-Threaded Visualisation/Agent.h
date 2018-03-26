#pragma once
#include "Node.h"
#include <vector>

class Agent
{
public:
	Agent();
	Agent(int id);
	~Agent();
	std::vector<Node *> path;
	int m_id;
private:
	
	
};

