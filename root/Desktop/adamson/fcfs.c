#include <stdio.h>   // for printf()
#include <stdlib.h>  // for atoi()

int fcfs(int bt[], int n)
{
    int wt[20],tat[20],avwt=0,avtat=0,i,j;
    //int finishTimes[20];
    //printf("Enter total number of processes(maximum 20):");
    //scanf("%d",&n);
 
    //printf("\nEnter Process Burst Time\n");
    //for(i=0;i<n;i++)
    //{
     //   printf("P[%d]:",i+1);
     //   scanf("%d",&bt[i]);
    //}
 
    wt[0]=0;    //waiting time for first process is 0
 
    //calculating waiting time
    for(i=1;i<n;i++)
    {
        wt[i]=0;
        for(j=0;j<i;j++)
            wt[i]+=bt[j];
    }
 
    printf("\nProcess\t\tService Time\tWaiting Time\tTurnaround Time\tFinish Time");
 
    //calculating turnaround time
    int finishTime = 0;
    for(i=0;i<n;i++)
    {
		finishTime += bt[i];
        //tat[i]=bt[i]+wt[i];
        tat[i] = bt[i] + wt[i];//turnaround time is burst time + waiting time.
        avwt+=wt[i];
        avtat+=tat[i];
        printf("\nP[%d]\t\t%d\t\t%d\t\t%d",i+1,bt[i],wt[i],tat[i]);
        
        //if (i==0) finishTimes[0] = bt[0];
        //else {
		//	finishTimes[i] = finishTimes[i-1] + bt[i];
		//	
		//}
		
		printf("\t\t%d",finishTime);
    }
	
	
 
    avwt/=i;
    avtat/=i;
    printf("\n\nAverage Waiting Time:%d",avwt);
    printf("\nAverage Turnaround Time:%d\n",avtat);
    
 
    return 0;
}

int main() {
	int serviceTimes[6] = {100,50,1,200,20,150}; 
	fcfs(serviceTimes,6);
	
	
	return 0;
}