#ifndef HPPN_H
#define HPPN_H

#include "procs.h"

typedef struct hppn_proc_struct
{
 int name;
 int arrival_time,burst_time,wait_time,turnaround_time;
 int completed;
} hppn_procs_t;

#endif /* HPPN_H */
