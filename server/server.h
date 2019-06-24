#ifndef __SERVER_H_
#define __SERVER_H__
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
#endif
