
#include <stdio.h>
#include <stdlib.h>

/* prototype definition for node */
typedef struct node {
  double arrival_time;
  double service_time;
  double wait_time;
  double end_time;
  struct node * next;
} node;

int main(proc_t *procs, int numprocs)
{

  struct node * front = NULL; /* will be the pointer to my linked list */
  struct node * last = NULL; /* for upkeep */
  struct node * curr = NULL /* currntly running process */

  //void traverse1(struct node *);                      /* prototype */
  void insertInOrder (struct node *, struct node *);  /* prototype */
  void updateWaitTimes(struct node * );               /* prototype */
  node getNextProcess(struct node * );                /* prototype */
  node * createProcessNode(proc_t *, node *);           /* prototype */
  void removeNode(node * , node ** )      /* prototype */

  // upkeep
  resetGlobals();

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
  printf("average \n", );

  return 0;
}

/* =========================================================================
 *     Linked List
 * =========================================================================
 */

/**
 * the following routine traverses and prints the contents of the list,
 * detecting the end of the list by a NULL pointer
 * use this for debugging
 */
 void traverse(struct node * first){
   struct node * walker = first;
   printf("The values in the list are: ");
   while (walker != NULL) {
      walker = walker->next;
   }
 }
 /**
  * the following routine traverses and prints the contents of the list,
  * detecting the end of the list by a NULL pointer
  * use this for debugging
  */
 void setBack(struct node * first, struct node * last){
   struct node * walker = first;
   while (walker != NULL) {
      last= walker;
      walker = walker->next;
   }
 }
 /**
  * the following routine traverses and updates wait times,
  * detecting the end of the list by a NULL pointer
  */
  void updateWaitTimes(struct node * first){
    struct node * walker = first;
    while (walker != NULL) {
       walker->wait_time +=1;
       walker = walker->next;
    }
  }
 /**
  * the following routine creates a process node, appended to front
  * sets front equal to proc node
  * returns front
  */
 node *createProcessNode(proc_t *p, node * front, int tempid){
   node * proc_node = (node*)malloc(sizeof(node));
   if (proc_node == NULL){
     error("out of memory");
   }
   proc_node->id= tempid;
   proc_node->arrival_time = p->arrival_time;
   proc_node->service_time = p->service_time;
   proc_node->wait_time = p->wait_time;
   proc_node->end_time = 0;
   proc_node->next = front;
   front = proc_node;
   proc_node = NULL; //no longer available by this name
   return front;
 }
 /**
  * the following routine traverses and returns node w/ highest response_ratio,
  * detecting the end of the list by a NULL pointer
  */
 node getNextProcess(struct node * first){
   struct node * walker = first;
   struct node * currentHRR = first;
   while (walker != NULL && walker->next !=NULL) {
      walker = walker->next;
      if(getResponseRatio(currentHRR) > getResponseRatio(walker)){
        currentHRR= walker;
      }
   }
   return currentHRR;
 }
 /**
  * the following routine traverses and deletes node toRemove
  * simulates process completion
  */

   void removeNode(node * thisNode, node ** head) {
     if (strcmp(thisNode->state, ((*head)->state) == 0) {
         node * temp = *head;
         *head = (*head)->next;
         free(temp);
         return;
     }

     node * current = (*head)->next;
     node * previous = *head;
     while (current != NULL && previous != NULL) {
         if (thisNode->id == current->id) {
             node * temp = current;
             previous->next = current->next;
             free(temp);
             return;
         }
         previous = current;
         current = current->next;
     }
     return;
 }

 /* =========================================================================
  *     Comparing times
  * =========================================================================
  */

  /**
   * Calculates average turnaround time
   */
  double averageTurnaroundTime(int theTurnaroundn, int numberOfProcesses){
  	double result = theTurnaround / (double) numberOfProcesses;
  	return result;
  }
  /**
   * Calulates average wait time
   */
  double averageWaitTime(int theWait, int numberOfProcesses){
  	double result = theWait / (double) numberOfProcesses;
  	return result;
  }

  /* =========================================================================
   *     HPPN
   * =========================================================================
   */
   /**
   * Returns response ratio for a process
   */
   int getResponseRatio(const void *a) {
     proc_t *process = (proc_t *) a;
     int response_ratio;
     response_ratio= ((process->wait_time + process->service_time)/process->service_time);
     return response_ratio;
   }
   /**
   *  Updates wait_time for process
   *
   *  When using sim time with global clock, pass in clock so it is passed
   *  in by value, otherwise using the global could theoretically mess up the accuracy
   */
   void setWaitTime(const void *a, int time) {
     proc_t *process = (proc_t *) a;
     int wt;
     wt = process->arrival_time - time;
     process->wait_time= wt;
   }
