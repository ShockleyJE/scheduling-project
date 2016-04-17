#ifndef HPPN_H
#define HPPN_H

#include "helpers.h"

/* prototype definition for node */
typedef struct node {
  double arrival_time;
  double service_time;
  double wait_time;
  double end_time;
  struct node * next;
} node;

int hppn(proc_t *, int );

#endif /* HPPN_H */
