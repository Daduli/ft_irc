#include "../../ft_irc.hpp"

bool ModeForUser(std::vector<std::string> cmd, int clientFd, Server *server) {

    Client *client_target = NULL;
    std::string options = "+-aiwro";
    //int clear = 0;

    if (cmd[1] == server->client[clientFd]->getNickname())
		client_target = server->client[clientFd];
    else
	{
	    if (server->client[clientFd]->getMode().find("o") == std::string::npos)
		{
            send_error("502", server->client[clientFd]->getNickname(), "Cant change mode for other users", clientFd);
            return false;
        }
        //client_target = cmd.getSender()->getServ()->getUserByname(cmd.getArgs()[0]);
		if (!client_target)
			return false;
	}
    

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