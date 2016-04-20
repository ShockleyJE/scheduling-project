#include <stdio.h>   // for printf()
#include <stdlib.h>  // for atoi()
#include <time.h>
#include "procs.h"
#include "procheap.h"

//ADD SIM TIME!!!!!!!!!!!!!!!!!!11

//gcc -o pro sched_compare.c procs.c procheap.c poisson.c -lm

// DO NOT CHANGE THESE TWO CONSTANTS !
#define INTER_ARRIVAL_TIME 3   // mean poisson dist
#define SERVICE_TIME       5   // mean poisson dist

int sjf(int len, proc_t * procs, int waiting[], int turnaround[], int finish[], double avgs[]);
int fcfs(int len, proc_t * procs, int waiting[], int turnaround[], int finish[], double avgs[]);
void hppn(proc_t * procs, int numprocs);

//function to calculate time difference of simulation
double mydifftime(struct timespec *tp0, struct timespec *tp1) {

  double secs = (int) (tp1->tv_sec - tp0->tv_sec);
  double nanosecs = (int) (tp1->tv_nsec - tp0->tv_nsec);

  if (nanosecs < 0) {
    nanosecs += 1000000000;
    secs--;
  }

  return secs*1000000000+nanosecs;

} 

int main(int argc, char** argv)
{
  int numprocs, seed;
  proc_t *procs;   // array of procs with service time and arrival time
  proc_t *procsSJF;

  if (argc < 3) {
    fprintf(stderr, "USAGE: %s numprocs seed\n", argv[0]);
    return 1;
  }

  numprocs = atoi(argv[1]);
  seed = atoi(argv[2]);

  // create an array of numprocs randomly generate (arrival time, service time)
procs = procs_random_create(numprocs, seed, INTER_ARRIVAL_TIME, SERVICE_TIME);

//create a separate procs for shortest job first, because sjf mixes up the procs.
procsSJF = procs_random_create(numprocs, seed, INTER_ARRIVAL_TIME, SERVICE_TIME);


  // Uncomment the next block of code and comment the line above if
  // you want to read the input from a file instead of generating
  // random values. This can be useful for debugging your code with
  // known inputs.  The file, "book_example.txt", contains an example
  // from the book.

  
  /*if ((procs = procs_read("book_example.txt", &numprocs)) == NULL) {
    fprintf(stderr, "Error reading procs array\n");
    return 2;
  }*/
  

  

  //create arrays for waiting, TR, and finish times. (for debugging use).
   int *waitingTimes;
  waitingTimes = malloc(numprocs * sizeof(int));
   int *turnaroundTimes;
  turnaroundTimes = malloc(numprocs * sizeof(int));
   int *finishTimes;
  finishTimes = malloc(numprocs * sizeof(int));

  double avgs[2] = {0,0};
  
  
  
  struct timespec start, end;
  double elapsed;
    //call the three scheduling algorithms.
    
    
    //Execute FCFS
    clock_gettime(CLOCK_REALTIME, &start);
    fcfs(numprocs,procs,waitingTimes,turnaroundTimes,finishTimes,avgs);
    clock_gettime(CLOCK_REALTIME, &end);
    elapsed = mydifftime(&start, &end);
    printf("\nFCFS: \nAverage Waiting time: %0.3f\nAverage Turnaround time: %0.3f\n",avgs[0],avgs[1]);
	printf("time in nanoseconds: %.4f\n\n",  elapsed);
	
  
  
  
  
  //Execute SJF
  clock_gettime(CLOCK_REALTIME, &start);
  sjf(numprocs,procsSJF,waitingTimes,turnaroundTimes,finishTimes,avgs);
  clock_gettime(CLOCK_REALTIME, &end);
    elapsed = mydifftime(&start, &end);
  printf("\nSPN: \nAverage Waiting time: %0.3f\nAverage Turnaround time: %0.3f\n\n",avgs[0],avgs[1]);
  printf("time in nanoseconds: %.4f\n\n",  elapsed);
  
  
  //Execute HPPN
  clock_gettime(CLOCK_REALTIME, &start);
  hppn(procs, numprocs);
    clock_gettime(CLOCK_REALTIME, &end);
    elapsed = mydifftime(&start, &end);
  printf("time in nanoseconds: %.4f\n\n",  elapsed);

  /* Either call your implemented functions for performing FCFS, SPN,
     and HRRN, or insert your code here to perform these algorithms.
     My recommendation is to write one or more functions for these
     algorithms in order for your main to be more readable and
     manageable.
  */

  free(procs);   // procs array was dynamically allocated, so free up

  return 0;
}


//First come first serve algorithm
int fcfs(int len, proc_t * procs, int waiting[], int turnaround[], int finish[], double avgs[]){
	int i = 0;
	double sumTurn = 0;
    double sumWait = 0;
	
	waiting[0] = 0;
	finish[0] = procs[0].arrival_time + procs[0].service_time;
	turnaround[0] = procs[0].service_time;
	
	//go through the queue iteratively, calculating the waiting and TR.
	for (i = 1; i < len; i++) {
		if (procs[i].arrival_time > finish[i-1]) {
			waiting[i] = 0;
		}
		else {
			waiting[i] = finish[i-1] - procs[i].arrival_time;
		}
		turnaround[i] = procs[i].service_time + waiting[i];
		finish[i] = turnaround[i] + procs[i].arrival_time;
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
    for (i = 0; i < len; i++)printf("%d,",procs[i].arrival_time);
    printf("\nservice times: ");
    for (i = 0; i < len; i++)printf("%d,",procs[i].service_time);

    printf("\nwaiting times: ");
    for (i = 0; i < len; i++)printf("%d,",waiting[i]);
    printf("\nturnaround times: ");
    for (i = 0; i < len; i++)printf("%d,",turnaround[i]);
    printf("\nfinish times: ");
    for (i = 0; i < len; i++)printf("%d,",finish[i]);*/
	
	
	return 0;
}



int selSort(proc_t *procs,int lower, int upper){
    //a is the array,lower is the lower bound, upper is the upper switching bound.
  int i = 0;
  int j = 0;
  int temp = 0;

  for(i=lower;i<upper;i++){
      for(j=i+1;j<upper;j++){ 
           if(procs[i].service_time > procs[j].service_time){
                //sort arrival time list
               temp=procs[i].service_time ;
              procs[i].service_time = procs[j].service_time ;
              procs[j].service_time =temp;

           }
      }
  }
  

  
  return 0;
}

//the max arrival time starts at 0.
//take all of the elements that are under the max arrival time and sort them by the shortest service time.

int sjf(int len, proc_t *procs, int waiting[], int turnaround[], int finish[], double avgs[]){
    int i = 0;
    int j = 0;
    int maxArrive = procs[0].arrival_time;
    int maxIndex = 0;
    double sumTurn = 0;
    double sumWait = 0;
    //double doubleLen = (double) len;

    for (j = 0; j < len; j++) {
        //this for loop finds all of the processes that have arrived.
        for (i = 0; i< len; i++) {
            if (procs[i].arrival_time <= maxArrive) maxIndex = i;
            else break;
        }
        //sort the processes (that have arrived) in ascending order.
        selSort(procs,j,maxIndex+1);

        //raise the max arrival time.
        maxArrive += procs[j].service_time;
    }





    waiting[0] = 0;

    int startTime = procs[0].arrival_time;//0,3,6,7
    //printf("Start Time: %d,",startTime);
    for (i = 1; i < len; i++) {
        startTime += procs[i-1].service_time;
        //printf("%d,",startTime);
        //waiting[i] = waiting[i-1] + arrive[i];
        if (startTime > procs[i].arrival_time) waiting[i] = startTime - procs[i].arrival_time;
        else waiting[i] = 0;
    }

     //calculate turnaround time:
    for (i = 0; i < len; i++) {
        turnaround[i] = procs[i].service_time + waiting[i];
    }

    //calculate finish time:
    for (i = 0; i < len; i++) {
        finish[i] = turnaround[i] + procs[i].arrival_time;
    }



    //uncomment the following block to print the arrival, service, waiting, turnaround, and finish times (for debugging)
    /*printf("\narrival times: ");
    for (i = 0; i < len; i++)printf("%d,",procs[i].arrival_time);
    printf("\nservice times: ");
    for (i = 0; i < len; i++)printf("%d,",procs[i].service_time);

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


//custom struct for hppn items
typedef struct hppn_proc_struct
{
 int name;
 int arrival_time,burst_time,wait_time,turnaround_time;
 int completed;
} hppn_procs_t;

//sort the processes of hppn by arrival.
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

//main hppn scheduling algorithm
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
  }
  printf("HPPN\n" );
  printf("Average waiting time:\t\t%f\n",avg_wait_time/numprocs);
  printf("Average turnaround time:\t%f\n",avg_turnaround_time*1.0/numprocs);

  free(p);
}