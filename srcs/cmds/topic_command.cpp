#include "../../ft_irc.hpp"

void	topic_command(std::vector<std::string> cmd, int clientFd, Server *server)
{
	if (cmd.size() < 2)
	{
		send_error("461", server->client[clientFd]->getNickname(), "Not enough parameters", clientFd);
		return;
	}
	if (server->channelList.find(cmd[1]) == server->channelList.end())
	{
		send_error_1("442", server->client[clientFd]->getNickname(), "You're not on that channel", clientFd, cmd[1]);
		return;
	}
	Channel	*chan = server->channelList[cmd[1]];
	if (std::find(chan->clients.begin(), chan->clients.end(), clientFd) == chan->clients.end())
	{
		send_error_1("442", server->client[clientFd]->getNickname(), "You're not on that channel", clientFd, cmd[1]);
		return;
	}
	if (cmd[].size() == 0)
	{

	}
	else
	{
		//format: :tle!~tle@freenode-a99.759.j1faas.IP TOPIC #bfiursg :hello	
	}
}