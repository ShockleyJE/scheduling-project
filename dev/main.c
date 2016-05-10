#include <stdio.h>    /* for printf */
#include <stdlib.h>   /* for string to integer conversion, random numbers */
#include "mem.h"

/*
  The main program will accept four paramemters on the command line.
  The first parameter is the memory size.  The second parameter is the
  duration of the each simulation run.  The third parameter is the
  number of times to repeat each experiment (ie. number of runs). The
  fourth parameter is a random number seed. Here is an example command
  line:

  ./hw7 1000 3000 100 1235

  This means that your program should initialize physical memory to
  1,000 units, perform 100 runs with each run taking 3000 units of
  time, and the random number generator should be seeded (one time)
  with the value 1235.
*/

int main(int argc, char** argv) {
  if (argc != 5){ printf("ERROR: 4 arguments needed.\n"); exit(1);}
  
  
  int units = (int) strtol(argv[1],0,10);
  int seed = (int) strtol(argv[4],0,10);
  int runs = (int) strtol(argv[3],0,10);
  int times = (int) strtol(argv[2],0,10);
  int runNumber = 0;
  int timeNumber = 0;
  int size = 0;
  int duration = 0;
  mem_init(units);
  srand(seed);

  
  //Initialize all the variables
  int bestProbes = 0;
  int bestFrags = 0;
  float bestAvgProbes = 0;
  float bestAvgFailures = 0;
  float bestAvgFrags= 0;
  int bestTotalProbes = 0;
  int bestTotalFailures = 0;
  int bestTotalFrags = 0;
  
  int firstProbes = 0;
  int firstFrags = 0;
  float firstAvgProbes = 0;
  float firstAvgFailures = 0;
  float firstAvgFrags= 0;
  int firstTotalProbes = 0;
  int firstTotalFailures = 0;
  int firstTotalFrags = 0;
  
  int nextProbes = 0;
  int nextFrags = 0;
  float nextAvgProbes = 0;
  float nextAvgFailures = 0;
  float nextAvgFrags= 0;
  int nextTotalProbes = 0;
  int nextTotalFailures = 0;
  int nextTotalFrags = 0;
  
  

  for(runNumber=0; runNumber < runs; runNumber++) {
	  
	//Best Case:
    for(timeNumber = 0; timeNumber < times; timeNumber++) {
      size = rand() % MAX_REQUEST_SIZE + MIN_REQUEST_SIZE;
      duration = rand() % MAX_DURATION + MIN_DURATION;
      bestProbes = mem_allocate(BESTFIT,size,duration);

		//if the probe worked:
      if(bestProbes != -1 && bestProbes < 11) bestTotalProbes += bestProbes;
      
		  //the "b_probes < 11" check prevents outliers from
		  //skewing the data. Nearly all of the probe sizes are 
		  //under 10, while others are 500+.
		  //therefore, those outliers count as failures.
      else bestTotalFailures++;
      
      bestFrags = mem_fragment_count(MIN_REQUEST_SIZE-1);
      bestTotalFrags += bestFrags;
      mem_single_time_unit_transpired();//decrement
    }  
	  
	  
    // FIRST
    for(timeNumber=0; timeNumber<times; timeNumber++) {
      size = rand() % MAX_REQUEST_SIZE + MIN_REQUEST_SIZE;
      duration = rand() % MAX_DURATION + MIN_DURATION;
      firstProbes = mem_allocate(FIRSTFIT,size,duration);

      if(firstProbes != -1)firstTotalProbes += firstProbes;
      else firstTotalFailures++;
      
      firstFrags = mem_fragment_count(MIN_REQUEST_SIZE-1);
      firstTotalFrags += firstFrags;

      mem_single_time_unit_transpired();//decrement
    }
    mem_clear();

    // Next Case
    for(timeNumber = 0; timeNumber < times; timeNumber++) {
      size = rand() % MAX_REQUEST_SIZE + MIN_REQUEST_SIZE;
      duration = rand() % MAX_DURATION + MIN_DURATION;
      nextProbes = mem_allocate(NEXTFIT,size,duration);
       
      if(nextProbes != -1) nextTotalProbes += nextProbes;
      else nextTotalFailures++;
      
      nextFrags = mem_fragment_count(MIN_REQUEST_SIZE-1);
      nextTotalFrags += nextFrags;//collect sum of nextFrags
      mem_single_time_unit_transpired();
    }
    mem_clear();

    
    mem_clear();
  }

  bestAvgFrags = (float) bestTotalFrags/runs;
  bestAvgProbes = (float) bestTotalProbes/runs;
  bestAvgFailures = (float) bestTotalFailures/runs;
  
  firstAvgFrags = (float) firstTotalFrags/runs;
  firstAvgProbes = (float) firstTotalProbes/runs;
  firstAvgFailures = (float) firstTotalFailures/runs;
  
  nextAvgFrags = (float) nextTotalFrags/runs;
  nextAvgProbes = (float) nextTotalProbes/runs;
  nextAvgFailures = (float) nextTotalFailures/runs;
  
  printf("\nBESTFIT:");
  printf("\nmean fragment count = %0.6f",bestAvgFrags / times);
  printf("\nmean number of probes = %0.6f",bestAvgProbes / times);
  printf("\nmean number of fails = %0.6f",bestAvgFailures / times / times /2);


  
  printf("\nFIRSTFIT:");
  printf("\nmean fragment count =  %0.6f",firstAvgFrags / times);
  printf("\nmean number of probes = %0.6f",firstAvgProbes / times);
  printf("\nmean number of fails = %0.6f",firstAvgFailures / times /times );


  
  printf("\nNEXTFIT:");
  printf("\nmean fragment count =  %0.6f",nextAvgFrags / times);
  printf("\nmean number of probes = %0.6f",nextAvgProbes / times);
  printf("\nmean number of fails = %0.6f\n",nextAvgFailures / times / times / 2 );

  mem_free();
  return 0;
}