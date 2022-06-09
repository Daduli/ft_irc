	#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/select.h>
#include <unistd.h>
#include <iostream>
#include <string>


int main(int ac, char **av)
{
	int opt = 1;
	int sockfd, new_sock, client_socket[30], max_clients = 30, activity, i, valread, sd, max_sd;
	struct sockaddr_in address;
	int addrlen = sizeof(address);
	char buf[1024];
	fd_set readfds;
	char msg[] = "Message received\r\n";

	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_family = AF_INET;
	address.sin_port = htons(4242);
	
	//std::string test = "Hello!\n";

	/*=====  initialisation du tableau de clients  =====*/
	for (int i = 0; i < max_clients; i++)
	{
		client_socket[i] = 0;
	}
	/*=====  mise en place du serveur  =====*/
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	//if (setsockopt(serv->sfd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0)
	//	exit_error("Setsockopt Error");

	if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(int)) < 0)
		exit(1);
	bind(sockfd, (struct sockaddr*)&address, sizeof(address));
	std::cout << "Waiting for connections..." << std::endl;
	listen(sockfd, 0);
	/*=====  boucle pour gérer actions des clients  ======*/
	while (1)
	{
		/*=====  nettoyer le fd_set  =====*/
		FD_ZERO(&readfds);
		/*=====  initialiser le fd_set  =====*/
		FD_SET(sockfd, &readfds);
		max_sd = sockfd;
		/*=====  innitialitier le nb de clients sur le serveur  =====*/
		for (int i = 0; i < max_clients; i++)
		{
			sd = client_socket[i];
			if (sd > 0)
			{
				FD_SET(sd, &readfds);
				std::cout << sd << std::endl;
			}
			if (sd > max_sd)
				max_sd = sd;
		}
		std::cout << max_sd << std::endl;
		select(max_sd + 1, &readfds, NULL, NULL, NULL);
		std::cout << "here\n";
		/*=====  vérifier que c'est une action vers le serveur  =====*/
		if (FD_ISSET(sockfd, &readfds))
		{	
			new_sock = accept(sockfd, (struct sockaddr*)&address, (socklen_t*)&addrlen);
			printf("New connection, socket is %d\n", new_sock);
			send(new_sock, msg, strlen(msg), 0);
			std::cout << "Message sent\n";
			//read(new_sock, buf, 1024);
			//std::cout << buf << std::endl;
			/*=====  ajouter des clients (fd du client) au tableau  =====*/
			for (int i = 0; i < max_clients; i++)
			{
				if (client_socket[i] == 0)
				{
					client_socket[i] = new_sock;
					printf("Adding to list of sockets as %d\n" , i);
					break;
				}
			}
		}
		/*=====  sinon l'action vient du client  =====*/
		for (int i = 0; i < max_clients; i++)
		{
			sd = client_socket[i];
			if (FD_ISSET(sd, &readfds))
			{
				if ((valread = read(sd, buf, 1024)) == 0)
				{
					printf("Host disconnected\n");
					close(sd);
					client_socket[i] = 0;
				}
				else
				{
					//buf = 0;
					//recv(sd, buf, 1024, 0);
					std::cout << buf << std::endl;
					//std::cout << "here\n";
				}
			}
		}
	}
}