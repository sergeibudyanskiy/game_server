#include "default_command.h"

DefaultCommand::DefaultCommand(chat_message cm)
{
	std::cout << "named \"DefaultCommand\" was created.\n";
	this->cmd = cm;
}

DefaultCommand::~DefaultCommand()
{
	std::cout << "Command named \"DefaultCommand\" was ";
}

chat_message DefaultCommand::getCommand() const
{
	return this->cmd;
}