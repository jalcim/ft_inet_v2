#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <poll.h>
#include <unistd.h>
#include <stdlib.h>

#include <stdio.h>

typedef struct sockaddr_in t_sockaddr_in;
typedef struct pollfd t_pollfd;
typedef struct sockaddr t_sockaddr;

typedef struct class_server_s class_server_t;
typedef void (*method) (class_server_t *);
struct class_server_s
{
  unsigned short int port;
  int sock;
  t_pollfd event;
  t_sockaddr_in server;  
  t_sockaddr_in info;
  socklen_t size;
  
  method m_fct[3];
};

void ft_sock(class_server_t *o_server);
void ft_wait_sock(class_server_t *o_server);
void ft_accept(class_server_t *o_server);

class_server_t *init_object_server(char *port);
class_server_t *init_object_server(char *port)
{
  class_server_t *o_server;

  o_server = (class_server_t *)malloc(sizeof(class_server_t));
  o_server->port = atoi(port);
  o_server->m_fct[0] = ft_sock;
  o_server->m_fct[1] = ft_wait_sock;
  o_server->m_fct[2] = ft_accept;
  return (o_server);
}

int main(int argc, char **argv)
{
  class_server_t *o_server;
  char c;
  char b;

  if (argc != 2)
    return (-1);
  o_server = init_object_server(argv[1]);

  c = -1;
  while(++c < 3)
    (*o_server->m_fct[c])(o_server);
  while(1)
    {
      read(o_server->sock, &c, 1);
      write(1, &c, 1);
      if (b == '\n' && c == '\r')
	break;
      b = c;
    }
  close(o_server->sock);
  free(o_server);
}

void ft_sock(class_server_t *o_server)
{
  if ((o_server->sock = socket(PF_INET, SOCK_STREAM, 0)) == -1)
    perror("socket");
  o_server->server.sin_family = PF_INET;
  o_server->server.sin_port = htons(o_server->port);
  if ((bind(o_server->sock, (t_sockaddr *)&o_server->server,
	    sizeof(t_sockaddr))) == -1)
    perror("bind");
}

void ft_wait_sock(class_server_t *o_server)
{
  o_server->event.fd = o_server->sock;
  o_server->event.events = POLLIN;
  if ((poll(&o_server->event, sizeof(t_pollfd), 1)) == -1)
    perror("poll -> ");
  if (listen(o_server->event.fd, 1) == -1)
    perror("listen -> ");
}

void ft_accept(class_server_t *o_server)
{
  o_server->size = sizeof(t_sockaddr);
  o_server->sock = accept(o_server->event.fd, (t_sockaddr *)&o_server->info, &o_server->size);
  if (o_server->sock == -1)
    perror("accept -> ");
}
