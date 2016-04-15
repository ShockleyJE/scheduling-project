/* =========================================================================
 * Just thought some helper functions would be... well... helpful
 * =========================================================================
 */

 void resetGlobals(){
   clock= 0;
   sum_turnaround_time = 0;
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
double averageTurnaroundTime(int theTurnaround){
	double result = theTurnaround / (double) numberOfProcesses;
	return result;
}
/**
 * Calulates average wait time
 */
double averageWaitTime(int theWait){
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
