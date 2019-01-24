#pragma once

#include "ICommand.h"
#include <memory>
#include <deque>

typedef std::unique_ptr<ICommand> ICommandPtr;

class CHistory
{
public:
	CHistory();
	~CHistory();

	bool CanUndo() const;
	void Undo();
	bool CanRedo() const;
	void Redo();
	void AddAndExecuteCommand(ICommandPtr&& command);

private:
	std::deque<ICommandPtr> m_commands;
	size_t m_nextCommandIndex = 0;
};