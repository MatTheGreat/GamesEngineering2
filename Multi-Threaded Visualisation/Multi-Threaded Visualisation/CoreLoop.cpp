#include "CoreLoop.h"


CoreLoop::CoreLoop()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		exit(0);
	}
	isRunning = true;

	window = SDL_CreateWindow("Multi-Threaded Visualisation", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1920, 1080, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	renderManager = new RenderManager(renderer);
	SDL_Surface * image = IMG_Load("Test.png");
	SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, image);
	graph = Graph();
	threadManager = new ThreadManager();

	for (int i = 0; i < 100; i++)
	{
		for (int r = 0; r < 100; r++)
		{
			renderObjs.push_back(new RenderObject(texture, 0, 0, 10, 10, i * 10 + (50), r * 10 + (10), 10, 10));
		}
	}
	GenerateMap();

	RunAStar();

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
	SDL_RenderClear(renderer);

	//Should Add timer to check time taken
	//for (int i = 0; i < renderObjs.size(); i++)
	//{
	//	renderManager->DrawObject(renderObjs.at(i));
	//}
	threadManager->Render(renderManager, renderObjs);
	SDL_RenderPresent(renderer);
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


//Test Thread
static int TestThread(void *ptr)
{
	Graph * pGraph = nullptr;
	std::vector<Agent*>* pAgents = nullptr;
	int * pStart = nullptr;
	int * pEnd = nullptr;
	std::vector<std::pair<void *, int>> * data = static_cast<std::vector<std::pair<void *, int>>*>(ptr);
	for (int i = 0; i < data->size(); i++)
	{
		if (data->at(i).second == 0)
		{
			pGraph = static_cast<Graph*>(data->at(i).first);
		}
		if (data->at(i).second == 1)
		{
			pAgents = static_cast<std::vector<Agent*>*>(data->at(i).first);
		}
		if (data->at(i).second == 2)
		{
			pStart = static_cast<int*>(data->at(i).first);
		}
		if (data->at(i).second == 3)
		{
			pEnd = static_cast<int*>(data->at(i).first);
		}
	}

	pGraph->aStarAmbush(pGraph->nodes.at(*pStart), pGraph->nodes.at(*pEnd), pAgents->at(2), *pAgents);
	std::cout << "Agent 3" << std::endl;
	for (int i = pAgents->at(2)->path.size() - 1; i > -1; i--)
	{
		std::cout << "Location : " << pAgents->at(2)->path.at(i)->id << " Cost : " << pAgents->at(2)->path.at(i)->weight << " h(n) : " << pAgents->at(2)->path.at(i)->m_estDistToDest << std::endl;
		if (pAgents->at(2)->path.at(i) == pGraph->nodes.at(*pStart))
		{
			std::cout << std::endl;
		}
	}

	pGraph->aStarAmbush(pGraph->nodes.at(*pStart), pGraph->nodes.at(*pEnd), pAgents->at(3), *pAgents);
	std::cout << "Agent 4" << std::endl;
	for (int i = pAgents->at(3)->path.size() - 1; i > -1; i--)
	{
		std::cout << "Location : " << pAgents->at(3)->path.at(i)->id << " Cost : " << pAgents->at(3)->path.at(i)->weight << " h(n) : " << pAgents->at(3)->path.at(i)->m_estDistToDest << std::endl;
		if (pAgents->at(3)->path.at(i) == pGraph->nodes.at(*pStart))
		{
			std::cout << std::endl;
		}
	}
	return 0;
}

void CoreLoop::RunAStar()
{

	agents.push_back(new Agent(0));
	agents.push_back(new Agent(1));
	agents.push_back(new Agent(2));
	agents.push_back(new Agent(3));

	data  = new std::vector<std::pair<void *, int>>();
	
	data->push_back(std::make_pair(&graph, 0));
	data->push_back(std::make_pair(&agents, 1));
	data->push_back(std::make_pair(&start, 2));
	data->push_back(std::make_pair(&end, 3));
	void *voidPtr = data;

	thread = SDL_CreateThread(TestThread, "TestThread", voidPtr);

	//graph.aStarAmbush(graph.nodes.at(start), graph.nodes.at(end), agents.at(0), agents);
	//std::cout << "Agent 1" << std::endl;
	//OutputPath(agents.at(0)->path,start);

	//graph.aStarAmbush(graph.nodes.at(start), graph.nodes.at(end), agents.at(1), agents);
	//std::cout << "Agent 2" << std::endl;
	//OutputPath(agents.at(1)->path,start);

}
