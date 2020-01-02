#ifndef CHAT_ROOM_H
#define CHAT_ROOM_H

#pragma once
#include "chat_participant.h"
#include "command.h"
#include "client_command.h"
#include "default_command.h"

class chat_room
{
public:

	void join(chat_participant_ptr participant);

	void leave(chat_participant_ptr participant);

	void deliver(const chat_message& msg);

private:

	std::set<chat_participant_ptr> participants_;
	enum { max_recent_msgs = 100 };
	chat_message_queue recent_msgs_;
};

#endif // !CHAT_ROOM_H