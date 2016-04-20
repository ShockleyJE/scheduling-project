#ifndef PROCS_H
#define PROCS_H

typedef struct hppn_proc_struct
{
 char name;
 int arrival_time,burst_time,wait_time,turnaround_time;
 int completed;
} hppn_procs_t;

#endif /* PROCS_H */
