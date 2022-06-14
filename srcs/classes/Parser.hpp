#ifndef PARSER_HPP
#define PARSER_HPP

/*==========================*/
/*=====    INCLUDES    =====*/
/*==========================*/

#include <string>
#include <vector>
#include <map>
#include "Client.hpp"

/*==========================*/
/*=======    CLASS    ======*/
/*==========================*/

class Server;

class Parser
{
	public:

	Parser(void);
	~Parser(void);

	void	parseCommand(std::string message, int clientFd, Server *server);
	void	getCommand(std::vector<std::string> cmd, int clientFd, Server *server);

	//command to add:
	//PASS
	//NICK
	//USER
	//JOIN
	//PART
	//PRIVMSG
	//KILL
	//QUIT
	//KICK
	//MODE
	//INVITE
	//TOPIC

	private:

		std::string	_command;

};

std::vector<std::string>	ft_split (std::string str, std::string delimiter);
void	ft_error(std::string s);

void	send_error(std::string code, std::string nickname, std::string toSend, int clientFd);
void	send_error_1(std::string code, std::string nickname, std::string toSend, int clientFd, std::string arg);
void	sendMode(std::string code, std::string nickname, int clientFd, std::string arg);
void	send_msg(int clientFd, std::string msg);
void	pass_command(std::vector<std::string> cmd, int clientFd, Server *server);
void	user_command(std::vector<std::string> cmd, int clientFd, Server *server);
void	nick_command(std::vector<std::string> cmd, int clientFd, Server *server);
void	ping_command(std::vector<std::string> cmd, int clientFd, Server *server);
void	oper_command(std::vector<std::string> cmd, int clientFd, Server *server);
void 	mode_command(std::vector<std::string> cmd, int clientFd, Server *server);
//void	join_command(std::vector<std::string> cmd, int clientFd, Server *server);

//      (:<préfixe>) <commande> (<paramètres>) <crnl>
//	Exemples:
//		NICK amy
//		WHOIS doctor
//		MODE amy +o
//		JOIN #tardis
//		QUIT
//maximum 15 paramètres
//si ':' sur le dernier paramètre -> message à envoyer

#endif