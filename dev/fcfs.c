//for now
#include helpers-temp.c

int clock;                 // counter for time simulation
int sum_turnaround_time;   // sum of turnaround times used for average

void fcfs(proc_t *process, int numprocs, )
{

  /* =========================================================================
   * Logic
   * =========================================================================
   */
   // while(number_procs){
   //   -add new incoming procs to to be added to ready queue
   //   -if a process has finished, move them from the waiting queue
   //       -set end time to current sim time

  // calculations
	for(i = 0; i < numberOfProcesses; i++){
    //TODO: decide where to store/ how to keep up with end_time for each
		sum_turnaround_time += procs[i].end_time - procs[i].arrival_time;
		total_waiting_time += procs[i].service_time;
	}
  //TODO: change from doubles to ints after sim time and not clock time is written
	double avg_wait_time = averageWaitTime(total_waiting_time);
	double avg_turnaround_time = averageTurnaroundTime(sum_turnaround_time);
}
