// Multi-Threaded Visualisation.cpp : Defines the entry point for the console application.
//


#include "CoreLoop.h"


int main()
{
	CoreLoop loop = CoreLoop();
	while (loop.Loop() == true)
	{

	}
    return 0;
}

