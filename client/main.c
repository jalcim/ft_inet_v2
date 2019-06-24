#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>


typedef struct sockaddr_in t_sockaddr_in;
typedef struct sockaddr t_sockaddr;

int main(int argc, char **argv)
{
  t_sockaddr_in sin;
  int sock;

  if ((sock = socket(PF_INET, SOCK_STREAM, 0)) == -1)
    perror("socket -> ");
  
  if (!(sin.sin_addr.s_addr = inet_addr("127.0.0.1")))
    perror("inet error ->");
  sin.sin_family = PF_INET;
  sin.sin_port = htons(atoi(argv[1]));			  
  if ((connect(sock, (t_sockaddr*)&sin, sizeof(t_sockaddr))))
    perror("connect -> ");
  write(sock, "bonjour\n\r", 9);
}
