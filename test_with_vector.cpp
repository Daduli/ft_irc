#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/select.h>
#include <unistd.h>
#include <iostream>
#include <string>
#include <vector>


int main()
{
	int opt = 1;
	int sockfd, new_sock, activity, i, valread, sd, max_sd;
	struct sockaddr_in address;
	int addrlen = sizeof(address);
	char buf[1024];
	fd_set readfds;
	char msg[] = "Message received\r\n";
	std::vector<int>	client_socket;
	std::vector<int>::iterator	it;

	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_family = AF_INET;
	address.sin_port = htons(4242);
	
	/*=====  mise en place du serveur  =====*/
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, (char *)&opt, sizeof(opt));
	bind(sockfd, (struct sockaddr*)&address, sizeof(address));
	listen(sockfd, 3);
	std::cout << "Waiting for connections..." << std::endl;
	/*=====  boucle pour gérer actions des clients*/
	while (1)
	{
		/*=====  nettoyer le fd_set  =====*/
		FD_ZERO(&readfds);
		/*=====  initialiser le fd_set  =====*/
		FD_SET(sockfd, &readfds);
		max_sd = sockfd;
		/*=====  innitialitier le nb de clients sur le serveur  =====*/
		for (it = client_socket.begin(); it != client_socket.end(); it++)
		{
			sd = *it;
			if (sd > 0)
				FD_SET(sd, &readfds);
			if (sd > max_sd)
				max_sd = sd;
		}
		select(max_sd + 1, &readfds, NULL, NULL, NULL);
		/*=====  vérifier que c'est une action vers le serveur  =====*/
		if (FD_ISSET(sockfd, &readfds))
		{	
			new_sock = accept(sockfd, (struct sockaddr*)&address, (socklen_t*)&addrlen);
			printf("New connection, socket is %d\n", new_sock);
			send(new_sock, msg, strlen(msg), 0);
			std::cout << "Message sent\n";
			/*=====  ajouter des clients (fd du client) au tableau  =====*/
			for (it = client_socket.begin(); it != client_socket.end(); it++)
			{
				if (*it == 0)
				{
					*it = new_sock;
					printf("Adding to list of sockets as %d\n" , i);
					break;
				}
			}
			if (it == client_socket.end())
				client_socket.push_back(new_sock);
		}
		/*=====  sinon l'action vient du client  =====*/
		for (it = client_socket.begin(); it != client_socket.end(); it++)
		{
			sd = *it;
			if (FD_ISSET(sd, &readfds))
			{
				if ((valread = read(sd, buf, 1024)) == 0)
				{
					printf("Host disconnected\n");
					close(sd);
					*it = 0;
				}
				else
				{
					buf[valread] = '\0';
					send(sd, buf, strlen(buf), 0);
				}
			}
		}
	}
}
