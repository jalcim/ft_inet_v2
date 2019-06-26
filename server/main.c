#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <poll.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "server.h"

t_block **block_tab(int sock);

class_server_t *init_object_server(int port)
{
  class_server_t *o_server;

  o_server = (class_server_t *)malloc(sizeof(class_server_t));
  o_server->port = port;
  o_server->m_fct[0] = ft_sock;
  o_server->m_fct[1] = ft_wait_sock;
  o_server->m_fct[2] = ft_accept;
  return (o_server);
}

int main(int argc, char **argv)
{
  class_server_t *o_server;

  if (argc != 2)
    return (-1);
  o_server = init_server(atoi(argv[1]));

  ft_wait_sock(o_server);

  block_tab(o_server->sock);

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
}

void ft_accept(class_server_t *o_server)
{
  if (listen(o_server->event.fd, 1) == -1)
    perror("listen -> ");
  o_server->size = sizeof(t_sockaddr);
  o_server->sock = accept(o_server->event.fd, (t_sockaddr *)&o_server->info, &o_server->size);
  if (o_server->sock == -1)
    perror("accept -> ");
}

inline void server_run(class_server_t *o_server)
{
  (*o_server->m_fct[0])(o_server);
  (*o_server->m_fct[1])(o_server);
  (*o_server->m_fct[2])(o_server);
}

inline class_server_t *init_server(int port)
{
  class_server_t *o_server;

  o_server = init_object_server(port);
  server_run(o_server);
  return (o_server);
}
