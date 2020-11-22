#include "extremite.h"

/** 
et redirige les données reçues sur la sortie standard.
ref: https://man7.org/linux/man-pages/man3/getaddrinfo.3.html#top_of_page
**/
int extout(char* host, int port) {
  //Crée un serveur écoutant sur le port 123
  port = DEFAULTPORT;
  int socket_listen, n; /* descripteurs de socket */
  int len,on; /* utilitaires divers */
  struct addrinfo * resol; /* résolution */
  struct addrinfo indic = {AI_PASSIVE, /* Toute interface */
                           AF_INET6,SOCK_STREAM,0, /* IP mode connecté IPv6 */
                           0,NULL,NULL,NULL};
  struct sockaddr_in client; /* adresse de socket du client */
  int err; /* code d'erreur */
  
  printf("Usage: %d port\n", port);
  err = getaddrinfo(NULL, "123", &indic, &resol); 
  if (err<0){
    fprintf(stderr,"Résolution: %s\n",gai_strerror(err));
    exit(2);
  }

  /* Création de la socket, de type TCP / IP */
  if ((socket_listen=socket(resol->ai_family,resol->ai_socktype,resol->ai_protocol))<0) {
    perror("allocation de socket");
    exit(3);
  }
  
  fprintf(stderr,"le n° de la socket est : %i\n",socket_listen);

  /* On rend le port réutilisable rapidement /!\ */
  on = 1;
  if (setsockopt(socket_listen,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on))<0) {
    perror("option socket");
    exit(4);
  }
  fprintf(stderr,"Option(s) OK!\n");
   printf("Binding socket to local address...\n");

  /* Association de la socket s à l'adresse obtenue par résolution */
  if (bind(socket_listen, resol->ai_addr, sizeof(struct sockaddr_in6))<0) {
    perror("bind");
    exit(5);
  }
  freeaddrinfo(resol); /* /!\ Libération mémoire */
  fprintf(stderr,"bind!\n");

  /* la socket est prête à recevoir */
  if (listen(socket_listen, SOMAXCONN)<0) {
    perror("listen");
    exit(6);
  }
  printf("Waiting for connection...\n");
  fprintf(stderr,"listen!\n");

  while (1)
  {
    struct sockaddr_storage client_address;
    socklen_t client_len = sizeof(client_address);
    int socket_client = accept(socket_listen,
            (struct sockaddr*) &client_address, &client_len);
    if (socket_client < 0) {
        fprintf(stderr, "accept() failed. (%d)\n", 3);
        return 1;
    }

    printf("client is connected");
    char address_buffer[100];
    char portc[NI_MAXSERV];
    getnameinfo((struct sockaddr*)&client_address, client_len, 
    address_buffer, sizeof(address_buffer), portc, NI_MAXSERV, NI_NUMERICHOST);
    printf("%s\n", address_buffer);

    printf("Reading request...\n");
    char request[1024];
    int bytes_received = recv(socket_client, request, 1024, 0);

    //redirige les données reçues sur la sortie standard.
    write(1, request, bytes_received);
  }
}

int ext_int(char* arg1, char* arg2) {
  // if (argc < 3) {
  // fprintf(stderr, "usage: tcp_client hostname port\n");
  // return 1;
  // }

  printf("Configuring remote address...\n");
  struct addrinfo hints;
  memset(&hints, 0, sizeof(hints));
  hints.ai_socktype = SOCK_STREAM;
  struct addrinfo *peer_address;
  if (getaddrinfo(arg1, arg2, &hints, &peer_address)) {
      fprintf(stderr, "getaddrinfo() failed. (%d)\n", 3);
      return 1;
  }

  printf("Remote address is: ");
  char address_buffer[100];
  char service_buffer[100];
  getnameinfo(peer_address->ai_addr, peer_address->ai_addrlen,
            address_buffer, sizeof(address_buffer),
            service_buffer, sizeof(service_buffer),
            NI_NUMERICHOST);
  printf("%s %s\n", address_buffer, service_buffer);

  printf("Creating socket...\n");
  int socket_peer;
  socket_peer = socket(peer_address->ai_family,
            peer_address->ai_socktype, peer_address->ai_protocol);

  if (socket_peer < 0) {
    fprintf(stderr, "socket() failed. (%d)\n", 3);
    return 1;
  }

  fprintf(stderr,"le n° de la socket est : %i\n",socket_peer);

  printf("Connecting...\n");
  if (connect(socket_peer, peer_address->ai_addr, peer_address->ai_addrlen) < 0) {
    fprintf(stderr, "connect() failed. (%d)\n", 3);
    return 1;
  }
  freeaddrinfo(peer_address);
  printf("Connected.\n");
  printf("To send data, enter text followed by enter.\n");

  while(1) {
        fd_set reads;
        FD_ZERO(&reads);
        FD_SET(socket_peer, &reads);
        struct timeval timeout;
        timeout.tv_sec = 0;
        timeout.tv_usec = 100000;

        if (select(socket_peer+1, &reads, 0, 0, &timeout) < 0) {
            fprintf(stderr, "select() failed. (%d)\n", 3);
            return 1;
        }

        if (FD_ISSET(socket_peer, &reads)) {
            char read[4096];
            int bytes_received = recv(socket_peer, read, 4096, 0);
            if (bytes_received < 1) {
                printf("Connection closed by peer.\n");
                break;
            }
            printf("Received (%d bytes): %.*s",
                    bytes_received, bytes_received, read);
        }

        if(FD_ISSET(0, &reads)) {
            char read[4096];
            if (!fgets(read, 4096, stdin)) break;
            printf("Sending: %s", read);
            int bytes_sent = send(socket_peer, read, strlen(read), 0);
            printf("Sent %d bytes.\n", bytes_sent);
        }
    }

    printf("Closing socket...\n");
    close(socket_peer);
    printf("Finished.\n");
    return 0;
}