#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "multitest.h"

double minA = 9007199254740992;
double minB = 9007199254740992;
double minC = 9007199254740992;
double minD = 9007199254740992;
double minE = 9007199254740992;
double minF = 9007199254740992;
double maxA = 0;
double maxB = 0;
double maxC = 0;
double maxD = 0;
double maxE = 0;
double maxF = 0;
double timeA[150];
double timeB[150];
double timeC[150];
double timeD[150];
double timeE[150];
double timeF[150];
double standA = 0;
double standB = 0;
double standC = 0;
double standD = 0;
double standE = 0;
double standF = 0;
double meanA;
double meanB;
double meanC;
double meanD;
double meanE;
double meanF;

double minTime(double last, double curr){
  if (curr < last){
    return curr;
  }
  else{
    return last;
  }
}

double maxTime(double last, double curr){
  if (curr > last){
    return curr;
  }
  else{
    return last;
  }
}

int main(int argc, char** argv){
  mode();
  
  int arrSize = 20000;
  int arrSize2 = 5000;
  int arr[arrSize];
  int arr2[arrSize2];

  randArray(arr, arrSize);
  randArray(arr2, arrSize2);

  int target = 20;
  int i = 0;
  struct timeval start, end;
  
  // printf("Commencing Test A\n");
  //printf("TestA Parameters: Array Size of 20000, Thread/Process Size of 250\n");
  for (i = 0; i < 150; i++){
    printf("Test iteration: %d\n", i);

    //Test A
    printf("Test A: Array of 20000 units, split by 250 units\n");
    gettimeofday(&start, NULL);
    Test(target, arr, arrSize);
    gettimeofday(&end, NULL);
    timeA[i] = (double)(((end.tv_sec - start.tv_sec) * 1000000) + end.tv_usec) - (start.tv_usec);
    printf("Test A time: %f\n", timeA[i]);

    //Test B
    printf("Test B: Array of 5000 units, split by 250 units\n");
    gettimeofday(&start, NULL);
    Test(target, arr2, arrSize2);
    gettimeofday(&end, NULL);
    timeB[i] = (double)(((end.tv_sec - start.tv_sec) * 1000000) + end.tv_usec) - (start.tv_usec);
    printf("Test B time: %f\n", timeB[i]);

    //Test C
    printf("Test C: Array 20000 units, splits 100 units\n");
    gettimeofday(&start, NULL);
    Test2(target, arr, arrSize);
    gettimeofday(&end, NULL);
    timeC[i] = (double)(((end.tv_sec - start.tv_sec) * 1000000) + end.tv_usec) - (start.tv_usec);
    printf("Test C time: %f\n", timeC[i]);

    //Test D
    printf("Test D: Array 5000 units, splits 100 units\n");
    gettimeofday(&start, NULL);
    Test2(target, arr, arrSize);
    gettimeofday(&end, NULL);
    timeD[i] = (double)(((end.tv_sec - start.tv_sec) * 1000000) + end.tv_usec) - (start.tv_usec);
    printf("Test D time: %f\n", timeD[i]);

    //Test E
    printf("Test E: Array 20000 units, splits 50 units\n");
    gettimeofday(&start, NULL);
    Test3(target, arr, arrSize);
    gettimeofday(&end, NULL);
    timeE[i] = (double)(((end.tv_sec - start.tv_sec) * 1000000) + end.tv_usec) - (start.tv_usec);
    printf("Test E time: %f\n", timeE[i]);

    //Test F
    printf("Test F: Array 5000 units, splits 50 units\n");
    gettimeofday(&start, NULL);
    Test3(target, arr, arrSize);
    gettimeofday(&end, NULL);
    timeF[i] = (double)(((end.tv_sec - start.tv_sec) * 1000000) + end.tv_usec) - (start.tv_usec);
    printf("Test F time: %f\n", timeF[i]);
  }

  double holdA = timeA[1];
  double holdB = timeB[1];
  double holdC = timeC[1];
  double holdD = timeD[1];
  double holdE = timeE[1];
  double holdF = timeF[1];

  for (i = 0; i < 150; i++){
    if (i == 1){
      minA = timeA[i];
      minB = timeB[i];
      minC = timeC[i];
      minD = timeD[i];
      minE = timeE[i];
      minF = timeF[i];

      maxA = timeA[i];
      maxB = timeB[i];
      maxC = timeC[i];
      maxD = timeD[i];
      maxE = timeE[i];
      maxF = timeF[i];
    }
    else{
      minA = minTime(minA, timeA[i]);
      minB = minTime(minB, timeB[i]);
      minC = minTime(minC, timeC[i]);
      minD = minTime(minD, timeD[i]);
      minE = minTime(minE, timeE[i]);
      minF = minTime(minF, timeE[i]);

      maxA = maxTime(maxA, timeA[i]);
      maxB = maxTime(maxB, timeB[i]);
      maxC = maxTime(maxC, timeC[i]);
      maxD = maxTime(maxD, timeD[i]);
      maxE = maxTime(maxE, timeE[i]);
    }
    timeA[1] = timeA[1] + timeA[i];
    timeB[1] = timeB[1] + timeB[i];
    timeC[1] = timeC[1] + timeC[i];
    timeD[1] = timeD[1] + timeD[i];
    timeE[1] = timeE[1] + timeE[i];
    timeF[1] = timeF[1] + timeF[i];
  }
  
  meanA = timeA[1]/150;
  meanB = timeB[1]/150;
  meanC = timeC[1]/150;
  meanD = timeD[1]/150;
  meanE = timeE[1]/150;
  meanF = timeF[1]/150;

  timeA[1] = holdA;
  timeB[1] = holdB;
  timeC[1] = holdC;
  timeD[1] = holdD;
  timeE[1] = holdE;
  timeF[1] = holdF;
  
  for (i = 0; i < 150; i++){
    standA += pow(timeA[i] - meanA, 2);
    standB += pow(timeB[i] - meanB, 2);
    standC += pow(timeC[i] - meanC, 2);
    standD += pow(timeD[i] - meanD, 2);
    standE += pow(timeE[i] - meanE, 2);
    standF += pow(timeF[i] - meanF, 2);
  }

  standA = sqrt(standA/150);
  standB = sqrt(standB/150);
  standC = sqrt(standC/150);
  standD = sqrt(standD/150);
  standE = sqrt(standE/150);
  standF = sqrt(standF/150);

  printf("TestA Average: %f, SD: %f, Min: %f, Max: %f\n", meanA, standA, minA, maxA);
  printf("TestB Average: %f, SD: %f, Min: %f, Max: %f\n", meanB, standB, minB, maxB);
  printf("TestC Average: %f, SD: %f, Min: %f, Max: %f\n", meanC, standC, minC, maxC);
  printf("TestD Average: %f, SD: %f, Min: %f, Max: %f\n", meanD, standD, minD, maxD);
  printf("TestE Average: %f, SD: %f, Min: %f, Max: %f\n", meanE, standE, minE, maxE);
  printf("TestF Average: %f, SD: %f, Min: %f, Max: %f\n", meanF, standF, minF, maxF);

  return 0;
}

//Checks array against thread size of 250
void Test(int target, int* arr, int arrSize){
  search(arr, target, 250, arrSize);
  newArr(arr, target, arrSize); 
}

//checks array against thread size of 100
void Test2(int target, int* arr, int arrSize){
  search(arr, target, 100, arrSize);
  newArr(arr, target, arrSize);
}

//checks array against thread size of 50
void Test3(int target, int* arr, int arrSize){
  search (arr, target, 50, arrSize);
  newArr(arr, target, arrSize);
}

void randArray(int* array, int arrSize){
  int i;
  
  for (i = 0; i < arrSize; i++){
    array[i] = i;
  }

  srand(time(0));
  
  int flips = (arrSize / 4) * 3;

  for (i = 0; i < flips; i++){
    int a = rand() % arrSize;
    int b = rand() % arrSize;
    
    int temp = array[a];
    array[a] = array[b];
    array[b] = temp;
  }
}

void newArr(int* array, int target, int arrSize){
  int i;
  int valDex;
  for (i = 0; i < arrSize; i++){
    if (array[i] == target){
      valDex = i;
    }
  }

  int a = rand() % arrSize;
  int temp = array[valDex];
  array[valDex] = array[a];
  array[a] = temp;
}
