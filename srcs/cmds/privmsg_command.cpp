#include "../../ft_irc.hpp"

Client	*getClientByName(Server *server, std::string name)
{
	std::map<int, Client*>::iterator it = server->client.begin();
	std::map<int, Client*>::iterator ite = server->client.end();

	for (; it != ite; it++)
	{
		if ((*it).second->getNickname() == name)
			return (*it).second;
	}
	return (nullptr);
}

void	privmsg_command(std::vector<std::string> cmd, int clientFd, Server *server)
{
	if (cmd.size() == 1)
	{
		send_error("411", server->client[clientFd]->getNickname(), "No receiver given", clientFd);
		return;
	}
	if (cmd.size() == 2)
	{
		send_error("412", server->client[clientFd]->getNickname(), "No text to send", clientFd);
		return;
	}
	std::vector<std::string>	checker = ft_split(cmd[1], ",");
	if (checker.size() != 1)
	{
		send_error("407", server->client[clientFd]->getNickname(), "Duplicate recipients. No message delivered", clientFd);
		return;
	}
	if (cmd[1].front() == '#')
	{
		if (server->channelList.find(cmd[1]) == server->channelList.end())
		{
			std::string	msg = ":PokeIRC 401 " + server->client[clientFd]->getNickname() + " " + cmd[1] + " :No such nick/channel\r\n";
			send(clientFd, msg.c_str(), msg.length(), 0);
			return;
		}
		Channel	*chan = server->channelList[cmd[1]];
		std::string	msg = cmd[2] + "\r\n";
		for (std::vector<int>::iterator it = chan->clients.begin(); it != chan->clients.end(); it++)
			send(*it, msg.c_str(), msg.length(), 0);
	}
	else
	{
		Client	*receiver = getClientByName(server, cmd[1]);
		if (!receiver)
		{
			std::string	msg = ":PokeIRC 401 " + server->client[clientFd]->getNickname() + " " + cmd[1] + " :No such nick/channel\r\n";
			send(clientFd, msg.c_str(), msg.length(), 0);
			return;
		}
		std::string	msg = cmd[2] + "\r\n";
		send(receiver->getFd(), msg.c_str(), msg.length(), 0);
	}
}