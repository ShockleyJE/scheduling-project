
#include <stdio.h>
#include <stdlib.h>

#include "helpers.c"
#include "procs.c"


int hppn(proc_t *procs, int numprocs)
{

  struct node * front = NULL; /* will be the pointer to my linked list */
  struct node * last = NULL; /* for upkeep */
  struct node * curr = NULL /* currntly running process */

  int clock= 0;
  int sum_turnaround_time = 0;
  int sum_wait_time = 0;

  int list_size= numprocs;
  int i= 0;

  // Initializes process list
  for(i = 0; i < list_size -1; i++){
    front= createProcessNode(procs[i], * front, i);
    if(i== 0){
      last= front;
    }
  }

  while(list_size > 0){
    // get next node with highest response ratio
    curr= getNextProcess(first);
    // update simclock for current process, simulating one timeslice each rep
    for(int i= 0; i< curr->service_time; i++){
        clock++;
    }
    //update running sums
    sum_turnaround_time += (curr->wait_time + curr->service_time);
    total_wait_time += curr->wait_time;
    // upkeep
    removeNode(curr, front);
    updateWaitTimes(front);
    list_size--;
  }
  //calculate average times
  int avg_wait_time = averageWaitTime(total_waiting_time, numprocs);
  int avg_turnaround_time = averageTurnaroundTime(sum_turnaround_time, numprocs);

  // TODO: format
  printf("HRRN\n");
  printf("average turnaround time: %d\n", avg_turnaround_time );
  printf("average wait time: %d\n", avg_wait_time );


  return 0;
}
