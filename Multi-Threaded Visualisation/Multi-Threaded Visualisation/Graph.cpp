#include "Graph.h"
#include <iostream>


Graph::Graph()
{

}

Graph::~Graph()
{
	
}

bool Graph::addNode(int data, std::string id, int row, int column)
{
	if (NodeExists(id) == false)
	{
		Node * node = new Node();
		node->SetID(id);
		node->SetWeight(data);
		node->SetMarked(false);
		nodes.push_back(node);
		node->m_position.first = row * 100;
		node->m_position.second = column * 100;
		node->agentCounter = 0;
		return true;
	}
	else
	{
		return false;
	}
}

void Graph::removeNode(int index)
{
	Arc* arc;
	for (int i = 0; i < nodes.size(); i++)
	{
		arc = nodes.at(i)->GetArc(nodes.at(index));
		if (arc != nullptr)
		{
			removeArc(i, index);
		}
	}

}

bool Graph::addArc(int from, int to, int weight)
{
	bool proceed = true;

	if (NodeExists(from) == false || NodeExists(to) == false)
	{
		proceed = false;
	}

	 //if an arc already exists we should not proceed
	if (nodes.at(from)->GetArc(nodes.at(to)) != 0) 
	{
		proceed = false;
	}

	if (proceed == true) 
	{
		// add the arc to the "from" node.
		nodes.at(from)->AddArc(nodes.at(to), weight);
	}

	return proceed;
}

void Graph::removeArc(int from, int to)
{
	bool nodeExists = true;
	if (NodeExists(from) == false || NodeExists(to) == false)
	{
		nodeExists = false;
	}

	if (nodeExists == true) 
	{
		nodes.at(from)->removeArc(nodes.at(to));
	}
}

Arc * Graph::getArc(int from, int to)
{
	Arc* pArc = 0;
	// make sure the to and from nodes exist
	if (NodeExists(from) == true && NodeExists(to) == true)
	{
		pArc = nodes.at(from)->GetArc(nodes.at(to));
	}

	return pArc;
}

void Graph::clearMarks()
{
	for (int i = 0; i < nodes.size(); i++)
	{
		nodes.at(i)->m_marked = false;
	}
}

bool Graph::NodeExists(std::string id)
{
	bool nodePresent = false;
	for (int i = 0; i < nodes.size(); i++)
	{
		if (id == nodes.at(i)->id)
		{
			nodePresent = true;
			break;
		}
	}
	if (nodePresent == true)
	{
		return true;
	}
	else
	{
		return false;
	}

}

bool Graph::NodeExists(int index)
{
	bool nodePresent = false;
	if (index <= nodes.size())
	{
		nodePresent = true;
	}
	if (nodePresent == true)
	{
		return true;
	}
	else
	{
		return false;
	}

}

Node * Graph::getNode(int row, int column)
{
	int index = row * 16;
	index = index + column;
	return nodes.at(index);
}

int Graph::GetIndex(std::string id)
{
	for (int i = 0; i < nodes.size(); i++)
	{
		if (id == nodes.at(i)->id)
		{
			return i;
		}
	}
	return -1;
}

int Graph::GetManhattanDistance(int xPosOne, int yPosOne, int xPosTwo, int yPosTwo)
{
	int length;
	length = sqrt((xPosTwo - xPosOne)*(xPosTwo - xPosOne));
	length += sqrt((yPosTwo - yPosOne)*(yPosTwo - yPosOne));
	return length;
}

int Graph::calculateAgentG(std::vector<Agent*>&agents, Node * currentNode, Agent * currentAgent)
{
	int counter = 1;
	for (int a = 0; a < agents.size(); a++)
	{
		if (agents.at(a)->m_id != (*currentAgent).m_id)
		{
			for (int n = 0; n < agents.at(a)->path.size(); n++)
			{
				if (currentNode == agents.at(a)->path.at(n))
				{
					counter++;
				}
			}
		}
	}
	return counter;
}

void Graph::ucs(Node * pStart, Node * pDest, std::vector<Node*>& path)
{
	if (pStart != 0)
	{
		for (int index = 0; index < nodes.size(); index++) 
		{
			if (nodes.at(index) != nullptr) 
			{
				nodes.at(index)->weight = std::numeric_limits<int>::max() - 10000;
			}
		}
		bool foundPath = false;
		std::priority_queue<Node*, std::vector<Node*>, NodeSearchCostComparer> nodeQueue;
		nodeQueue.push(pStart);
		pStart->m_marked = true;
		pStart->weight = 0;
		while (nodeQueue.size() != 0 && nodeQueue.top() != pDest)
		{
			std::list<Arc>::const_iterator iter = nodeQueue.top()->m_arcList.begin();
			std::list<Arc>::const_iterator endIter = nodeQueue.top()->m_arcList.end();
			for (; iter != endIter; iter++)
			{
				if ((*iter).getDestNode() != nodeQueue.top())
				{
					int dist = nodeQueue.top()->weight + iter->getWeight();

					if ((*iter).getDestNode()->m_marked == false)
					{
						// mark the node and add it to the queue.
						(*iter).getDestNode()->m_previous = nodeQueue.top();
						if (dist < (*iter).getDestNode()->weight)
						{
							(*iter).getDestNode()->weight = dist;
						}
						(*iter).getDestNode()->m_marked = true;
						nodeQueue.push((*iter).getDestNode());
					}
					if (dist < (*iter).getDestNode()->weight)
					{
						(*iter).getDestNode()->weight = dist;
						(*iter).getDestNode()->m_previous = nodeQueue.top();
					}
					if ((*iter).getDestNode() == pDest)
					{
						if (dist <= (*iter).getDestNode()->weight)
						{
							(*iter).getDestNode()->weight = dist;
							(*iter).getDestNode()->m_previous = nodeQueue.top();
							if (foundPath == true)
							{
								path.clear();
							}
							Node* temp = (*iter).getDestNode();
							path.push_back((*iter).getDestNode());
							while (temp != pStart)
							{
								temp = temp->m_previous;
								path.push_back(temp);
							}
							foundPath = true;
						}
					}

				}
			}
			nodeQueue.pop();
		}
	}
}

void Graph::setHeuristic(Node * pStart, Node * pDest)
{

	for (int i = 0; i < nodes.size(); i++)
	{
		nodes.at(i)->weight = GetManhattanDistance(pDest->m_position.first, pDest->m_position.second, nodes.at(i)->m_position.first, nodes.at(i)->m_position.second);
		nodes.at(i)->m_estDistToDest = nodes.at(i)->weight*0.9f;
		nodes.at(i)->weight = std::numeric_limits<int>::max() - 10000;
		//std::cout << nodes.at(i)->id << " " << nodes.at(i)->m_estDistToDest << std::endl;

		nodes.at(i)->m_marked = false;
		nodes.at(i)->m_removed = false;
	}

}

void Graph::aStar(Node * pStart, Node * pDest, std::vector<Node*>& path)
{
	ResetGraph();
	//g(n) = nodeQueue.top()->weight
	//h(n) = estimated cost
	//f(n) = g(n)+h(n)

	if (pStart != 0)
	{
		setHeuristic(pStart,pDest);
		std::priority_queue<Node*, std::vector<Node*>, NodeSearchEstimateComparer> nodeQueue;

		//Add starting node to queue and set its distance and that it has been visited
		nodeQueue.push(pStart);
		pStart->m_marked = true;
		pStart->weight = 0;

		while (nodeQueue.size() != 0 && nodeQueue.top() != pDest)
		{
			std::list<Arc>::const_iterator iter = nodeQueue.top()->m_arcList.begin();
			std::list<Arc>::const_iterator endIter = nodeQueue.top()->m_arcList.end();

			for (; iter != endIter; iter++)
			{
				if ((*iter).getDestNode()->m_previous != nodeQueue.top())
				{
					int dist = nodeQueue.top()->weight + iter->getWeight();

					//Checks if distance is shorter than current shortest distance to this node
					if (dist < (*iter).getDestNode()->weight)
					{
						//sets new distance
						(*iter).getDestNode()->weight = dist;
						//sets pointer for previous node to the node at the top of the queue
						(*iter).getDestNode()->m_previous = nodeQueue.top();
					}

					//Checks to see if the node has been visited
					if ((*iter).getDestNode()->m_marked == false)
					{
						//sets pointer for previous node to the node at the top of the queue
						(*iter).getDestNode()->m_previous = nodeQueue.top();
						// mark the node and add it to the queue.
						(*iter).getDestNode()->m_marked = true;
						nodeQueue.push((*iter).getDestNode());
					}

					if ((*iter).getDestNode() == pDest)
					{
						if (dist <= (*iter).getDestNode()->weight)
						{
							//sets new distance
							(*iter).getDestNode()->weight = dist;
							//sets pointer for previous node to the node at the top of the queue
							(*iter).getDestNode()->m_previous = nodeQueue.top();
							//Clears contents of vector
							path.clear();
							Node* temp = (*iter).getDestNode();
							path.push_back((*iter).getDestNode());
							//Gets pointer to the previous node and adds it to the path vector
							while (temp != pStart)
							{
								temp = temp->m_previous;
								path.push_back(temp);
							}
						}
					}
				}
			}
			nodeQueue.pop();
		}
	}
}

void Graph::aStarAmbush(Node * pStart, Node * pDest, Agent* agent, std::vector<Agent*>& agents)
{
	ResetGraph();
	//g(n) = nodeQueue.top()->weight
	//h(n) = estimated cost
	//f(n) = g(n)+h(n)

	if (pStart != 0)
	{
		setHeuristic(pStart, pDest);
		std::priority_queue<Node*, std::vector<Node*>, NodeSearchEstimateComparer> nodeQueue;

		//Add starting node to queue and set its distance and that it has been visited
		nodeQueue.push(pStart);
		pStart->m_marked = true;
		pStart->weight = 0;

		while (nodeQueue.size() != 0 && nodeQueue.top() != pDest)
		{
			std::list<Arc>::const_iterator iter = nodeQueue.top()->m_arcList.begin();
			std::list<Arc>::const_iterator endIter = nodeQueue.top()->m_arcList.end();

			for (; iter != endIter; iter++)
			{
				if ((*iter).getDestNode()->m_previous != nodeQueue.top())
				{
					int dist = nodeQueue.top()->weight + iter->getWeight()*(calculateAgentG(agents,(*iter).getDestNode(),agent)*(calculateAgentG(agents, (*iter).getDestNode(), agent)));

					//Checks if distance is shorter than current shortest distance to this node
					if (dist < (*iter).getDestNode()->weight)
					{
						//sets new distance
						(*iter).getDestNode()->weight = dist;
						//sets pointer for previous node to the node at the top of the queue
						(*iter).getDestNode()->m_previous = nodeQueue.top();
					}

					//Checks to see if the node has been visited
					if ((*iter).getDestNode()->m_marked == false)
					{
						//sets pointer for previous node to the node at the top of the queue
						(*iter).getDestNode()->m_previous = nodeQueue.top();
						// mark the node and add it to the queue.
						(*iter).getDestNode()->m_marked = true;
						nodeQueue.push((*iter).getDestNode());
					}

					if ((*iter).getDestNode() == pDest)
					{
						if (dist <= (*iter).getDestNode()->weight)
						{
							//sets new distance
							(*iter).getDestNode()->weight = dist;
							//sets pointer for previous node to the node at the top of the queue
							(*iter).getDestNode()->m_previous = nodeQueue.top();
							//Clears contents of vector
							agent->path.clear();
							Node* temp = (*iter).getDestNode();
							agent->path.push_back((*iter).getDestNode());
							//Gets pointer to the previous node and adds it to the path vector
							while (temp != pStart)
							{
								temp = temp->m_previous;
								agent->path.push_back(temp);
							}
						}
					}
				}
			}
			nodeQueue.pop();
		}
	}
}




void Graph::ResetGraph()
{
	for (int i = 0; i < nodes.size(); i++)
	{
		nodes.at(i)->ResetNode();
	}
}

bool Graph::NodeInVector(Node* node, std::vector<Node*> nodeVector)
{
	for (int n = 0; n < nodeVector.size(); n++)
	{
		if (node == nodeVector.at(n))
		{
			return true;
		}
	}
	return false;
}