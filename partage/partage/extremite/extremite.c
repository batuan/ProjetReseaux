#include "extremite.h"

char msg_buffer[BUFFER_SIZE];

int extremite(char *tun_name, char *host, char *port, int mode)
{
	int tun_fd, socket_fd, network_fd;
	int err;

	msg_start_func(__func__);

	// 1. allocation of tun interface @tun_name and get the fd describing it
	if((tun_fd = tun_alloc(tun_name)) < 0) {
		msg_end_func(__func__);
		return tun_fd;
	}
	sprintf(msg_buffer, "Connection to interface %s ok !\n", tun_name);
	msg_info(msg_buffer);

	if(mode == SERVER) {
		struct addrinfo *resol;
		struct addrinfo indic = {
			AI_PASSIVE, // every interface
			PF_INET6, SOCK_STREAM, 0, // tcp/IPv6
			0, NULL, NULL, NULL};
		int on; // /!\ used to make the port reusable fast
		
		// 2. resolve address
		if ((err = getaddrinfo(NULL, port, &indic, &resol)) < 0) {
			sprintf(msg_buffer, "Resolving address : %s\n", gai_strerror(err));
			msg_error(msg_buffer);
			msg_end_func(__func__);
			return err;
		}

		// 3. open TCP/IPv6 socket
		if((socket_fd = socket(resol->ai_family, resol->ai_socktype, resol->ai_protocol)) < 0) {
			msg_error("Socket's allocation\n");
			msg_end_func(__func__);
			return socket_fd;
		}
		sprintf(msg_buffer, "Socket's number : %d\n", socket_fd);
		msg_info(msg_buffer);

		// 4. make the port used by @socket_fd reusable fast
		on = 1;
		if((err = setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on))) < 0) {
			msg_error("Socket's option\n");
			msg_end_func(__func__);
			return err;
		}
		msg_info("Socket's options OK !\n");

		// 5. associate socket @socket_fd to the address resolved
		if ((err = bind(socket_fd, resol->ai_addr, sizeof(struct sockaddr_in6))) < 0) {
			msg_error("Bind\n");
			msg_end_func(__func__);
			return err;
		}
		freeaddrinfo(resol); // /!\ free memory
		msg_info("Bind OK !\n");

		// 6. makes the socket @socket_fd ready to accept connections 
		if ((err = listen(socket_fd, SOMAXCONN)) < 0) {
			msg_error("Listen\n");
			msg_end_func(__func__);
			return err;
		}
		msg_info("Listen OK !\n");

		// 7. wait for connection request
		msg_info("Waiting for connection...\n");
		struct sockaddr_in6 client;
		socklen_t len = sizeof(struct sockaddr_in6);
		char host_client[NI_MAXHOST]; 
		char port_client[NI_MAXSERV];
		if((network_fd = accept(socket_fd, (struct sockaddr*)&client, &len)) < 0) {
			msg_error("Accept\n");
			msg_end_func(__func__);
			return err;
		}

		// 8. resolve client connection
		if((err = getnameinfo((struct sockaddr*)&client, len, host_client, NI_MAXHOST, port_client, NI_MAXSERV, 0)) < 0) {
			msg_error("Resolve client connection\n");
			msg_end_func(__func__);
			return err;
		}
		sprintf(msg_buffer, "Accepted client from %s on port %s\n", host_client, port_client);
		msg_info(msg_buffer);
	} else {
		// TODO :: client
		char ip[NI_MAXHOST];
		char *addr_ipv6;
		struct addrinfo *resol_client;

		// 2. resolve address
		if ((err = getaddrinfo(host, port, NULL, &resol_client)) < 0) {
			sprintf(msg_buffer, "Resolving address : %s\n", gai_strerror(err));
			msg_error(msg_buffer);
			msg_end_func(__func__);
			return err;
		}

		// 3. extract ip address
		addr_ipv6 = malloc(150);
		inet_ntop(PF_INET6, &(((struct sockaddr_in6*)resol_client->ai_addr)->sin6_addr), addr_ipv6, 100);
		sprintf(ip, "%s", addr_ipv6);
		free(addr_ipv6);

		// 4. open TCP/IPv6 socket
		if((socket_fd = socket(resol_client->ai_family, resol_client->ai_socktype, resol_client->ai_protocol)) < 0) {
			msg_error("Socket's allocation\n");
			msg_end_func(__func__);
			return socket_fd;
		}
		sprintf(msg_buffer, "Socket's number : %d\n", socket_fd);
		msg_info(msg_buffer);

		// 5. connection to the host:port speficied
		if((err = connect(socket_fd, resol_client->ai_addr, sizeof(struct sockaddr_in6))) < 0) {
			msg_error("Connection\n");
			msg_end_func(__func__);
			return err;
		}
		freeaddrinfo(resol_client); // /!\ free memory
		sprintf(msg_buffer, "Connected to host = %s | ip = %s | port = %s\n", host, ip, port);
		msg_info(msg_buffer);

		network_fd = socket_fd; //TODO
	}

	// x. handling two file descriptors at once using select
	int max_fd = network_fd > tun_fd ? network_fd : tun_fd;
	fd_set read_set;
	int rv;
	while(1) {
		FD_ZERO(&read_set);
		FD_SET(network_fd, &read_set);
		FD_SET(tun_fd, &read_set);

		rv = select(max_fd + 1, &read_set, NULL, NULL, NULL);
		/*
		if(rv < 0 && errno == EINTR) {
			continue;
		}
		*/
		if(rv < 0) {
			msg_error("Select\n");
			msg_end_func(__func__);
			return rv;
		}

		// we have data from tun interface : read it and write it back to the network
		if(FD_ISSET(tun_fd, &read_set)) {
			if(src_to_dst(tun_fd, network_fd) < 0) {
				msg_end_func(__func__);
				exit(EXIT_FAILURE);
			}
		}
		
		// we have data from the network : read it and write it to the tun interface
		if(FD_ISSET(network_fd, &read_set)) {
			if(src_to_dst(network_fd, tun_fd) < 0) {
				msg_end_func(__func__);
				exit(EXIT_FAILURE);
			}
		}
	}

	msg_end_func(__func__);
	return EXIT_SUCCESS;
}