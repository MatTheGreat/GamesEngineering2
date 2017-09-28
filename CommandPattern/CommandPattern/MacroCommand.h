#pragma once
#include <list>
#include "Command.h"

class MacroCommand : public Command
{
	public:
		MacroCommand();
		virtual ~MacroCommand();
		virtual void add(Command* newMacro);
		virtual void remove(Command* removeMacro);
		virtual void execute();
	private:
		std::list<Command*>* commands;

};