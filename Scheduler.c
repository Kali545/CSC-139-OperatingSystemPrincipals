#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


//these are in milliseconds
int pid = 0;
int arrival_time = 0;
int burst_time = 0; //CPU time requested by task
int systemTime = 0; //keeps track of system time
int totalBurst = 0;

//round robin variables
int quantum = 0;

//calculation variables
double waitingTime = 0;
double totalWait = 0;
double nonActive = 0;
double down = 0;
double waitTime = 0;
double waitingT = 0;
double tArrival;
double active = 0;
double totalResponseTime = 0;
double totalTurnaroundTime = 0;
double turnaroundTime = 0;
double totalW = 0;
double tDone; //completion time
int np = 0; //number of processes 
double turnaround = 0;
double totalTurn = 0;

//keeps track of process for FCFS ------------------------------------------------------------------
//rows columns
int processArray[6][3] =//this will keep the processes
{
   {1, 0, 10},
   {2, 0, 9},
   {3, 3, 5},
   {4, 7, 4},
   {5, 10, 6},
   {6, 10, 7}
};


//struct for SRTF
struct processData {
    int piD;
    int arrive;
    int burst;
    int remainingBurst;
    int firstStart;
    int tdone;
};

struct node {
    int pid;
    int arrival;
    int burst;
    int firstRun;
    struct node* next;
    struct node* prev;
};
struct node* head = NULL;


//these are the functions for the scheduling algorithms

//FIRST COME FIRST SERVE------------------------------------------------------------------------------
void FCFS() {

    printf("First Come First Serve\n\n");

    int i = 0;
    int j = 0;
    // int k = 0;
    int burstCount = 0;
    int wait = 0;
    double start = 0;
    double tstart = 0;
   

    for (i = 0; i < 6; i++) {
        pid = processArray[i][j];
        // printf("pid: %d\n", pid);
        arrival_time = processArray[i][j + 1];
        //printf("arrival_time: %d\n", arrival_time);
        burst_time = processArray[i][j + 2];
        //printf("burst_time: %d\n", burst_time);
        burstCount = burst_time;  //this will keep track of how many times we print the line 
        //printf("processCount: %d\n", processCount);
        arrival_time;
        start = systemTime;
        waitTime = start - arrival_time;
        totalWait = waitTime + totalWait;
        for (int k = 0; k < burst_time; k++) {

            printf("<system time  %d> process  %d is running\n", systemTime, pid);
            if (burstCount > 0) {
                systemTime++;
                burstCount--;
            }
            
        }
        
        printf("<system time  %d> process  %d is finished.......\n", systemTime, pid);
        tDone = systemTime;
        //printf("tdone %d\n", systemTime);
        turnaroundTime = tDone - start;
        //printf("%.2f start\n", start);
        //printf("turnaroundTime %.2f\n", turnaroundTime);
        totalTurnaroundTime = turnaroundTime + totalTurnaroundTime;

    }
    
    averageWaitingTime(totalWait, np);
    averageTurnaroundTime(totalTurnaroundTime, np);
    averageResponseTime(totalWait, np);
    cpuUsage();
}



//ROUND ROBIN
void RR(struct processData cqueue_arr[], struct processData arr_arriveRR[], int np, int totalBurst, int quantum) {
       // printf("<system time  %d> process  %d is running\n", systemTime, arr_arriveRR[systemTime].piD);
        //printf("<system time  %d> que  %d is running\n", systemTime, cqueue_arr[systemTime].piD);
        


                                           
    }


//SHORTEST REMAINING TIME FIRST------------------------------------------------------------------------------------
void SRTF(int np, struct processData arr_arrive[], int total) {
    
    printf("Shortest Remaining Time First\n\n");
    totalBurst = total;
    //printf("totalb %d", totalBurst);
    int complete = 0; //how many pids are still left to complete
    int small = 30;
    int k = 0;
    int i = 0;
    int j = 0;
    
    for (systemTime = 0; systemTime < totalBurst; systemTime++) {
       small = 3000;
       for (j = 0; j < np; j++) {
           if (arr_arrive[j].arrive <= systemTime && arr_arrive[j].remainingBurst > 0 && arr_arrive[j].remainingBurst < small) {
              small = arr_arrive[j].remainingBurst;
              k = j;
           }    
       }
       if (arr_arrive[k].remainingBurst == arr_arrive[k].burst) {
           arr_arrive[k].firstStart = systemTime;
           //printf("%d first start \n", systemTime, arr_arrive[k].firstStart);
       }
       arr_arrive[k].remainingBurst--;
       printf("<system time  %d> process  %d is running\n", systemTime, arr_arrive[k].piD);
       
       if (arr_arrive[k].remainingBurst == 0) {
           printf("<system time  %d> process  %d is finished.......\n", systemTime, arr_arrive[k].piD);
           arr_arrive[k].tdone = systemTime;
           complete++;
       }   
        }
    calculateTotalWait(arr_arrive, np);
   // printf("%.2f \n", totalW);
    calculateTotalTurnAround(arr_arrive, np);
    averageWaitingTime(totalW, np);
    averageTurnaroundTime(totalTurn, np);
    averageResponseTime(totalTurn, np);
    cpuUsage();
    }
//------------------------------------------------------------------------------------------------------------------

void calculateTotalTurnAround(struct processData arr_arrive[], int np) {
    for (int i = 0; i < np; i++) {
        turnaround = arr_arrive[i].tdone - arr_arrive[i].arrive;
        //printf("first start %d arrive %d wait %.2f\n", arr_arrive[i].firstStart, arr_arrive[i].arrive, waitingT);
        totalTurn = totalTurn + turnaround;
        printf("%.2f\n", totalTurn);

    }
}
void calculateTotalWait(struct processData arr_arrive[], int np) {
    for (int i = 0; i < np; i++) {
        waitingT = arr_arrive[i].firstStart - arr_arrive[i].arrive;
        //printf("first start %d arrive %d wait %.2f\n", arr_arrive[i].firstStart, arr_arrive[i].arrive, waitingT);
        totalW = waitingT + totalW;
        //printf("%.2f\n", totalW);

    }
}
//functions to sort list of items
void makeStruct(struct processData arr_arrive[]) {
    
    int jj = 0;
    for (int i = 0; i < 6; i++) {
        arr_arrive[i].piD = processArray[i][jj]; 
        arr_arrive[i].arrive = processArray[i][jj + 1];
        arr_arrive[i].burst = processArray[i][jj + 2];
        arr_arrive[i].remainingBurst = processArray[i][jj + 2];
    }
}

    //this sorts by arrival time srtf
    void sortArrival(struct processData arr_arrive[], struct processData arr_temp[], int n) {
        int i, j, min, nn;
        nn = n;
        for (i = 0; i < nn - 1; i++) {
            min = i;
            for (j = i + 1; j < nn; j++) {
                if (arr_arrive[j].arrive < arr_arrive[min].arrive) {
                    min = j;
                }
            }
            arr_temp[0] = arr_arrive[min];
            arr_arrive[min] = arr_arrive[i];
            arr_arrive[i] = arr_temp[0];
        }
    }

    //this sorts burst times
    void sortBurst(struct processData arr_arrive[], struct processData arr_temp[], int n) {
        int i, j, min, nn;
        nn = n;
       // for (i = 0; i < nn - 1; i++) {
            //min = i;
          // for (j = 0; j < nn; j++) {
                if (arr_arrive[j].arrive == arr_arrive[j+1].arrive) {
                    if (arr_arrive[j].remainingBurst > arr_arrive[j+1].remainingBurst) {
                        //min = j;
                       //printf("here");
                        //printf("here");
                        arr_temp[0] = arr_arrive[j];
                        arr_arrive[j] = arr_arrive[j+1];
                        arr_arrive[j+1] = arr_temp[0];
                    }
                }
                
          //  }
      //  }
    }

    //print array for arr_arrive
    void printArray(struct processData arr_arrive[], int size)
    {
        int i;
        for (i = 0; i < size; i++) {
            printf("pid %d \n", arr_arrive[i].piD);
            printf("arrival %d\n", arr_arrive[i].arrive);
            printf("burst: %d\n", arr_arrive[i].remainingBurst);
        }
    }
 
    void countBurst(struct processData arr[], int size)
    {
        int i;
        for (i = 0; i < size; i++) {
            totalBurst += arr[i].burst;
            //printf("burst: %d\n", arr_arrive[i].burst);
        }
        //printf("total Burst %d\n", totalBurst);
    }

//functions to calculate
void averageWaitingTime(double totalWait, int np){
   // waitingTime = tStart - tArrival;
    float avWait = totalWait / np; 
    printf("The average waiting time is: %.2f\n", avWait);

}

void averageTurnaroundTime(double totalTurnarounTime, int np){
   // turnaroundTime = tDone - tArrival;
    double avTurn = totalTurnaroundTime / np;
    printf("The average turnaround time is: %.2f\n", avTurn);

}

void averageResponseTime(double totalResponseTime, int np){
   // responseTime = tFirstRun - tArrival;
    double avResponse = totalResponseTime / np;
    printf("The average response time is: %.2f\n", avResponse);
}

void cpuUsage(){
    double activeTotal = systemTime - nonActive;
    double totalTime = systemTime;
    double cpuUsage = active / totalTime * 100;
   printf("The overall CPU usage is  100%\n\n", CPUusage);
    printf("===========================================================================================\n");
}


int main(int argc, char* argv[]){
    np = 6;
    struct processData arr_burst[6];
    struct processData arr_arrive[np];
    struct processData arr_temp[1]; 
    FCFS();
   makeStruct(arr_arrive);
   sortArrival(arr_arrive, arr_temp, np);
   sortBurst(arr_arrive, arr_temp, np);
   countBurst(arr_arrive, np);
   SRTF(np, arr_arrive, totalBurst);
   //printArray(arr_arrive, np);
 
    //RR(cqueue_arr, arr_arriveRR, 6, 41, 2);
        
        
        


}



