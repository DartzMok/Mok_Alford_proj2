#include <stdio.h>
#include <stdlib.h>

//Global variable that holds the sum of all grades inputted
double gradeSum = 0;

//Global variable the counts the number of grades inputted
int size = 0;

//Gloabal variable that temporarily holds the grade to be inputted
double temp;

//Global pointer that points to the first element in an array
double *ptr;

//Global variable that counts the number of times memory was allocated
int increasedSize = 0;

//Global variable that counts the number of bytes allocated 
int byteAllocs = 0;

//Global variable that counts the number of bytes freed
int byteFreed = 0;

//Global variable that counts the total bytes allocated
int totalAllocs = 0;

//Global variable that counts the number of alloctions to the heap
int allocs = 0;

//Global variable that counts the number of frees from the heap
int frees = 0;

/*
Method that calculates the average of all grades inputted
into the program then outputs whether or not each grade is
less than or greater than the average
*/
void calculateAverage();

/*
Method that populates the array with the inputted grades and
calls a method to dynamically allocate memory as needed
*/
int populateArray(int index);

/*
Method that dynamically allocates memory for the array by creating 
a new array and copying the value of the old array over to the new
*/
void dynamicAllocation(int index);

int main(int argc, char ** argv){
  printf("Enter a list of grades below where each grade is serparated by a newline character.\n");
  printf("After the last grade is entered, enter a negative value to end the list.\n");
  int index = 0;

  while(populateArray(index) > 0){
    index++;
  }
  for(int i = 0; i < size; i++){
    printf("%lf\n", *(ptr+i));
  }

  if(size != 0){
    calculateAverage();
  }
  else{
    printf("The average of 0 grades is %lf.\n", 0.0);
  }
  printf("total heap usage: %d allocs, %d frees, %d bytes allocated\n", allocs, frees, totalAllocs);
  return 0;
}

int populateArray(int index){
  scanf("%lf",&temp);

  if(temp < 0){
    return -1;
  }
  else{
    size++;
    if(size == 1){
      ptr = (double *)malloc(sizeof(double)*5);
      byteAllocs = 5 * sizeof(double);
      totalAllocs += byteAllocs;
      printf("Allocated %d bytes to the heap at %p.\n", byteAllocs, (void*)ptr);
      increasedSize++; allocs++;
    }
    printf("Stored %lf in the heap at %p.\n", temp, (void*)(ptr+index));
    dynamicAllocation(index);
    *(ptr+index) = temp;
    gradeSum += temp;
    return 1;
  }
}

void dynamicAllocation(int index){
  if(size == (5 * increasedSize)){
    printf("Stored %d grades (%d bytes) to the heap at %p.\n", (size), byteAllocs, (void*)ptr);
    printf("Heap at %p is full.\n", (void*)ptr);
    allocs++;
    byteAllocs = allocs * 5 * sizeof(double);
    totalAllocs += byteAllocs;
    increasedSize++;
    double * tempArray = (double *)malloc(sizeof(double)*5*increasedSize);
    for(int i = 0; i < size; i++){
      *(tempArray+i) = *(ptr+i);
    }
    printf("Allocated %d bytes to the heap at %p.\n", byteAllocs, (void*)tempArray);
    printf("Copied %d grades from %p to %p.\n", size, (void*)ptr, (void*)tempArray);
    frees++;
    byteFreed = frees * 5 * sizeof(double);
    printf("Freed %d bytes from the heap at %p.\n", byteFreed, (void*)ptr);
    free(ptr);
    ptr = tempArray;
  }
}

void calculateAverage(){
  double average = gradeSum / size;
  printf("The average of %d grades is %lf\n", size, average);

  for(int i = 0; i < size; i++){
    if(*(ptr + i) >= average){
      printf("%d. The grade of %lf is >= the average.\n", (i+1), *(ptr+i));
    }
    else if(*(ptr + i) < average){
      printf("%d. The grade of %lf is < the average.\n", (i+1), *(ptr+i));
    }
  }

  printf("Freed %d bytes from the heap at %p.\n", byteAllocs, (void*)ptr);
  free(ptr);
  frees++;
}
