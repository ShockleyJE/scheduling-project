#include<stdio.h>
#include <stdlib.h>  /* for malloc() */

#include "hppn.h"
#include "procs.h"

#define DEBUG 0

 /*
  * sort array of process structs by arrival_time
  * requires
  */
void sortByArrival(hppn_procs_t *p,int n){
  hppn_procs_t temp;
  int i,j;
  for(i=0;i<n-1;i++){
    for(j=i+1;j<n;j++){
      if(p[i].arrival_time>p[j].arrival_time){
        temp=p[i];
        p[i]=p[j];
        p[j]=temp;
       }
     }
   }
}

void hppn(proc_t * procs, int numprocs)
{
 int i,time,sum_burst_time=0,avg_turnaround_time=0,c;
 float avg_wait_time=0;

 hppn_procs_t *p;
 p = malloc(numprocs * sizeof(hppn_procs_t));

 for(i=0,c=1;i<numprocs;i++,c++){
   p[i].arrival_time = procs[i].arrival_time;
   p[i].burst_time = procs[i].service_time;
   p[i].wait_time = procs[i].wait_time;
   p[i].name = c;
   p[i].completed = 0;
   sum_burst_time+=p[i].burst_time;
 }

 sortByArrival(p, numprocs);

 if(DEBUG){printf("\nName\tArrival Time\tBurst Time\tWaiting Time\tTurnAround Time");}
  for(time=p[0].arrival_time;time<sum_burst_time;){
    //initialize hrr to something we should never get
    float hrr=-9999;
    //initialize location var
    int loc;
    //for each, find uncompleted processes that have arrived already
    //then, find the one with the highest response ratio
    for(i=0;i<numprocs;i++){
     if(p[i].arrival_time<=time && p[i].completed!=1){
      float temp=(float)(p[i].burst_time + (time-p[i].arrival_time))/(float) p[i].burst_time;
      if(hrr < temp){
        hrr=temp;
        loc=i;
      }
     }
    }
    //simulated process completion upkeep
    time+=p[loc].burst_time;
    p[loc].wait_time=time-p[loc].arrival_time-p[loc].burst_time;
    p[loc].turnaround_time=time-p[loc].arrival_time;
    p[loc].completed=1;
    avg_wait_time+=p[loc].wait_time;
    avg_turnaround_time+=p[loc].turnaround_time;
    if(DEBUG){printf("\n%d\t\t%d\t\t%d\t\t%d\t\t%d\t",p[loc].name,p[loc].arrival_time,p[loc].burst_time,p[loc].wait_time,p[loc].turnaround_time);}
  }
  printf("\n---------------------------------------------------\n");
  printf("Highest Priority Process Next\n" );
  printf("\tAverage waiting time:\t\t%f\n",avg_wait_time/numprocs);
  printf("\tAverage turnaround time:\t%f\n",avg_turnaround_time*1.0/numprocs);
  printf("---------------------------------------------------\n");

  free(p);
}
