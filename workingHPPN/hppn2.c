
#include <stdio.h>
#include <stdlib.h>

#include "procs.c"
#include "procs.h"

struct processes
{
 char name;
 int arrival_time,burst_time,ct,wait_time,tt;
 int completed;
 float ntt;
} process[10];

int n;

void sortByArrival()
{
  struct process temp;
  int i,j;
  for(i=0;i<n-1;i++)
  for(j=i+1;j<n;j++)
  {
    if(process[i].arrival_time>process[j].arrival_time)
    {
      temp=process[i];
      process[i]=process[j];
      process[j]=temp;
     }
   }
}
void hppn2(proc_t * procs,int numprocs)
{
 int i,j,time,sum_burst_time=0;
 char c;
 float avgwt=0;
 for(i=0,c='A';i<numprocs;i++,c++){
   process[i].name=c;
   process[i].arrival_time = procs[i].arrival_time;
   process[i].burst_time = procs[i].service_time;
   process[i].completed=0;
   sum_burst_time+=process[i].burst_time;
  }

sortByArrival();

printf("\nName\tArrival Time\tBurst Time\tWaiting Time\tTurnAround Time\t Normalized TT");
  for(time=process[0].arrival_time;time<sum_burst_time;){
   float hrr=-9999;
   int loc;
   for(i=0;i<n;i++){
     if(process[i].arrival_time<=time && process[i].completed!=1){
      float temp=(process[i].burst_time + (time-process[i].arrival_time))/process[i].burst_time;
      if(hrr < temp){
        hrr=temp;
        loc=i;
       }
     }
   }
   time+=process[loc].burst_time;
   process[loc].wait_time=time-process[loc].arrival_time-process[loc].burst_time;
   process[loc].tt=time-process[loc].arrival_time;
   process[loc].ntt=((float)process[loc].tt/process[loc].burst_time);
   process[loc].completed=1;
   avgwt+=process[loc].wait_time;
   printf("\n%c\t\t%d\t\t%d\t\t%d\t\t%d\t\t%f",process[loc].name,process[loc].arrival_time,process[loc].burst_time,process[loc].wait_time,process[loc].tt,process[loc].ntt);
  }
  printf("\nAverage waiting time:%f\n",avgwt/n);
}
