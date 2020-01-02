#ifndef CHAT_PARTICIPANT_H
#define CHAT_PARTICIPANT_H

#pragma once
#include <cstdlib>
#include <deque>
#include <iostream>
#include <list>
#include <memory>
#include <set>
#include <utility>
#include <map>
#include <boost/asio.hpp>
#include "chat_message.h"

using boost::asio::ip::tcp;

typedef std::deque<chat_message> chat_message_queue;

class chat_participant
{
public:

	virtual ~chat_participant();

	virtual void deliver(const chat_message& msg) = 0;
};

typedef std::shared_ptr<chat_participant> chat_participant_ptr;

#endif // !CHAT_PARTICIPANT_H