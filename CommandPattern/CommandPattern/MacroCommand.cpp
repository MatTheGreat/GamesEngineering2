#pragma once
#include "MacroCommand.h"
#include <iterator>

void MacroCommand::execute()
{
	for (std::list<Command*>::const_iterator i = commands->begin(), end = commands->end(); i != end; ++i)
	{
		Command * c = *i;
		c->execute();
	}
}

void MacroCommand::add(Command* newMacro)
{
	commands->push_back(newMacro);
}

void MacroCommand::remove(Command* removeMacro)
{
	commands->remove(removeMacro);
}