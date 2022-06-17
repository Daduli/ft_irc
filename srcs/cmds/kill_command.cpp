#include "../../ft_irc.hpp"

Client  *getClientBynick(Server *server, std::string name)
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

void 	kill_command(std::vector<std::string> cmd, int clientFd, Server *server) {

    Client *client_target = NULL;
    
    if (cmd.size() != 3)
	{
        send_error_1("461", server->client[clientFd]->getNickname(), "Not enough parameters", clientFd, cmd[0]);
        return;
    }	
    if (server->client[clientFd]->getMode().find('o') == std::string::npos)
	{
        send_error("481", server->client[clientFd]->getNickname(), "Permission Denied- You're not an IRC operator", clientFd);
        return;
    }
    client_target = getClientBynick(server, cmd[1]);
	if (!client_target)
	{
            send_error_1("401", server->client[clientFd]->getNickname(), "No such nick/channel", clientFd, cmd[1]);
            return;
    }
    std::string msg = ":" + server->client[clientFd]->getNickname() + "!" + server->client[clientFd]->getUsername() + "127.0.0.1 KILL :" + cmd[2] + "\r\n";
    send(client_target->getFd(), msg.c_str(), msg.length(), 0);
    server->clientDisconnect(client_target->getFd());
}
