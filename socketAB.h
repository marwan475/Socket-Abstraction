#ifndef SOCKETAB_H
#define SOCKETAB_H

int INIT_Sockets();
int CLOSE_Socket(int socket);
int CLEANUP_Sockets();

int UDP_Socket();
int UDP_Sendto(int destport, char* destip);
int UDP_Bind(int port, char* interface);
int UDP_Recvfrom(int socket, char* buff, int buffsize);

#endif
