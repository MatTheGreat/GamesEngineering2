#pragma once
#include "Receiver.h"

class Command
{
public:
	virtual ~Command() {};
	virtual void execute() = 0;

protected:
	Receiver* pReceiver;
	Command() {};
	Command(Receiver* receiver) : pReceiver(receiver) {};
	
};

