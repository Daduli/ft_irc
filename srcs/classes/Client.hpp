#ifndef CLIENT_HPP
#define CLIENT_HPP

/*==========================*/
/*=====    INCLUDES    =====*/
/*==========================*/

#include <string>

/*==========================*/
/*=======    CLASS    ======*/
/*==========================*/

class Client
{
	public:

		Client(void);
		~Client(void);

		std::string &getMessage(void);
		void	setMessage(std::string const &message);
		std::string const &getNickname(void) const;
		void	setNickname(std::string const &nickname);
		std::string	const &getUsername(void) const;
		void	setUsername(std::string const &username);

		bool	_isConnected;
		bool	_passwordOk;
		bool	_nicknameOk;
		bool	_usernameOk;

	private:

		std::string	_message;
		std::string	_nickname;
		std::string	_username;

};

#endif