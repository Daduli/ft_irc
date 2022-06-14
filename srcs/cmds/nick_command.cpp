#include "../../ft_irc.hpp"

void	nickname_parse(std::vector<std::string> cmd, int clientFd, Server *server)
{
	if (cmd.size() == 2)
	{
		if (!isalpha(cmd[1][0]))
			send_error("432", server->client[clientFd]->getNickname(), "Erroneus nickname.", clientFd);
		for (std::string::iterator it=cmd[1].begin(); it!=cmd[1].end(); it++)
		{
			if (!isalnum(*it) && *it != '_' && *it != '-')
			{
				send_error("432", server->client[clientFd]->getNickname(), "Erroneus nickname.", clientFd);
				return;
			}
		}
		if (cmd[1].length() > 30)
		{
			send_error("432", server->client[clientFd]->getNickname(), "Erroneus nickname.", clientFd);
			return;
		}
		for (std::vector<std::string>::iterator it = server->_nicknameList.begin(); it != server->_nicknameList.end(); it++)
		{
			if (*it == cmd[1])
			{
				if (server->client[clientFd]->_isConnected)
					send_error("433", server->client[clientFd]->getNickname(), "Nickname already used.", clientFd);
				else
					send_error("436", server->client[clientFd]->getNickname(), "Nickname collision.", clientFd);
				return;
			}
		}
	}
}

void	nick_command(std::vector<std::string> cmd, int clientFd, Server *server)
{
	if (!server->client[clientFd]->_passwordOk)
	{
		send(clientFd, "You must enter the password first.\r\n", strlen("You must enter the password first.\r\n"), 0);
		return;
	}
	nickname_parse(cmd, clientFd, server);
	std::string msg;
	if (server->client[clientFd]->_isConnected)
	{
		if (cmd.size() == 1)
		{	
			msg = "Nickname: " + server->client[clientFd]->getNickname() + "\r\n";
			send(clientFd, msg.c_str(), msg.length(), 0);
		}
		else
			{
				msg = ":" + server->client[clientFd]->getNickname() + "!" + server->client[clientFd]->getUsername() + "127.0.0.1 NICK :" + cmd[1] + "\r\n";
				std::cout << msg << std::endl;
				send(clientFd, msg.c_str(), msg.length(), 0);
				server->client[clientFd]->setNickname(cmd[1]);
			}
	}
	else
	{
		if (cmd.size() == 1)
		{
			send_error("431", server->client[clientFd]->getNickname(), "No nickname given", clientFd);
			return;
		}
		server->client[clientFd]->setNickname(cmd[1]);
		server->client[clientFd]->_nicknameOk = 1;
	}
	if (server->client[clientFd]->_passwordOk && server->client[clientFd]->_nicknameOk && server->client[clientFd]->_usernameOk && !server->client[clientFd]->_isConnected)
	{
		server->client[clientFd]->_isConnected = true;
		send_error("001", server->client[clientFd]->getNickname(), "Welcome to PokeIRC!", clientFd);
	}
}