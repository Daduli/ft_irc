#include "Server.hpp"
#include "Client.hpp"
#include "Parser.hpp"
#include <iostream>

Server::Server(void)
{
	return;
}

Server::~Server(void)
{
	return;
}

void	Server::setPassword(std::string password)
{
	_password = password;
}

std::string const &Server::getPassword(void) const
{
	return (_password);
}

// lire le ircserv.config && recuperer ligne par ligne et stocker 'op_pass'(stocker dans une string)
void	Server::getConfig(std::string param) 
{
	std::ifstream ifs(param);
	std::string temp;
	size_t pos;

	if(!ifs.is_open())
		ft_error("Error: cannot open file");
	while(getline(ifs, temp))
	{
		if(temp.compare("op_pass") == 0)
			break;
	}
	pos = temp.find("=");
	_operatorPwd = temp.substr(pos + 2, temp.length());
}

void	Server::deleteClient(void)
{
	std::vector<int>::iterator	it = clientFds.begin();
	std::vector<int>::iterator	ite = clientFds.end();
	std::map<int, Client *>::iterator clientIt;

	for ( ; it != ite; it++)
	{
		clientIt = client.find(*it);
		delete clientIt->second;
		close (clientIt->first);
		client.erase(clientIt->first);
	}
	clientFds.clear();
}

void	Server::serverAccept(void)
{
	struct sockaddr_in address;
	socklen_t addr_len = sizeof(address);
	int	newSock;
	Client	*user = new Client();

	newSock = accept(socketFd, (struct sockaddr*)&address, &addr_len);
	fcntl(newSock, F_SETFL, O_NONBLOCK);
	client.insert(std::pair<int, Client *>(newSock, user));
	client[newSock]->setFd(newSock);
}


void	Server::receiveMessage(int clientFd, std::string buffer)
{
	if (buffer.length() > 510)
	{
		send(clientFd, "Warning: Limit of a string is 512 characters\r\n", 47, 0);
		return;
	}
	std::vector<std::string>	array;
	if (buffer.find('\n') == std::string::npos)
		client[clientFd]->setMessage(buffer);
	else if (!client[clientFd]->getMessage().empty())
	{
		client[clientFd]->setMessage(buffer);
		array.push_back(client[clientFd]->getMessage());
		//array = ft_split(client[clientFd]->getMessage(), "\n");
		//split on \r\n then \n
		//a message can have multiple commands separated with '\r\n'
	}
	else
	{
		client[clientFd]->setMessage(buffer);
		array = ft_split(client[clientFd]->getMessage(), "\r\n");

		//split on \n then space
	}
	if (client[clientFd]->getMessage().find('\n') != std::string::npos)
	{
		for (std::vector<std::string>::iterator it = array.begin(); it != array.end(); it++)
			_parse.parseCommand(*it, clientFd, this);
		client[clientFd]->getMessage().clear();
	}
	//transform msg into cmd
	//parse cmd only
}

void	Server::clientDisconnect(int socketFd)
{
	clientFds.push_back(socketFd);
	std::cout << "Client disconnected" << std::endl;
}