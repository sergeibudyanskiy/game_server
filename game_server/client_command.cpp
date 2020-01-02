#include "client_command.h"

ClientCommand::ClientCommand(chat_message cm)
{
	std::cout << "named \"ClientCommand\" was created \"chat_message\".\n";
	this->cmd = cm;
}

ClientCommand::ClientCommand(const char* str)
{
	std::cout << "named \"ClientCommand\" was created by \"const char\".\n";
	chat_message cm;
	cm.body_length(std::strlen(str));
	std::memcpy(cm.body(), str, cm.body_length());
	cm.encode_header();
	this->cmd = cm;
}

ClientCommand::~ClientCommand()
{
	std::cout << "Command named \"ClientCommand\" was ";
}

chat_message ClientCommand::getCommand() const
{
	return this->cmd;
}