#pragma once
#include "Command.h"

class JumpCommand : public Command
{
public:
	JumpCommand(Receiver* receiver) :Command(receiver) {};
	virtual void execute() { pReceiver->Action("Jump"); };

};

