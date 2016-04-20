
#include <stdio.h>
#include <stdlib.h>

// #include "procs.c"
#include "procs.h"

#define DEBUG 0

// NOTES
// high response ratio represent high priority

int hppn(proc_t * procs,int numprocs)
{
  int i,time,sum_wait=0,sum_turnaround=0;
  int largest,arrival_time[numprocs],burst_time[numprocs],wait_time[numprocs],remain;
  double priority[numprocs];

  remain=numprocs;

  // initialize
  for(i=0;i<numprocs;i++)
  {
    arrival_time[i] = procs[i].arrival_time;
    burst_time[i] = procs[i].service_time;
    wait_time[i] = procs[i].wait_time;
    priority[i]= 0;
  }

  // if(DEBUG){
  //   printf("intialized arrays\n");
  //   printf("\n\nProcess\t|arrival_time|service_time|wait_time|turnaround_time\n");
  //   for(i=0;i<numprocs;i++){
  //     if(DEBUG){printf("P[%d]\t|\t%d\t|\t%d|\t%d\n",i,arrival_time[i],burst_time[i],wait_time[i]);}
  //   }
  // }

  if(DEBUG){printf("\n\nProcess\t|Turnaround time|waiting time|\n");}

  // begin sim
  for(time=0;remain!=0;)
  {
    largest=9;
    //redefine priorities
    for(i=0;i<numprocs;i++)
    {
      if(arrival_time[i]<=time && burst_time[i]>0)
      {
        priority[i]= (double)(((double) time-arrival_time[i]+ (double) burst_time[i])/ (double) burst_time[i]);
      }
      // printf("P[%d], priority: %f\n",i,priority[i] );
    }
    //determine which process is up next
    for(i=0;i<numprocs;i++)
    {
      if(arrival_time[i]<=time && priority[i]>priority[largest] && burst_time[i]>0)
      {
        largest=i;
      }
    }
    if(DEBUG){printf("--- Current = P[%d] --- time = %d ---\n", largest, time);}
    if(DEBUG){printf("process: P[%d] current time:|%d\n",largest,time);}
    //increment sim wait time
    time+=burst_time[largest];
    //decrement how many remain
    remain--;
    if(DEBUG){printf("P[%d]\t|\t%d\t|\t%d\t|\t%d\n",largest+1,time-arrival_time[largest],time-arrival_time[largest]-burst_time[largest], time);}
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
  printf("\n/*** HPPN ***/\n");
  printf("Avg waiting time = %f\n",sum_wait*1.0/numprocs);
  printf("Avg turnaround time = %f\n\n",sum_turnaround*1.0/numprocs);
  return 0;
}
