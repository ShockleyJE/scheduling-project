/* =========================================================================
 * Just thought some helper functions would be... well... helpful
 * =========================================================================
 */

 void resetGlobals(){
   clock= 0;
   sum_turnaround_time = 0;
 }

 /* =========================================================================
  *     Linked List
  * =========================================================================
  */

 typedef struct node {
   double arrival_time;
   double service_time;
   double wait_time;
   double end_time;
   struct node * next;
   int id;
 } node;

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
   * NOTE: the first is a recursive implementation, I'm going to try not to use it
   */

  //  node *RemoveNode(Node *currP, int toRemoveID)
  // {
  //   /* See if we are at end of list. */
  //   if (currP == NULL)
  //     return NULL;
  //
  //   /*
  //    * Check to see if current node is one
  //    * to be deleted.
  //    */
  //   if (currP->id == toRemoveID) {
  //     Node *tempNextP;
  //
  //     /* Save the next pointer in the node. */
  //     tempNextP = currP->next;
  //
  //     /* Deallocate the node. */
  //     free(currP);
  //
  //     /*
  //      * Return the NEW pointer to where we
  //      * were called from.  I.e., the pointer
  //      * the previous call will use to "skip
  //      * over" the removed node.
  //      */
  //     return tempNextP;
  //   }

    void RemoveNode(node * thisNode, node ** head) {
      if (strcmp(thisNode->state, ((*head)->state) == 0) {
          node * temp = *head;
          *head = (*head)->next;
          free(temp);
          return;
      }

      node * current = (*head)->next;
      node * previous = *head;
      while (current != NULL && previous != NULL) {
          if (strcmp(thisNode->id, current->id) == 0) {
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
 * Compare arrival time of two processes
 */
int compareArrivalTime(const void *a, const void *b){
	proc_t *first = (proc_t *) a;
	proc_t *second = (proc_t *) b;
	return first->arrivalTime - second->arrivalTime;
}
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
 *      Queueing processes
 * =========================================================================
 */
/**
 * Initializes a process queue. Makes an empty queue
 */
void initializeProcessQueue(Process_queue *q){
	q = (Process_queue*)malloc(sizeof(Process_queue));
	q->front = q->back = NULL;
	q->size = 0;
}
/**
 * Creates a single process node with pointer to data and next
 */
  Process_node *createProcessNode(proc_t *p){
	Process_node *node = (Process_node*)malloc(sizeof(Process_node));
	if (node == NULL){
		error("out of memory");
	}
	node->data = p;
	node->next = NULL;
	return node;
}
/**
 * Equeues a process
 */
void enqueueProcess(Process_queue *q, proc_t *p){
	Process_node *node = createProcessNode(p);
	if (q->front == NULL){
		assert(q->back == NULL);
		q->front = q->back = node;
	}
	else{
		assert(q->back != NULL);
		q->back->next = node;
		q->back = node;
	}
	q->size++;
}
/**
 * Dequeues a process
 */
void dequeueProcess(Process_queue *q) {
    Process_node *deleted = q->front;
    assert(q->size > 0);
    if (q->size == 1) {
        q->front = NULL;
        q->back = NULL;
    } else {
        assert(q->front->next != NULL);
        q->front = q->front->next;
    }
    free(deleted);
    q->size--;
}

/* =========================================================================
 *      Comparing processes
 * =========================================================================
 */
 /**
 * Compare arrival time of two processes
 */
int compareArrivalTime(const void *a, const void *b) {
	proc_t *first = (proc_t *) a;
	proc_t *second = (proc_t *) b;
	return first->arrival_time - second->arrival_time;
}
/**
* Compare service time of two processes
*/
int compareServiceTime(const void *a, const void *b) {
 proc_t *first = (proc_t *) a;
 proc_t *second = (proc_t *) b;
 return first->service_time - second->service_time;
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
