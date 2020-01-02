#include "chat_session.h"

void deleteSpaces(std::string& str)
{
	size_t begin = str.find_first_not_of(' ');
	size_t end = str.find_last_not_of(' ');
	str.erase(end + 1, str.size() - end);
	str.erase(0, begin);
}

const std::vector<std::vector<std::string>> commands = {
	{
		"ClientCommand ",
		"connected ",
		"unconnected ",
		"play ",
		"pause ",
		"registrate "
	}
};

Command* determineCommandType(const char* str)
{
	chat_message msg;
	msg.body_length(strlen(str));
	std::memcpy(msg.body(), str, msg.body_length());
	msg.encode_header();

	std::string copy = str;
	deleteSpaces(copy);
	if (copy.find("> ") == 0)
	{
		for (size_t i = 0; i < commands.size(); ++i)
		{
			if (copy.find(commands[i][0]) < copy.length())
			{
				for (size_t j = 0; j < commands[i].size(); ++j)
				{
					if (copy.find(commands[i][j]) < copy.length())
					{
						switch (i)
						{
						case 0:
							return new ClientCommand(msg);
						default:
							break;
						}
					}
				}
			}
		}

		return new DefaultCommand(msg);
	}
	else return nullptr;
}

chat_session::chat_session(tcp::socket socket, chat_room& room) : socket_(std::move(socket)), room_(room)
{
}

void chat_session::start()
{
	room_.join(shared_from_this());
	do_read_header();
}

void chat_session::deliver(const chat_message& msg)
{
	bool write_in_progress = !write_msgs_.empty();
	write_msgs_.push_back(msg);

	if (!write_in_progress)
	{	
		std::unique_ptr<Command> cmd(determineCommandType(msg.body()));
		std::cout.write(msg.body(), msg.body_length()) << std::endl;
		do_write();
	}
}

void chat_session::do_read_header()
{
	auto self(shared_from_this());
	boost::asio::async_read(socket_, boost::asio::buffer(read_msg_.data(), chat_message::header_length),
		[this, self](boost::system::error_code ec, std::size_t /*length*/)
		{
			if (!ec && read_msg_.decode_header()) do_read_body();
			else room_.leave(shared_from_this());
		});
}

void chat_session::do_read_body()
{
	auto self(shared_from_this());
	boost::asio::async_read(socket_, boost::asio::buffer(read_msg_.body(), read_msg_.body_length()),
		[this, self](boost::system::error_code ec, std::size_t /*length*/)
		{
			if (!ec)
			{
				room_.deliver(read_msg_);
				do_read_header();
			}
			else room_.leave(shared_from_this());
		});
}

void chat_session::do_write()
{
	auto self(shared_from_this());
	boost::asio::async_write(socket_, boost::asio::buffer(write_msgs_.front().data(), write_msgs_.front().length()),
		[this, self](boost::system::error_code ec, std::size_t /*length*/)
		{
			if (!ec)
			{
				write_msgs_.pop_front();
				if (!write_msgs_.empty()) do_write();
			}
			else room_.leave(shared_from_this());
		});
}