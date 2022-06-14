#include "Client.hpp"

Client::Client(void)
{
	_isConnected = false;
	_passwordOk = false;
	return;
}

Client::~Client(void)
{
	return;
}

std::string &Client::getMessage(void)
{
	return this->_message;
}

void	Client::setMessage(std::string const &message)
{
	_message += message;
}

const std::string &Client::getNickname(void) const
{
	return this->_nickname;
}

void	Client::setNickname(std::string const &nickname)
{
	_nickname = nickname;
}

std::string	const &Client::getUsername(void) const
{
	return _username;
}

void	Client::setUsername(std::string const &username)
{
	_username = username;
}