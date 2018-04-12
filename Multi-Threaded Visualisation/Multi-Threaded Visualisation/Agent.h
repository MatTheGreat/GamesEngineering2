#pragma once
#include "Node.h"
#include <vector>

class Agent
{
public:
	Agent();
	Agent(int id,int nodeID);
	~Agent();
	std::vector<Node *> path;
	int m_id;
	int m_nodeID;
private:
	
	
};

