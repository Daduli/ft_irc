#include "../../ft_irc.hpp"

void	oper_command(std::vector<std::string> cmd, int clientFd, Server *server) {

    if (cmd.size() != 3)
	{
        send_error_1("461", server->client[clientFd]->getNickname(), "Not enough parameters", clientFd, cmd[0]);
        return;
    }
    if (cmd[2] != server->getOperatorPass() || cmd[1] != server->getAdmin())
    {
        send_error("464", server->client[clientFd]->getNickname(), "Password incorrect", clientFd);
        return;
    }
    send_error("381", server->client[clientFd]->getNickname(), "Password You are now an IRC operator", clientFd);
    if (server->client[clientFd]->getMode().find('o') == std::string::npos)
	{
		server->client[clientFd]->setMode(server->client[clientFd]->getMode() + "o");
        sendMode("221", server->client[clientFd]->getNickname(), clientFd, server->client[clientFd]->getMode());
	}

}