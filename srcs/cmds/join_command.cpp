#include "../../ft_irc.hpp"

void	join_command(std::vector<std::string> cmd, int clientFd, Server *server)
{
	if (cmd.size() == 1)
	{
		send_error("461", server->client[clientFd]->getNickname(), "Not enough parameters", clientFd);
		return;
	}
	std::vector<std::string>	channels = ft_split(cmd[1], ",");
	if (cmd.size() > 11 || server->client[clientFd]->getChannelNb() + channels.size() > 10)
	{
		send_error("405", server->client[clientFd]->getNickname(), "You have joined too many channels", clientFd);
		return;
	}
	for (std::vector<std::string>::iterator it = channels.begin(); it != channels.end(); it++)
	{	
		if ((*it)[0] != '#')
		{
			std::string	msg = ":PokeIRC 403 " + server->client[clientFd]->getNickname() + " " + *it + " :No such channel\r\n";
			send(clientFd, msg.c_str(), msg.length(), 0);
			return;
		}
		if (server->channelList.find(*it) == server->channelList.end())
		{
			Channel *newChannel = new Channel();
			server->client[clientFd]->setChannelNb(1);
			newChannel->clients.push_back(clientFd);
			server->channelList.insert(std::pair<std::string, Channel *>(*it, newChannel));
		}
		else
		{
			if (std::find(server->channelList[*it]->clients.begin(), server->channelList[*it]->clients.end(), clientFd) == server->channelList[*it]->clients.end())
			{
				std::string	toSend;
				server->client[clientFd]->setChannelNb(1);
				server->channelList[*it]->clients.push_back(clientFd);
				for (std::vector<int>::iterator itt = server->channelList[*it]->clients.begin(); itt != server->channelList[*it]->clients.end(); itt++)
				{
					toSend = ":" + server->client[clientFd]->getUsername() + " JOIN " + *it + "\r\n";
					if (*itt != clientFd)
						send(*itt, toSend.c_str(), toSend.length(), 0);
				}
			}
		}
	}
}