
#include <stdio.h>
#include <stdlib.h>

#include "procs.c"
#include "hppn.h"

#define DEBUG = 1;

// NOTES
// high response ratio represent high priority

int main(proc_t * procs, numprocs)
{
  int i,j,time,sum_wait=0,sum_turnaround=0;
  int largest,arrival_time[10],burst_time[10],priority[10],remain;

  remain=numprocs;

  // initialize
  for(i=0;i<numprocs;i++)
  {
    arrival_time[i] = procs[i]->arrival_time;
    burst_time[i] = procs[i]->service_time;
    wait_time[i] = procs[i]->wait_time;
    priority[i]= 0;
  }

  if(DEBUG){printf("\n\nProcess\t|Turnaround time|waiting time\n");}

  // begin sim
  for(time=0;remain!=0;)
  {
    largest=9;
    //redefine priorities
    for(i=0;i<numprocs;i++)
    {
      if(arrival_time[i]<=time && burst_time[i]>0)
      {
        priority[i]= ((wait_time[i]+service_time[i])/service_time[i]);
      }
    }
    //determine which process is up next
    for(i=0;i<numprocs;i++)
    {
      if(arrival_time[i]<=time && priority[i]>priority[largest] && burst_time[i]>0)
      {
        largest=i;
      }
    }
    // increment sim wait time
    time+=burst_time[largest];
    //decrement how many remain
    remain--;
    if(DEBUG){printf("P[%d]\t|\t%d\t|\t%d\n",largest+1,time-arrival_time[largest],time-arrival_time[largest]-burst_time[largest]);}
    // running totals
    sum_wait+=time-arrival_time[largest]-burst_time[largest];
    sum_turnaround+=time-arrival_time[largest];

    //increment wait times
    for(i=0;i<numprocs;i++)
    {
      if(arrival_time[i]<=time && burst_time[i]>0)
      {
        wait_time[i] += burst_time[largest];
      }
    }

    burst_time[largest]=0;
  }
  printf("\nAvg waiting time = %f\n",sum_wait*1.0/numprocs);
  printf("Avg turnaround time = %f",sum_turnaround*1.0/numprocs);
  return 0;
}
