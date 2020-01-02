#ifndef CLIENT_COMMAND_H
#define CLIENT_COMMAND_H

#pragma once
#include <string>
#include "command.h"

class ClientCommand : public Command
{
public:

	ClientCommand(chat_message);
	
	ClientCommand(const char*);

	~ClientCommand();

	chat_message getCommand() const;

};


#endif // !CLIENT_COMMAND_H