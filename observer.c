#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#define LB_SIZE 100
#define LONG "long"
#define SHORT "short"
#define STANDARD "standard"

char* delim; 
int iteration;
int duration;
int interval;
char c1;
char c2;
int count = 0;
char lineBuf[LB_SIZE];
char lineBuff[LB_SIZE];
char repTypeName[16];
char charRead;
struct timeval now;
int user, system1, idle, nice; 
char junk;
int boot;
int days, hours, minutes, seconds; 
int proc;
char fill1[100];
char fill2[100];
char fill3[100];
char fill5[100];
char fill6[100];

//void cpuModelMethod();
void cpuModelMethod()
{
  FILE* cpuModel = fopen("/proc/cpuinfo", "r");
while((fgets(lineBuf, sizeof(lineBuf), cpuModel))){
count++;
if(count == 5)
{
printf("CPU  %s\n", lineBuf);
}
}
fclose(cpuModel);

/*------------------kernel version----------------------*/
}
//void kernelVersionMethod();
void kernelVersionMethod()
{
FILE* kernelVersion = fopen("/proc/version","r");
printf("Kernel Version: ");
while((charRead =fgetc(kernelVersion))!= EOF)
{
printf("%c", charRead);
}
printf("\n");
fclose(kernelVersion);
}

/*-----------------system boot time----------------*/
//void bootTimeMethod();
void bootTimeMethod()
{
FILE* bootTime = fopen("/proc/uptime", "r");
printf("Boot Time:");
while((fgets(lineBuf, sizeof(lineBuf), bootTime)))
{
sscanf(lineBuf, "%d", &boot);
days = boot/60/60/24;
hours = boot /60/60% 24;
minutes = boot / 60 % 60;
seconds = boot % 60;
printf("%02d:%02d:%02d:%02d", days, hours, minutes, seconds);
}
printf("\n\n");
fclose(bootTime);
}
/*--------time of day---------------------------------*/
//void getTimeOfDay();
void getTimeOfDay(){
gettimeofday(&now, NULL);
printf("Time of Day: %s\n", ctime(&(now.tv_sec)));
}

/*---------machine hostname -----------------------*/
//void machineHostName();
void machineHostName(){
FILE* thisProcFile = fopen("/proc/sys/kernel/hostname", "r");
fgets(lineBuf, LB_SIZE+1, thisProcFile);
printf("Machine hostname: %s\n",lineBuf);
fclose(thisProcFile);
}
/*--------------------user, system, idle --------------*/
//void cpuModeMethod();
void cpuModeMethod(){
FILE* cpuMode = fopen("/proc/stat", "r");
fgets(lineBuf,sizeof(lineBuf), cpuMode);
sscanf(lineBuf, "%s %d %d %d %d", fill1, &user,&nice,&system1,&idle);
printf("User mode: %d\n", user);
printf("System mode: %d\n", system1);
printf("Idle mode: %d\n\n", idle);
fclose(cpuMode);
}
/*---------disk read/write--------------------*/
//void diskReadsWrites();
void diskReadsWrites(){
  int count1 = 0;
FILE* rwRequests = fopen("/proc/diskstats", "r");
fgets(lineBuf,sizeof(lineBuf), rwRequests);
fgets(lineBuf,sizeof(lineBuf),rwRequests);
 // printf("lineBuf %s", lineBuf);
 // count1++;
 // printf("count %d\n",count1);
  int one, two, four, five, six, seven, eight, nine;
  char three;
  sscanf(lineBuf, "%d %d %s %d %d %d %d %d %d",&one, &two, fill2, &four, &five, &six, &seven, &eight, &nine);
 // printf("Line Buff: %s\n", fill2);
  printf("Disk Reads: %d\n", four);
  printf("Disk Writes: %d\n\n", eight);
fclose(rwRequests);
}

/*-------context switches--------------------------------*/
//void contextSwitchMethod();
void contextSwitchMethod(){
//delim = NULL;
FILE* contextSwitch = fopen("/proc/stat", "r");
while((fgets(lineBuf, sizeof(lineBuf), contextSwitch))){
  delim = strtok(lineBuf, " ");
  if(delim != NULL){
    if(strcmp(lineBuf, "ctxt")==0){
    break;
    }
  }
}
delim = strtok(NULL,  " ");
printf("Context Switches: %s\n", delim);
fclose(contextSwitch);
}


/*--------processes created----------------------------------*/
//void processCreatedMethod();
void processCreatedMethod(){
FILE* process = fopen("/proc/stat", "r");
//delim = NULL;
while((fgets(lineBuf, sizeof(lineBuf),process))){
  delim = strtok(lineBuf, " ");
  {
    if(delim != NULL){
      
      if(strcmp(lineBuf, "processes")==0){
    
    break;
    }
  }
  
  }
  
}
  delim = strtok(NULL, " ");
  printf("Processes Created: %s\n", delim);
  fclose(process);
}

/*----------memory configured-------*/
//void memoryConfiguredMethod();
void memoryConfiguredMethod(){
//delim = NULL;
FILE* memory = fopen("/proc/meminfo", "r");
  fgets(lineBuf, sizeof(lineBuf), memory);
  printf("Memory Total: %s\n", lineBuf);
  fclose(memory);
}
/*--------memory Available--------------*/
void memoryFreeMethod(){
FILE* memoryFree = fopen("/proc/meminfo", "r");
fgets(lineBuf, sizeof(lineBuf), memoryFree);
fgets(lineBuf, sizeof(lineBuf), memoryFree);
  printf("Memory Free: %s\n\n", lineBuf);
  fclose(memoryFree);

}
/*---------------load average-------------------*/
void loadAverageMethod(){
while(iteration < duration){
  sleep(interval);
  FILE* loadavg = fopen("/proc/loadavg","r");
  fgets(lineBuf,sizeof(lineBuf), loadavg);
 printf("Interval: %d Iteration: %d Load Average: %s", interval, iteration, lineBuf);
    iteration += interval;
}

//fclose(loadavg);
}

/*-------------------main----------------------------------*/
int main(int argc, char *argv[]){
  cpuModelMethod();
  kernelVersionMethod();
  bootTimeMethod();
  getTimeOfDay();
if(argc > 1){
  sscanf(argv[1], "%c%c", &c1,&c2);
  
  if(c1 != '-'){
    fprintf(stderr, "usage: observer [-s][-l int dur]\n");
    exit(1);
  }
}
  if(c2 =='s'){
  strcpy(repTypeName, "Short");
  cpuModeMethod();
  diskReadsWrites();
  contextSwitchMethod();
  processCreatedMethod();
  }

if(c2 == 'l'){
strcpy(repTypeName, "Long");
interval = atoi(argv[2]);
duration = atoi(argv[3]);
  cpuModeMethod();
  diskReadsWrites();
  contextSwitchMethod();
  processCreatedMethod();
  memoryConfiguredMethod();
  memoryFreeMethod();
  loadAverageMethod();
}
return 0;

}
