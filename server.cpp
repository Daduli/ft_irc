/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 42 <42@student.42nice.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 08:47:31 by asebrech          #+#    #+#             */
/*   Updated: 2022/05/04 11:27:07 by asebrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#include <exception>
#include <iostream>

int	main (int ac, char **av)
{
	/*
	* socket() creates an endpoint for communication and returns a file
       	* descriptor that refers to that endpoint.
	* AF_INET : IPv4
	* SOCK_STREAM : TCP
	* 0 : IP
	*/

	int	sockfd = 0;
	try
	{
		if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
			throw	std::runtime_error("socket failed");
	}
	catch (std::exception & e) {std::cout << e.what() << std::endl;}

	/* Structures for handling internet addresses
	* sin_family : protocol family (IPv4)
	* s_addr : IP | INADDR_ANY : any IP
	* sin_port : port | htons() : htons function converts a u_short from host
	* to TCP/IP network byte order
	*/

	struct sockaddr_in	address;	
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(4242);

	/*bind() assigns the address specified by addr to the socket referred to
        * by the file descriptor sockfd.
	*/

	try
	{
		if (bind(sockfd, (struct sockaddr *)&address, sizeof(address)) < 0)
			throw	std::runtime_error("bind failed");
	}
	catch (std::exception & e) {std::cout << e.what() << std::endl;}

	/*
	* listen() marks the socket referred to by sockfd as a passive
        * socket, that is, as a socket that will be used to accept incoming
        * connection requests using accept(2).
	*/

	try
	{
		if (listen(sockfd, 3) < 0)
			throw	std::runtime_error("listen failed");
	}
	catch (std::exception & e) {std::cout << e.what() << std::endl;}

	/*
	* accept() extracts the first connection request on the queue of pending connections
	* for the listening socket, sockfd, creates a new connected socket, and
        * returns a new file descriptor referring to that socket.
	*/

	int	addrlen = sizeof(address);
	int	new_socket = 0;
	while (true)
	{
		try
		{
			if ((new_socket = accept(sockfd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0)
				throw	std::runtime_error("accept failed");
		}
		catch (std::exception & e) {std::cout << e.what() << std::endl;}

		char	buffer[1024];
		read(new_socket, buffer, 1024);
		std::cout << buffer << std::endl;
	}
	return (0);
}
