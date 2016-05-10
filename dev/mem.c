#include <stdlib.h>   // for malloc() and free()
#include <stdio.h>
#include "mem.h"

/*
 * 
 * tar -pczf adamson.tar.gz /root/downoads/...  (or just adamson/)
  Physical memory array. This is a static global array for all
  functions in this file.  An element in the array with a value of
  zero represents a free unit of memory.
*/
static dur_t* memory;

/*
 The size (i.e. number of units) of the physical memory array. This is
 a static global variable used by functions in this file.
 */
static int mem_size;


/*
 The last_placement_position variable contains the end position of the
 last allocated unit used by the next fit placement algorithm.
 */
static int last_placement_position;

//Extra function initiations:
int getchunk(int startindex);

int getFirstEmpty();

void allocate(int size, int duration, int startindex);

int firstCaseInit(int size, int duration);

int nextCaseInit(int size, int duration);

int bestCaseInit(int size, int duration);



/*
  Using the memory placement algorithm, strategy, allocate size
  units of memory that will reside in memory for duration time units.

  If successful, this function returns the number of contiguous blocks
  (a block is a contiguous "chuck" of units) of free memory probed while 
  searching for a suitable block of memory according to the placement 
  strategy specified.  If unsuccessful, return -1.

  If a suitable contiguous block of memory is found, the first size
  units of this block must be set to the value, duration.
 */
int mem_allocate(mem_strats_t strategy, int size, dur_t duration){
	int allocateStrategy;

	//initiate based on the strategy (functions elaborated at bottom for readability).
	if (strategy == FIRSTFIT) allocateStrategy = firstCaseInit(size, duration);
	else if (strategy == NEXTFIT) allocateStrategy = nextCaseInit(size, duration);
	else allocateStrategy = bestCaseInit(size, duration);
	return allocateStrategy;
}

/*
  Go through all of memory and decrement all positive-valued entries.
  This simulates one unit of time having transpired.  NOTE: when a
  memory cell is decremented to zero, it becomes "unallocated".
 */
int mem_single_time_unit_transpired(){
	int i;
	//decrement every memory.
	for (i = 0; i < mem_size; i++) if (memory[i] > 0) memory[i]--;
	return 0;
}

/*
  Return the number of fragments in memory.  A fragment is a
  contiguous free block of memory of size less than or equal to
  frag_size.
 */
int mem_fragment_count(int frag_size) { 
  int i = 0;
  int fragCount = 0;
  int freeCount = 0;
  while(i < mem_size) {
    if(memory[i] == 0)freeCount++;
    
    if(i > 0 && memory[i] != 0 && memory[i-1] == 0 ) {
      //count number of frags
      if(freeCount < frag_size) fragCount++;
      freeCount = 0;
    }
    i++;
  }
  return fragCount;
}


/*
 Allocate physical memory to size. This function should 
 only be called once near the beginning of your main function.
 */
void mem_init(int size )
{
	memory = malloc( sizeof(int)*size );
	last_placement_position = 0;
	mem_size = size;
	mem_clear();
}


/*
  Set the value of zero to all entries of memory.
 */
void mem_clear(){
	int i;
	last_placement_position = 0;
	for (i = 0; i < mem_size; i++) memory[i] = 0;
	
}





/*
 Deallocate physical memory. This function should 
 only be called once near the end of your main function.
 */
void mem_free(){ free( memory ); }




/*
  Print memory for testing/debugging purposes.  This is an optional
  routine to write, but highly recommended!  You will need to test and
  debug your allocation algorithms.  Calling this routine in your
  main() after every allocation (successful or not) will help in this
  endeavor.  NOTE: you should print the memory contents in contiguous
  blocks, rather than single units; otherwise, the output will be very
  long.
 */
void mem_print(){
	printf("Current Memory: ");
	int i;
	for (i = 0; i < mem_size; i++) printf("%d|", memory[i]);
	printf("\n");
}




//Extra functions:

void allocate(int size, int duration, int startindex){
	int i;
	for (i = 0; i < size; i++) memory[startindex + i] = duration;
}

int getFirstEmpty(){
	int i;
	for (i = 0; i < mem_size; i++) if (memory[i] == 0) return i;
	return -1;
}


int getchunk(int startindex){
	int currentSize = 0;
	int i = 0;
	for (i = startindex; i < mem_size; i++){
		if (memory[i] == 0) currentSize++;
		else break;
	}
	return currentSize;
}




int firstCaseInit(int size, int duration){
	int i = getFirstEmpty();
	int chunksize = 0;
	int isDone = 0;
	int tries = 0;
	
	if (i == -1) return -1;

	while (i < mem_size && !isDone){
		chunksize = getchunk(i);
		if (chunksize <= 0) i++;
		
		else if (chunksize >= size){
			isDone = 1;
			allocate(size, duration, i);
		}
		
		else {
			i += chunksize;
			tries += 1;
		}
	}

	if (isDone) return tries;
	else return -1;//failed

}

int nextCaseInit(int size, int duration){
	int i = last_placement_position;
	 int chunksize = 0;
	 int done = 0;
	 int tries = 0; 
	 int end = 0;
	
	while (i < mem_size && !done){
		chunksize = getchunk(i);
		if (chunksize <= 0) i++;

		else if (chunksize >= size){
			done = 1;
			allocate(size, duration, i);
			last_placement_position = i;	
		}
		
		else {
			i += chunksize;
			tries++;
			if (!end && i >= mem_size){
				end = 1;
				i = i % mem_size;
			}
		}
	}
	if (done) return tries;
	else return -1;
}


int bestCaseInit(int size, int duration){
   int i = getFirstEmpty();
   int chunksize = 0;
   int found = 0;
   int besti = 0;
   int bestsize = mem_size + 1;
   int tries = 0;

   while (i < mem_size){
      chunksize = getchunk(i);
      if (chunksize <= 0)i++;

      //perfect fit
      else if (chunksize == size)return i;

      else if (chunksize > size && chunksize <= bestsize){
         //new optimal chunk
         besti = i;
         bestsize = chunksize;
         i += chunksize;
	     found = 1;
		 
      }
      else {
		  i += chunksize;
		  tries++;
			
      }
   } 

	if (found){
		allocate(size, duration, besti);
		return tries; }
		
	else return -1;
}