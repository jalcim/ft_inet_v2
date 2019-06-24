#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

typedef void (*m_cmd_tab_t)(char *);

void t_read(char *buffer);
void t_write(char *buffer);
void t_null(char *buffer);

unsigned int size;
unsigned int cpt;

int main()
{
  int fd = open("input", O_RDWR);
  char *buffer;
  char *cmd_tab[3];
  m_cmd_tab_t m_cmd_tab[3];

  cmd_tab[0] = strdup("rd");
  cmd_tab[1] = strdup("wr");
  cmd_tab[2] = NULL;

  m_cmd_tab[0] = t_read;
  m_cmd_tab[1] = t_write;
  m_cmd_tab[2] = t_null;
  
  read(fd, &size, 4);
  buffer = (char *)malloc(size);
  read(fd, buffer, size);

  cpt = -1;
  while (cmd_tab[++cpt] && strncmp(buffer, cmd_tab[cpt], 2));
  (*m_cmd_tab[cpt])(buffer);

  free(cmd_tab[0]);
  free(cmd_tab[1]);
}

void t_read(char *buffer)
{
  printf("read\n");
}

void t_write(char *buffer)
{
  printf("write\n");
}

void t_null(char *buffer)
{
  printf("null\n");
}
