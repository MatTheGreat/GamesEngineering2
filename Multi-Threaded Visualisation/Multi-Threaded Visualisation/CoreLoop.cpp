#include "CoreLoop.h"



CoreLoop::CoreLoop()
{
	isRunning = true;

	window = SDL_CreateWindow("Multi-Threaded Visualisation", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1600, 900, SDL_WINDOW_SHOWN);

	graph = Graph();

	GenerateMap();

	RunAStar(graph);

}

CoreLoop::~CoreLoop()
{

}

bool CoreLoop::Loop()
{
	Update();
	Draw();
	return isRunning;
}

void CoreLoop::Update()
{
	SDL_Event events;

	while (SDL_PollEvent(&events))
	{
		if (events.type == SDL_KEYDOWN)
		{
			if (events.key.keysym.sym == SDLK_ESCAPE)
			{
				isRunning == false;
			}
		}
	}
}

void CoreLoop::Draw()
{

}

void CoreLoop::GenerateMap()
{
	std::string temp;
	std::ifstream myfile;
	for (int r = 0; r < 16; r++)
	{
		for (int c = 0; c < 16; c++)
		{
			temp = "R :" + std::to_string(r) + " C: " + std::to_string(c);
			graph.addNode(std::numeric_limits<int>::max() - 10000, temp,r,c);
		}
	}
	int from, to, weight;

	for (int r = 0; r < 16; r++)
	{
		for (int c = 0; c < 16; c++)
		{
			std::string IDstring;
			IDstring = "R :" + std::to_string(r) + " C: " + std::to_string(c);
			if (r != 0)
			{
				std::string destString;
				destString = "R :" + std::to_string((r - 1)) + " C: " + std::to_string(c);
				if (graph.getArc(graph.GetIndex(IDstring), graph.GetIndex(destString)) == 0)
				{
					graph.addArc(graph.GetIndex(IDstring), graph.GetIndex(destString), 100);
				}
			}
			if (c != 0)
			{
				std::string destString;
				destString = "R :" + std::to_string(r) + " C: " + std::to_string((c - 1));
				if (graph.getArc(graph.GetIndex(IDstring), graph.GetIndex(destString)) == 0)
				{
					graph.addArc(graph.GetIndex(IDstring), graph.GetIndex(destString), 100);
				}
			}
			if (r < 15)
			{
				std::string destString;
				destString = "R :" + std::to_string((r + 1)) + " C: " + std::to_string(c);
				if (graph.getArc(graph.GetIndex(IDstring), graph.GetIndex(destString)) == 0)
				{
					graph.addArc(graph.GetIndex(IDstring), graph.GetIndex(destString), 100);
				}
			}
			if (c < 15)
			{
				std::string destString;
				destString = "R :" + std::to_string(r) + " C: " + std::to_string((c + 1));
				if (graph.getArc(graph.GetIndex(IDstring), graph.GetIndex(destString)) == 0)
				{
					graph.addArc(graph.GetIndex(IDstring), graph.GetIndex(destString), 100);
				}
			}
		}
	}
}

void CoreLoop::OutputPath(std::vector<Node*> path, int startIndex)
{
	for (int i = path.size() - 1; i > -1; i--)
	{
		std::cout << "Location : " << path.at(i)->id << " Cost : " << path.at(i)->weight << " h(n) : " << path.at(i)->m_estDistToDest << std::endl;
		if (path.at(i) == graph.nodes.at(startIndex))
		{
			std::cout << std::endl;
		}
	}
}

void CoreLoop::RunAStar(Graph graph)
{
	int start = 17;
	int end = 151;
	std::vector<Agent*> agents;
	agents.push_back(new Agent(0));
	agents.push_back(new Agent(1));
	agents.push_back(new Agent(2));
	agents.push_back(new Agent(3));

	graph.aStarAmbush(graph.nodes.at(start), graph.nodes.at(end), agents.at(0), agents);
	std::cout << "Agent 1" << std::endl;
	OutputPath(agents.at(0)->path,start);

	graph.aStarAmbush(graph.nodes.at(start), graph.nodes.at(end), agents.at(1), agents);
	std::cout << "Agent 2" << std::endl;
	OutputPath(agents.at(1)->path,start);

	graph.aStarAmbush(graph.nodes.at(start), graph.nodes.at(end), agents.at(2), agents);
	std::cout << "Agent 3" << std::endl;
	OutputPath(agents.at(2)->path, start);

	graph.aStarAmbush(graph.nodes.at(start), graph.nodes.at(end), agents.at(3), agents);
	std::cout << "Agent 4" << std::endl;
	OutputPath(agents.at(3)->path, start);

}
