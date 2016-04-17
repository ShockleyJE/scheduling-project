#ifndef HELPERS_H
#define HELPERS_H

typedef struct node {
  double arrival_time;
  double service_time;
  double wait_time;
  double end_time;
  struct node * next;
  int id;
} node;


void traverse1(struct node *);                      /* prototype */
void insertInOrder (struct node *, struct node *);  /* prototype */
void updateWaitTimes(struct node * );               /* prototype */
node getNextProcess(struct node * );                /* prototype */
node * createProcessNode(proc_t *, node *);         /* prototype */
void removeNode(node * , node ** );                 /* prototype */
int getResponseRatio(const void *);                 /* prototype */
void setWaitTime(const void *a, int time);          /* prototype */
void setBack(struct node *, struct node *);         /* prototype */
double averageTurnaroundTime(int theTurnaroundn, int numberOfProcesses);
double averageWaitTime(int theWait, int numberOfProcesses);

#endif /* HELPERS_H */
