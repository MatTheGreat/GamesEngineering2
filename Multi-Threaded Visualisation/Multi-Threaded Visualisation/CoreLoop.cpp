#include "CoreLoop.h"


CoreLoop::CoreLoop()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		exit(0);
	}
	isRunning = true;

	m_player = Player(151);


	imageOne = IMG_Load("Test.png");
	textureOne = SDL_CreateTextureFromSurface(renderer, imageOne);

	window = SDL_CreateWindow("Multi-Threaded Visualisation", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1920, 1080, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	renderManager = new RenderManager(renderer);
	graph = Graph();
	threadManager = new ThreadManager();
	timer = 5;
	GenerateMap();

	imageThree = IMG_Load("Test3.png");
	textureThree = SDL_CreateTextureFromSurface(renderer, imageThree);
	renderObjs.at(m_player.m_nodeID)->setTexture(textureThree);
	

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
	if (timer > 5)
	{
		timer = 0;
		RunAmbushStar();
	}
	else
	{
		timer++;
	}
	Collision();
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
	//Rendering is MultiThreaded
	threadManager->Render(renderManager, renderObjs);
	SDL_RenderPresent(renderer);
}

void CoreLoop::GenerateMap()
{
	std::string temp;
	std::ifstream myfile;
	imageOne = IMG_Load("Test.png");
	textureOne = SDL_CreateTextureFromSurface(renderer, imageOne);
	int index = 0;
	for (int r = 0; r < 16; r++)
	{
		for (int c = 0; c < 16; c++)
		{
			index++;
			temp = "R :" + std::to_string(r) + " C: " + std::to_string(c);
			graph.addNode(std::numeric_limits<int>::max() - 10000, temp,r,c);
			renderObjs.push_back(new RenderObject(textureOne, 0, 0, 10, 10, c * 10 + (50), r * 10 + (10), 10, 10,index));

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

void CoreLoop::Collision()
{
	for (int i = 0; i < agents.size(); i++)
	{
		if (m_player.m_nodeID == agents.at(i)->m_nodeID)
		{
			std::cout << "Collision" << std::endl;
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

void CoreLoop::RunAmbushStar()
{
	for (int i = agents.size(); i < 4; i++)
	{
		agents.push_back(new Agent(i, start));
	}

	for (int i = 0; i < agents.size(); i++)
	{
		renderObjs.at(agents.at(i)->m_nodeID)->setTexture(textureOne);
		graph.aStarAmbush(graph.nodes.at(agents.at(i)->m_nodeID), graph.nodes.at(end), agents.at(i), agents);
  		std::cout << "Agent "<<(i+1) << std::endl;
		OutputPath(agents.at(i)->path, agents.at(i)->m_nodeID);
		if (agents.at(i)->path.size() > 1)
		{
			agents.at(i)->m_nodeID = graph.GetIndex(agents.at(i)->path.at(agents.at(i)->path.size() - 2)->id);
		}
	}

	imageTwo = IMG_Load("Test2.png");
	textureTwo = SDL_CreateTextureFromSurface(renderer, imageTwo);

	for (int i = 0; i < agents.size(); i++)
	{
		renderObjs.at(agents.at(i)->m_nodeID)->setTexture(textureTwo);
	}

}
