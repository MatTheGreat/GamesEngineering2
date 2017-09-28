#pragma once
#include "Command.h"

class FireCommand : public Command
{
public:
	FireCommand(Receiver* receiver) :Command(receiver) {};
	virtual void execute() { pReceiver->Action("Fire"); };

};