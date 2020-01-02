#include <iostream>
#include <cstring>
#include <malloc.h>
#include "command.h"
#include "client_command.h"
#include "default_command.h"
#include "chat_server.h"

int main(int argc, char* argv[])
{
	try
	{
		argv[1] = (char*)"4000";
		argc = 2;
		if (argc < 2)
		{
			std::cerr << "Usage: chat_server <port> [<port> ...]\n";
			return 1;
		}

		boost::asio::io_context io_context;

		std::list<chat_server> servers;
		for (int i = 1; i < argc; ++i)
		{
			tcp::endpoint endpoint(tcp::v4(), std::atoi(argv[i]));
			servers.emplace_back(io_context, endpoint);
		}

		io_context.run();
	}
	catch (std::exception & e)
	{
		std::cerr << "Exception: " << e.what() << "\n";
	}

	return 0;
}