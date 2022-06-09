#include "../../ft_irc.hpp"

void	send_error(std::string code, std::string nickname, std::string toSend, int clientFd)
{
	std::string	message;

	message = ":PokeIRC " + code + " " + nickname + " :" + toSend + "\r\n";
	send(clientFd, message.c_str(), message.length(), 0);
}