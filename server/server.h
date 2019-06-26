#ifndef __SERVER_H_
#define __SERVER_H__

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

class_server_t *init_object_server(int port);
void server_run(class_server_t *o_server);

class_server_t *init_server(int port);

/////////////////////////////////////

typedef struct s_block t_block;

struct s_block
{
  unsigned int size[3];
  char *ops, *lib, *data;
};



#endif
