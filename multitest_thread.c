#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <pthread.h>
#include "multitest.h"

//Provides the upper and lower search bounds, as well as the target and a bool
typedef struct bounds{
  int tooSlow;
  int high;
  int low;
  int* arr;
  int found;
}bounds;

void mode(){
  printf("-thread Mode\n");
}

//Basic iterative search function
int itrSearch(int* arr, int target, int high, int low){
  int i;
  for(i = low; i < high; i++){
    if (arr[i] == target){
      return i;
    }
  }
  return -1;
}

//Thread, performs the search function, outputs index target is found
void* myThread(void* args){
  //int* threadID = (int*) args;
  //printf("Thread ID: %d\n", *threadID);

  int* failptr = 0;
  int* succptr;
  bounds* ptr = (bounds*)args;
  
  int ret = itrSearch(ptr->arr, ptr->tooSlow, ptr->high, ptr->low);
  if (ret != -1){
    //printf("Found at: %d\n", ret);
    ptr->found = 1;
    succptr = &ret;
    pthread_exit((void*)succptr);
  }

  pthread_exit((void*)failptr);
}

int mySearch(int* arr, int target, int threadSize, int arrSize){
  //randArr();
  //newList(14994);
  //arr[14994] = 0;
  void* status;
  int threadsMade = 0;
  int i;

  int totalThreads = arrSize / threadSize;
  // char* exit;
  bounds args = {threadSize, 0, target, arr};
  //void* status;
  
  // args->high = 250;
  //args->low = 0;
  //args->tooSlow = 20;
  
  pthread_t ptid[totalThreads];
  for (i = 0; i < totalThreads; i++){
    ptid[i] = i;
  }

  for (i = 0; i < totalThreads; i++){
    if (args.found != 1){
      //ptid = i;
      pthread_create(&ptid[i], NULL, myThread, &args);
      //printf("Thread ID: %d\n", ptid);
      args.high += threadSize;
      args.low += threadSize;
      threadsMade = i;
    }
    else{
      break;
    }
  }

  //ptid = 0;
  
  for (i = 0; i < threadsMade; i++){
    //ptid = i;
    pthread_join(ptid[i], &status);
    //printf("Thread Status: %d\n", status);
    if (status != 0){
      return status;
    }
  }

  return 0;
}
