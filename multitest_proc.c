#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <math.h>
#include "multitest.h"

void mode(){
  printf("-proc Mode\n");
}

void search(int *array, int target, int upperbound, int arrSize){

	int m;
	int s;
	int x;
	int y;
	int count = arrSize / upperbound;
	int lowerbound;
	int status;
	int index;
	int subindex;
	int mod;
	pid_t pid;
		
	//put start time here	

	int pidarr[count];
	for(s=0; s < count; s++){
		
		
		pid = fork();
		if(pid < 0){
		  //printf("ERROR: fork failed\n");
			}
	
		if(pid == 0){//child process

			for(m = lowerbound; m < upperbound; m++ ){
	
				if(array[m] == target){
				  //printf("target found: %d, at index %d, by child: %d\n", target, m, getpid());
					//switch the index of target here for the next loop
					srand(time(0));
					int  a = (rand() % arrSize);
					int tempid = array[m];
					array[m] = array[a];
					array[a] = tempid;
					subindex = m - lowerbound;
					//printf("lowerbound: %d and m index : %d\n",lowerbound, m);
					}//end if statement
					
				}//end for loop

		exit(0);			
		}//end child
		
		lowerbound += 250;
		upperbound += 250;

		pidarr[s] = pid;

	}//end for loop
	
	if(pid>0) {//parent process
		int b;
		for(b=0; b<count; b++){
		  //printf( "pid of child %d is %d\n", b, pidarr[b]);	
			}

	for(status = 0; status < count; status++){
		waitpid(pidarr[status], &status, 0);	
		}
	}
		
	//printf("parent pid: %d\n",getpid());
		


}//end search function
