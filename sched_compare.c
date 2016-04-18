#include <stdio.h>   // for printf()
#include <stdlib.h>  // for atoi()

#include "procs.h"
#include "procheap.h"

//gcc -o pro sched_compare.c procs.c procheap.c poisson.c -lm

// DO NOT CHANGE THESE TWO CONSTANTS !
#define INTER_ARRIVAL_TIME 3   // mean poisson dist
#define SERVICE_TIME       5   // mean poisson dist

int sjf(int len, int services[], int arrive[], int waiting[], int turnaround[], int finish[], double avgs[]);
int fcfs(int len, int services[], int arrive[], int waiting[], int turnaround[], int finish[], double avgs[]);
int hppn(proc_t * procs,int numprocs);


int main(int argc, char** argv)
{
  int numprocs, seed;
  proc_t *procs;   // array of procs with service time and arrival time

  if (argc < 3) {
    fprintf(stderr, "USAGE: %s numprocs seed\n", argv[0]);
    return 1;
  }

  numprocs = atoi(argv[1]);
  seed = atoi(argv[2]);

  // create an array of numprocs randomly generate (arrival time, service time)
 procs = procs_random_create(numprocs, seed, INTER_ARRIVAL_TIME, SERVICE_TIME);
  
  // Uncomment the next block of code and comment the line above if
  // you want to read the input from a file instead of generating
  // random values. This can be useful for debugging your code with
  // known inputs.  The file, "book_example.txt", contains an example
  // from the book.

  
  /*if ((procs = procs_read("book_example.txt", &numprocs)) == NULL) {
    fprintf(stderr, "Error reading procs array\n");
    return 2;
  }*/
  

  //printf("procs array:\n");
  //printf("(arrival time, service time)\n");
  //procs_print(procs, numprocs);
  
  //shortest process next (or shortest job first algorithm)
  int i = 0;
  int *arrivalTimes;
  arrivalTimes = malloc(numprocs * sizeof(int));
  int *serviceTimes;
  serviceTimes = malloc(numprocs * sizeof(int));
  
   int *waitingTimes;
  waitingTimes = malloc(numprocs * sizeof(int));
   int *turnaroundTimes;
  turnaroundTimes = malloc(numprocs * sizeof(int));
   int *finishTimes;
  finishTimes = malloc(numprocs * sizeof(int));
  for (i = 0; i < numprocs; i++) {
	  arrivalTimes[i] = procs[i].arrival_time;
	  serviceTimes[i] = procs[i].service_time;
  }
  
  double avgs[2] = {0,0};
  
  
  fcfs(numprocs,serviceTimes,arrivalTimes,waitingTimes,turnaroundTimes,finishTimes,avgs);
  printf("\nFCFS: \nAverage Waiting time: %0.3f\nAverage Turnaround time: %0.3f\n\n",avgs[0],avgs[1]);
  
  sjf(numprocs,serviceTimes,arrivalTimes,waitingTimes,turnaroundTimes,finishTimes,avgs);
  printf("\nSPN: \nAverage Waiting time: %0.3f\nAverage Turnaround time: %0.3f\n\n",avgs[0],avgs[1]);
  
  hppn(procs, numprocs);

  /* Either call your implemented functions for performing FCFS, SPN,
     and HRRN, or insert your code here to perform these algorithms.
     My recommendation is to write one or more functions for these
     algorithms in order for your main to be more readable and
     manageable.
  */

  free(procs);   // procs array was dynamically allocated, so free up

  return 0;
}

int fcfs(int len, int services[], int arrive[], int waiting[], int turnaround[], int finish[], double avgs[]){
	int i = 0;
	double sumTurn = 0;
    double sumWait = 0;
	
	waiting[0] = 0;
	finish[0] = arrive[0] + services[0];
	turnaround[0] = services[0];
	
	//go through the queue iteratively, calculating the waiting and TR.
	for (i = 1; i < len; i++) {
		if (arrive[i] > finish[i-1]) {
			waiting[i] = 0;
		}
		else {
			waiting[i] = finish[i-1] - arrive[i];
		}
		turnaround[i] = services[i] + waiting[i];
		finish[i] = turnaround[i] + arrive[i];
	}
	
	
	  //sum up the total turnaround and waiting times
    for (i = 0; i < len; i++){
        sumTurn += turnaround[i];
        sumWait += waiting[i];
    }
  
  
    avgs[0] = sumWait / len;
	avgs[1] = sumTurn / len;
	
	
	//uncomment the following block to print the arrival, service, waiting, turnaround, and finish times (for debugging)
    /*printf("\narrival times: ");
    for (i = 0; i < len; i++)printf("%d,",arrive[i]);
    printf("\nservice times: ");
    for (i = 0; i < len; i++)printf("%d,",services[i]);

    printf("\nwaiting times: ");
    for (i = 0; i < len; i++)printf("%d,",waiting[i]);
    printf("\nturnaround times: ");
    for (i = 0; i < len; i++)printf("%d,",turnaround[i]);
    printf("\nfinish times: ");
    for (i = 0; i < len; i++)printf("%d,",finish[i]);*/
	
	
	return 0;
}



int selSort(int a[],int lower, int upper){
    //a is the array,lower is the lower bound, upper is the upper switching bound.
  int i = 0;
  int j = 0;
  int temp = 0;

  for(i=lower;i<upper;i++){
      for(j=i+1;j<upper;j++){
           if(a[i]>a[j]){
                //sort arrival time list
               temp=a[i];
              a[i]=a[j];
              a[j]=temp;

           }
      }
  }
  

  
  return 0;
}

//the max arrival time starts at 0.
//take all of the elements that are under the max arrival time and sort them by the shortest service time.

int sjf(int len, int services[], int arrive[], int waiting[], int turnaround[], int finish[], double avgs[]){
    int i = 0;
    int j = 0;
    int maxArrive = arrive[0];
    int maxIndex = 0;
    double sumTurn = 0;
    double sumWait = 0;
    //double doubleLen = (double) len;

    for (j = 0; j < len; j++) {
        //this for loop finds all of the processes that have arrived.
        for (i = 0; i< len; i++) {
            if (arrive[i] <= maxArrive) maxIndex = i;
            else break;
        }
        //sort the processes (that have arrived) in ascending order.
        selSort(services,j,maxIndex+1);

        //raise the max arrival time.
        maxArrive += services[j];
    }





    waiting[0] = 0;

    int startTime = arrive[0];//0,3,6,7
    //printf("Start Time: %d,",startTime);
    for (i = 1; i < len; i++) {
        startTime += services[i-1];
        //printf("%d,",startTime);
        //waiting[i] = waiting[i-1] + arrive[i];
        if (startTime > arrive[i]) waiting[i] = startTime - arrive[i];
        else waiting[i] = 0;
    }

     //calculate turnaround time:
    for (i = 0; i < len; i++) {
        turnaround[i] = services[i] + waiting[i];
    }

    //calculate finish time:
    for (i = 0; i < len; i++) {
        finish[i] = turnaround[i] + arrive[i];
    }



    //uncomment the following block to print the arrival, service, waiting, turnaround, and finish times (for debugging)
    /*printf("\narrival times: ");
    for (i = 0; i < len; i++)printf("%d,",arrive[i]);
    printf("\nservice times: ");
    for (i = 0; i < len; i++)printf("%d,",services[i]);

    printf("\nwaiting times: ");
    for (i = 0; i < len; i++)printf("%d,",waiting[i]);
    printf("\nturnaround times: ");
    for (i = 0; i < len; i++)printf("%d,",turnaround[i]);
    printf("\nfinish times: ");
    for (i = 0; i < len; i++)printf("%d,",finish[i]);*/


    //sum up the total turnaround and waiting times
    for (i = 0; i < len; i++){
        sumTurn += turnaround[i];
        sumWait += waiting[i];
    }

    //printf("\nAverage waiting time: %0.3f\nAverage turnaround time: %0.3f",sumWait / len, sumTurn / len);
	avgs[0] = sumWait / len;
	avgs[1] = sumTurn / len;

    return 0;
}


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

  //if(DEBUG){
    //printf("intialized arrays\n");
    //printf("\n\nProcess\t|arrival_time|service_time|wait_time\n");
    //for(i=0;i<numprocs;i++){
      //if(DEBUG){printf("P[%d]\t|\t%d\t|\t%d|\t%d\n",i,arrival_time[i],burst_time[i],wait_time[i]);}
    //}
  //}

  //if(DEBUG){printf("\n\nProcess\t|Turnaround time|waiting time|priority\n");}

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
    // if(DEBUG){printf("--- Current = P[%d] --- time = %d ---\n", largest, time);}
    // if(DEBUG){printf("process: P[%d] current time:|%d\n",largest,time);}
    // increment sim wait time
    time+=burst_time[largest];
    //decrement how many remain
    remain--;
    //if(DEBUG){printf("P[%d]\t|\t%d\t|\t%d\t|\t%f\n",largest+1,time-arrival_time[largest],time-arrival_time[largest]-burst_time[largest], priority[largest]);}
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