#include "../../ft_irc.hpp"

// Client	*getClientByname(Server *server, std::string name)
// {
// 	std::map<int, Client*>::iterator it = server->client.begin();
// 	std::map<int, Client*>::iterator ite = server->client.end();

// 	for (; it != ite; it++)
// 	{
// 		if ((*it).second->getNickname() == name)
// 			return (*it).second;
// 	}
// 	return (nullptr);
// }

bool mode_parser(std::vector<std::string> cmd, Client *client_target, int clientFd, Server *server) {

    std::string mode = client_target->getMode();
    bool clear = false;
    std::string options = "+-iwos";

    for (size_t i = 0; i != cmd.size() - 1; ++i)
    {
        if (cmd[2][i] == '-')      
                clear = true;
		else if (cmd[2][i] == '+')
				clear = false;
        if (options.find(cmd[2][i]) == std::string::npos)
		{
            send_error("501", server->client[clientFd]->getNickname(), "Unknown MODE flag", clientFd);
            return false;
        }
        else
        {
            if (clear == true && (&mode)->find(cmd[2][i]) != std::string::npos)
		    {
                if (cmd[2][i] != '+' && cmd[2][i] != '-')
                {
                    (&mode)->erase((&mode)->find(cmd[2][i]), 1);
                    server->client[clientFd]->setMode(mode);
                }
            }
            else if (clear == false && (&mode)->find(cmd[2][i]) == std::string::npos)
            {
                if (cmd[2][i] != '+' && cmd[2][i] != '-' && cmd[2][i] != 'o')
                {
                    (&mode)->push_back(cmd[2][i]);
                    server->client[clientFd]->setMode(mode);
                }
            }
        }
    }
    sendMode("221", server->client[clientFd]->getNickname(), client_target->getFd(), server->client[clientFd]->getMode());
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
        client_target = server->getClientBynick(cmd[1]);
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

bool ModeForChannel(int clientFd, Server *server) {

    std::string mode = "nt";

    sendMode("221", server->client[clientFd]->getNickname(), clientFd, mode);
    return true;
}

void 	mode_command(std::vector<std::string> cmd, int clientFd, Server *server) {
	
    if(cmd[1].find("#") != std::string::npos)
    {
        if (!ModeForChannel(clientFd, server))
            return;
    }   
    else
    {
        if (cmd.size() != 3)
        {
	        send_error_1("461", server->client[clientFd]->getNickname(), "Not enough parameters", clientFd, cmd[0]);
            return;
        }         
        if (!ModeForUser(cmd, clientFd, server))
            return;
    }
}