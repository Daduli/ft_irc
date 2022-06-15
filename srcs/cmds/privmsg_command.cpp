#include "../../ft_irc.hpp"

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
		// implementer la fonction send_error1 de samir une fois merge  
		send_error("407", server->client[clientFd]->getNickname(), "Duplicate recipients. No message delivered", clientFd);
		return;
	}
	
	if (cmd[1].front() == '#')
	{
		std::cout << "Channel\n";
		;
	}
	else
	{
		//if (server->client.find(server->client) == server->client.end())
		//{
		//	std::cout<<"hello"<<std::endl;
		//	std::string	msg = ":PokeIRC 401 " + server->client[clientFd]->getNickname() + " " + cmd[1] + " :No such nick/channel\r\n";
		//	send(clientFd, msg.c_str(), msg.length(), 0);
		//	return;
		//}
	}

	// reste a envoyer le msg et checker si c'est un channel ou un utilisateur pour l'erreur ERR_NOSUCHNICK.

	// std::string = 
	// send(clientFd, )
}