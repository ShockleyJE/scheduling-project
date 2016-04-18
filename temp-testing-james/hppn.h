#ifndef HPPN_H
#define HPPN_H

#include "helpers.h"
#include "procs.h"

/* prototype definition for node */
typedef struct nodes {
  double arrival_time;
  double service_time;
  double wait_time;
  double end_time;
  int id;
} node;

#endif /* HPPN_H */
