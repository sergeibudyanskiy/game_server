#ifndef CHAT_SERVER_H
#define CHAT_SERVER_H

#pragma once
#include "chat_session.h"

class chat_server
{
public:

	chat_server(boost::asio::io_context& io_context, const tcp::endpoint& endpoint);

private:

	void do_accept();

	tcp::acceptor acceptor_;
	chat_room room_;
};

#endif // !CHAT_SERVER_H