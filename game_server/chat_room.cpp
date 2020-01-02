#include "chat_room.h"

void chat_room::join(chat_participant_ptr participant)
{
	participants_.insert(participant);

	chat_message cm;
	char cmd_str[] = "> ClientCommand connected";
	cm.body_length(strlen(cmd_str));
	std::memcpy(cm.body(), cmd_str, cm.body_length());
	cm.encode_header();
	
	recent_msgs_.push_back(cm);

	for (auto msg : recent_msgs_) participant->deliver(msg);
}

void chat_room::leave(chat_participant_ptr participant)
{
	Command* cmd = new ClientCommand("> ClientCommand unconnected");
	chat_message cm = cmd->getCommand();
	std::cout.write(cm.body(), cm.body_length()) << std::endl;
	delete cmd;

	recent_msgs_.push_back(cm);

	participants_.erase(participant);
}

void chat_room::deliver(const chat_message& msg)
{
	recent_msgs_.push_back(msg);
	while (recent_msgs_.size() > max_recent_msgs) recent_msgs_.pop_front();
	for (auto participant : participants_) participant->deliver(msg);
}