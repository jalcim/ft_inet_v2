#include "server.h"

//nb_elem
//size_block
//block

t_block *block_read_sock(int sock);

t_block **block_tab(int sock)
{
  t_block **block_tab;
  int nb_elem, i = -1;

  read(sock, &nb_elem, 4);
  printf("nb_elem = %d\n", nb_elem);
  block_tab = (t_block **)malloc(nb_elem * sizeof(t_block));
  while (++i < nb_elem)
    block_tab[i] = block_read_sock(sock);
  return (block_tab);
}

inline t_block *block_read_sock(int sock)
{
  t_block *block = (t_block *)malloc(sizeof(t_block));

  read(sock, &block->size[0], 4);
  printf("size = %d\n", block->size[0]);
  block->ops = (char *)malloc(block->size[0]);
  read(sock, block->ops, block->size[0]);
  printf("ops = %s\n", block->ops);

  read(sock, &block->size[1], 4);
  printf("size = %d\n", block->size[1]);
  block->lib = (char *)malloc(block->size[1]);
  read(sock, block->lib, block->size[1]);
  printf("lib = %s\n", block->lib);

  read(sock, &block->size[2], 4);
  printf("size = %d\n", block->size[2]);
  block->data = (char *)malloc(block->size[2]);
  read(sock, block->data, block->size[2]);
  printf("data = %s\n", block->data);
  return (block);
}
