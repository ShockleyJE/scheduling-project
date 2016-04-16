#i

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

int sjf(int len, int services[], int arrive[], int waiting[], int turnaround[], int finish[]){
    int i = 0;
    int j = 0;
    int maxArrive = arrive[0];
    int maxIndex = 0;
    double sumTurn = 0;
    double sumWait = 0;
    double doubleLen = (double) len;

    for (j = 0; j < len; j++) {
        //this for loop finds all of the processes that have arrived.
        for (i = 0; i< len+1; i++) {
            if (arrive[i] <= maxArrive) maxIndex = i;
            else break;
        }

        //sort the processes (that have arrived) in ascending order.
        selSort(services,j,maxIndex+1);

        //raise the max arrival time.
        maxArrive += services[j];
    }





    waiting[0] = 0;
    int startTime = 0;//0,3,6,7
    for (i = 1; i < len; i++) {
        startTime += services[i-1];
        //waiting[i] = waiting[i-1] + arrive[i];
        waiting[i] = startTime - arrive[i];
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
    /*printf("arrival times: ");
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

    printf("\nAverage waiting time: %0.3f\nAverage turnaround time: %0.3f",sumWait / len, sumTurn / len);


    return 0;
}

int main(){

    //turnaround = burst + waiting.
    //tr times = 3,7,11,14,3
    //waiting times = 0,
    int services[5] = {3,6,4,5,2};
    int arrive[5] =   {0,2,4,6,8};

    //int services[4] = {7,4,1,4};
    //int arrive[4] =   {0,2,4,5};
    int waiting[5];


    int turnaround[5];
    int finish[5];

    sjf(5,services,arrive,waiting,turnaround,finish);
    return 0;
}

