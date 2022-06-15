#include "Client.hpp"

Client::Client(void)
{
	_isConnected = false;
	_passwordOk = false;
	_channelNb = 0;
	return;
}

Client::~Client(void)
{
	return;
}

int const &Client::getFd(void) const
{
	return _fd;
}
		
void	Client::setFd(int const &fd)
{
	_fd = fd;
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

int	const &Client::getChannelNb(void) const
{
	return _channelNb;
}

void	Client::setChannelNb(int const &nb)
{
	if (nb > 0)
		_channelNb++;
	else
		_channelNb--;
}