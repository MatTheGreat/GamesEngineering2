#include "ThreadManager.h"

SDL_sem *renderSem;

ThreadManager::ThreadManager()
{
	
	renderSem = SDL_CreateSemaphore(1);
	objsOne = new std::vector<RenderObject*>();
	objsTwo = new std::vector<RenderObject*>();
	idOne = new int(1);
	idTwo = new int(2);
}

ThreadManager::~ThreadManager()
{

}

static int RenderingThread(void *ptr)
{
	RenderManager * pRenderManager = nullptr;
	std::vector<RenderObject*>* pRenderObjs = nullptr;
	std::vector<std::pair<void *, int>> * data = static_cast<std::vector<std::pair<void *, int>>*>(ptr);
	int * id = nullptr;
	for (int i = 0; i < data->size(); i++)
	{
		if (data->at(i).second == 0)
		{
			pRenderManager = static_cast<RenderManager*>(data->at(i).first);
		}
		if (data->at(i).second == 1)
		{
			pRenderObjs = static_cast<std::vector<RenderObject*>*>(data->at(i).first);
		}
		if (data->at(i).second == 2)
		{
			id = static_cast<int*>(data->at(i).first);
		}
	}

	for (int i = 0; i < pRenderObjs->size(); i++)
	{
		SDL_SemWait(renderSem);
		std::cout << *id << std::endl;
		pRenderManager->DrawObject(pRenderObjs->at(i));
		SDL_SemPost(renderSem);
	}
	return 0;
}

void ThreadManager::Render(RenderManager* renderManager, std::vector<RenderObject*> renderObjs)
{

	//First Thread

	dataOne = new std::vector<std::pair<void *, int>>();
	dataOne->push_back(std::make_pair(renderManager, 0));
	for (int i = 0; i < (renderObjs.size() / 2); i++)
	{
		objsOne->push_back(renderObjs.at(i));
	}
	dataOne->push_back(std::make_pair(objsOne, 1));
	dataOne->push_back(std::make_pair(idOne, 2));
	void * voidPtrOne = dataOne;

	//Second Thread
	
	dataTwo = new std::vector<std::pair<void *, int>>();
	dataTwo->push_back(std::make_pair(renderManager, 0));
	for (int i = (renderObjs.size() / 2); i < renderObjs.size(); i++)
	{
		objsTwo->push_back(renderObjs.at(i));
	}
	dataTwo->push_back(std::make_pair(objsTwo, 1));
	dataTwo->push_back(std::make_pair(idTwo, 2));
	void * voidPtrTwo = dataTwo;

	
	threadOne = SDL_CreateThread(RenderingThread, "ThreadOne", voidPtrOne);
	threadTwo = SDL_CreateThread(RenderingThread, "ThreadTwo", voidPtrTwo);

	SDL_WaitThread(threadOne, NULL);
	SDL_WaitThread(threadTwo, NULL);
}
