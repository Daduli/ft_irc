#include "../../ft_irc.hpp"

void	part_command(std::vector<std::string> cmd, int clientFd, Server *server)
{
	if (cmd.size() < 2)
	{
		send_error("461", server->client[clientFd]->getNickname(), "Not enough parameters", clientFd);
		return;
	}
	std::vector<std::string>	channels = ft_split(cmd[1], ",");
	for (std::vector<std::string>::iterator it = channels.begin(); it != channels.end(); it++)
	{	
		if (server->channelList.find(*it) == server->channelList.end())
		{
			send_error_1("403", server->client[clientFd]->getNickname(), "No such channel", clientFd, *it);
			return;
		}
		std::vector<int>::iterator	toDelete;
		Channel	*chan = server->channelList[*it];
		if ((toDelete = std::find(chan->clients.begin(), chan->clients.end(), clientFd)) == chan->clients.end())
		{
			send_error_1("442", server->client[clientFd]->getNickname(), "You're not on that channel",clientFd, *it);
			return;
		}
		std::string	msg;
		for (std::vector<int>::iterator client = chan->clients.begin(); client != chan->clients.end(); client++)
		{
			if (*client != clientFd)
			{	
				msg = ":" + server->client[clientFd]->getNickname() + "!" + server->client[clientFd]->getUsername() + "@127.0.0.1 PART :" + *it + "\r\n";
				send(*client, msg.c_str(), msg.length(), 0);
			}
			else
			{	
				msg = ":" + server->client[clientFd]->getNickname() + "!" + server->client[clientFd]->getUsername() + "@127.0.0.1 PART :" + *it + "\r\n";
				send(clientFd, msg.c_str(), msg.length(), 0);
			}		
		}
		chan->clients.erase(toDelete);
		if (chan->clients.empty())
		{	
			std::map<std::string, Channel *>::iterator	delChannel = server->channelList.find(*it);
			delete delChannel->second;
			server->channelList.erase(*it);
		}
	}
}
