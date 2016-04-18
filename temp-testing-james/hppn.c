
#include <stdio.h>
#include <stdlib.h>

#include "procs.c"
#include "hppn.h"

#define DEBUG = 1;

int main(proc_t * procs, numprocs)
{
  int time,burst_time[10],arrival_time[10],sum_burst_time=0,smallest,numprocs,i;
  int sum_turnaround=0,sum_wait=0;

  //set arrival times and burst (service) times
  for(i=0;i<numprocs;i++)
  {
    burst_time[i]= procs[i].service_time;
    // burst_time[i]= procs[i]->service_time;

    arrival_time[i]= procs[i].arrival_time;
    // arrival_time[i]= procs[i]->arrival_time;

    sum_burst_time+=burst_time[i];
  }
  burst_time[9]=9999;

  if(DEBUG==1){printf("\n\nProcess\t|Turnaround Time| Waiting Time\n\n");}

  for(time=0; time < sum_burst_time;)
  {
    smallest=9;
    // find which has lowest response ratio
    for(i=0;i<numprocs;i++)
    {
      if(arrival_time[i]<=time && burst_time[i]>0 && burst_time[i]<burst_time[smallest])
        smallest=i;
    }
    if(smallest==9)
    {
      time++;
      continue;
    }
    if(DEBUG==1){printf("P[%d]\t|\t%d\t|\t%d\n",smallest+1,time+burst_time[smallest]-arrival_time[smallest],time-arrival_time[smallest]);}
    sum_turnaround+=time+burst_time[smallest]-arrival_time[smallest];
    sum_wait+=time-arrival_time[smallest];
    time+=burst_time[smallest];
    burst_time[smallest]=0;
  }
  printf("\n\numprocs average waiting time = %f",sum_wait*1.0/numprocs);
  printf("\n\numprocs average turnaround time = %f",sum_turnaround*1.0/numprocs);
  return 0;
}
