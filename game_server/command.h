#ifndef COMMAND_H
#define COMMAND_H

#pragma once
#include "chat_message.h"
#include <string>
#include <iostream>
#include <vector>

class Command
{
public:

	Command();

	virtual ~Command();

	virtual chat_message getCommand() const = 0;

protected:

	chat_message cmd;
};

#endif // !COMMAND_H