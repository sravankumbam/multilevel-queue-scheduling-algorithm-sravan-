#include<stdio.h> 
#include <stdlib.h> 
struct ps{ 
 int prior; 
 int burst_t; 
 int pid; 
 int wait_t; 
 int turn_t; 
 int remain_t; 
 int arrival_t; 
}; 
void getInp(); 
void calWaitTime(struct ps *q,int); 
void calTurnAroundTime(struct ps *q,int); 
void printQueue(struct ps *q,int size); 
void RoundRobin(); 
void PrioSorting(); 
void FCFS(); 
void printQueueI(struct ps); 
void printQueue(struct ps *,int); 
int q1_n=0,q2_n=0,q3_n=0,n=0;  
struct ps *q1,*q2,*q3; 
int time_quantum = 4; 
void getInput(){ 
 printf("\n Total Number of Process:\t"); 
 scanf("%d",&n); 
 int i; 
 q1 = (struct ps *)malloc(n*sizeof(struct ps)); 
 q2 = (struct ps *)malloc(n*sizeof(struct ps)); 
 q3 = (struct ps *)malloc(n*sizeof(struct ps)); 
 for(i=0;i<n;i++) 
 { 
  struct ps p; 
  printf("\n\t\tProcess %d\n\n",i+1); 
  p.arrival_t = (rand())%(n+1);     
  printf("PId:\t"); 
  scanf("%d",&p.pid); 
  printf("Priority (1-9):\t"); 
  scanf("%d",&p.prior); 
  printf("\nBurst Time: %d\t",p.burst_t); 
  scanf("%d",&p.burst_t); 
  p.remain_t = p.burst_t; 
  if(p.prior>0 && p.prior<=3){ 
   q1[q1_n++]  = p; 
  }else if(p.prior>3 && p.prior<=6){ 
   q2[q2_n++] = p; 
  }else{ 
   q3[q3_n++] = p; 
  }   
 } 
} 
void printQueue(struct ps *q,int size){ 
 
 calcWaitingTime(q,size); 
 calcTurnAroundTime(q,size); 
 printf("\nPId\t\tPriority\t\tBurst Time\t\tWaiting Time\t\tTurnAround Time\t\tArrival"); 
 printf("\n*****************************************************\ n"); 
 int i; 
 for(i=0;i<size;i++){ 
  printQueueI(q[i]); 
 } 
 printf("\n\n"); 
} 
void printQueueI(struct ps p){ 
 printf("\n%d\t\t%d\t\t\t%d\t\t\t%d\t\t\t%d\t\t%d",p.pid,p.prior,p.burst_t, p.wait_t,p.turn_t,p.arrival_t); 
} 
void calcWaitingTime(struct ps *q,int size){ 
 q[0].wait_t = 0; 
 int i; 
 for(i=1;i<size;i++){ 
  q[i].wait_t = q[i-1].wait_t + q[i-1].burst_t; 
 } 
} 
void calcTurnAroundTime(struct ps *q,int size){ 
 q[0].wait_t = 0; 
 int i; 
 for( i=0;i<size;i++){ 
  q[i].turn_t = q[i].wait_t + q[i].burst_t; 
 } 
} 
void RoundRobinAlgo(struct ps *q,int size){ 
 int time=0,i=0,remain=size,flag=0,wait_time=0,tat_time=0,total_times=0; 
 for(time=0,i=0;remain!=0;){ 
  struct ps p = q[i]; 
  if(p.remain_t<=time_quantum && p.remain_t>0){ 
   time += p.remain_t; 
   p.remain_t = 0; 
   flag = 1; 
  }else if(p.remain_t>time_quantum){ 
   p.remain_t -= time_quantum; 
   time += time_quantum; 
  } 
  if(p.remain_t==0 && flag==1){ 
   remain--; 
   printf("\n%d\t\t%d\t\t\t%d\t\t\t%d\t\t\t%d",p.pid,p.prior,p.burst_t,p.wait _t,p.turn_t); 
   wait_time += time -p.arrival_t - p.burst_t; 
   tat_time += time -p.arrival_t; 
   flag = 0; 
  } 
   
  if(i==remain-1){ 
   i=0; 
  }else if(q[i+1].arrival_t<time){ 
   i++; 
  }else{ 
   i=0; 
  } 
 
  q[i] = p; 
 } 
 printf("\nAverage Waiting Time= %f\n",wait_time*1.0/n);  
 printf("Avg Turnaround Time = %f\n",tat_time*1.0/n);   
} 
void RoundRobin(){ 
 printf("\n\t\tRound Robin\t"); 
 printf("\n****************************************************** *****\n\n"); 
 
 printf("\nPId\t\tPriority\t\tBurst Time\t\tWaiting Time\t\tTurnAround Time"); 
 printf("\n****************************************************** *****\n"); 
 calcWaitingTime(q3,q3_n); 
 calcTurnAroundTime(q3,q3_n); 
 
 RoundRobinAlgo(q3,q3_n); 
} 
void PrioSortingAlgorithm(struct ps *q,int size){ 
 int i; 
 for( i=0;i<size;i++){ 
  int j; 
  for( j=0;j<size;j++){ 
   if(q[j].prior>q[i].prior){ 
    struct ps t = q[i]; 
    q[i] = q[j]; 
    q[j] = t; 
   } 
  } 
 } 
} 
void PrioSorting(){ 
 printf("\n\t\tPriority Sorting\t"); 
 printf("\n**********************************************\n\n"); 
 PrioSortingAlgorithm(q2,q2_n); 
 printQueue(q2,q2_n); 
} 
void FCFSAlgorithm(struct ps *q,int size){ 
 int i,j; 
 for( i=0;i<size;i++){ 
  for( j=0;j<size;j++){ 
   if(q[j].arrival_t>q[i].arrival_t){ 
    struct ps t = q[i]; 
    q[i] = q[j]; 
    q[j] = t; 
   } 
  } 
 } 
} 
void FCFS(){ 
  
 printf("\n\t\tFirst Come First Serve\t"); 
 printf("\n****************************************************\n \n"); 
 FCFSAlgorithm(q1,q1_n); 
 printQueue(q1,q1_n); 
} 
int main(){ 
 getInput(); 
 int i=1; 
 while(n>0){ 
  switch(i){ 
   case 3: 
    RoundRobin(); 
    break; 
   case 2: 
    PrioSorting(); 
    break; 
   case 1: 
    FCFS(); 
    break; 
  } 
  i++; 
  sleep(10); 
 } 
 printf("\n\n"); 
} 

