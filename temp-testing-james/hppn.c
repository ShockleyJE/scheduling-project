
#include <stdio.h>
#include <stdlib.h>

#include "procs.c"
#include "hppn.h"

#define DEBUG = 1;

int main(proc_t * procs, numprocs)
{
  int i,j,time,sum_wait=0,sum_turnaround=0;
  int smallest,arrival_time[10],burst_time[10],priority[10],remain;

  remain=numprocs;

  for(i=0;i<numprocs;i++)
  {
    arrival_time[i] = procs[i]->arrival_time;
    burst_time[i] = procs[i]->service_time;
    priority[i]= 0;
  }
  if(DEBUG){printf("\n\nProcess\t|Turnaround time|waiting time\n");}
  for(time=0;remain!=0;)
  {
    smallest=9;
    for(i=0;i<numprocs;i++)
    {
      if(arrival_time[i]<=time && priority[i]<priority[smallest] && burst_time[i]>0)
      {
        smallest=i;
      }
    }
    time+=burst_time[smallest];
    remain--;
    if(DEBUG){printf("P[%d]\t|\t%d\t|\t%d\n",smallest+1,time-arrival_time[smallest],time-arrival_time[smallest]-burst_time[smallest]);}
    sum_wait+=time-arrival_time[smallest]-burst_time[smallest];
    sum_turnaround+=time-arrival_time[smallest];
    burst_time[smallest]=0;
  }
  printf("\nAvg waiting time = %f\n",sum_wait*1.0/numprocs);
  printf("Avg turnaround time = %f",sum_turnaround*1.0/numprocs);
  return 0;
}
