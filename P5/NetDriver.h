#ifndef NETDRIVER_H
  #define NETDRIVER_H

struct Computer
{
  char address[16];
};

struct Edge
{
  char src[16];
  char dest[16];
  short capacity;
};

#endif