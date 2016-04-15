/*
 * Just a placeholder for now.
 *
 */

void spn(proc_t *process, int numprocs, )
{
  // clear globals
  resetGlobals();

  /* =========================================================================
   * Logic
   * =========================================================================
   */
   // while(number_procs){
   //   -add new incoming procs to to be added to ready queue
   //   -if a process has finished, move them from the waiting queue
   //       -set end time to current sim time
   //   -perform maintainance on ready queue to make sure shortest is next
   //       -compareServiceTime in helpers-temp

  // calculations
  for(i = 0; i < numberOfProcesses; i++){
    //TODO: figure out where to store/ how to keep up with end_time for each
    sum_turnaround_time += procs[i].end_time - procs[i].arrival_time;
    total_waiting_time += procs[i].service_time;
  }
  //TODO: change from doubles to ints after sim time and not clock time is written
  double avg_wait_time = averageWaitTime(total_waiting_time);
  double avg_turnaround_time = averageTurnaroundTime(sum_turnaround_time);
}
