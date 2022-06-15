#include "../../ft_irc.hpp"

Client					*getClientByname(Server *server, std::string name)
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

bool mode_parser(std::vector<std::string> cmd, Client *client_target, int clientFd, Server *server) {

    std::string mode = client_target->getMode();
    bool clear;
    std::string options = "+-aiwro";

    for (size_t i = 0; i != cmd.size() - 1; ++i)
    {
        if (options.find(cmd[2][i]) == '-')
				clear = true;
		else if (options.find(cmd[2][i]) == '+')
				clear = false;
        if (options.find(cmd[2][i]) == std::string::npos)
		{
            send_error("502", server->client[clientFd]->getNickname(), "Unknown MODE flag", clientFd);
            return false;
        }



    }

    return true;
}



bool ModeForUser(std::vector<std::string> cmd, int clientFd, Server *server) {

    Client *client_target = NULL;
    std::string options = "+-aiwro";
    
    if (cmd[1] == server->client[clientFd]->getNickname())
		client_target = server->client[clientFd];
    else
	{
	    if (server->client[clientFd]->getMode().find("o") == std::string::npos)
		{
            send_error("502", server->client[clientFd]->getNickname(), "Cant change mode for other users", clientFd);
            return false;
        }
        client_target = getClientByname(server, cmd[1]);
		if (!client_target)
		{
            send_error_1("401", server->client[clientFd]->getNickname(), "No such nick/channel", clientFd, cmd[1]);
            return false;
        }
    }
    if (!mode_parser(cmd, client_target, clientFd, server))
        return false;

    return true;
}

void 	mode_command(std::vector<std::string> cmd, int clientFd, Server *server) {

    if (cmd.size() != 3)
    {
	    send_error_1("461", server->client[clientFd]->getNickname(), "Not enough parameters", clientFd, cmd[0]);
        return;
    }
    // //if (command->cmd->getArgs()[0].find("#") != std::string::npos)
    // //else
	if (!ModeForUser(cmd, clientFd, server))
      return;

}