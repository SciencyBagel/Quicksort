//Jahir Montes 1001635994
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


// A utility function to print an array of size n

void swap(int* a, int* b)
{
  int t = *a;
  *a = *b;
  *b = t;
}

int partition(int arr[], int low, int high)
{
  #if QSM
  int middle = (high+low)/2;
  swap(&arr[middle], &arr[high]);
  #elif QSRND
  int random = (rand() % (high-low +1)) + low;
  swap(&arr[random], &arr[high]);
  #endif

  int pivot = arr[high];    // pivot
  int i = (low - 1);  // Index of smaller element

  int j;
  for (j = low; j <= high - 1; j++)
  {
    // If current element is smaller than the pivot
    if (arr[j] < pivot)
    {
      i++;    // increment index of smaller element
      swap(&arr[i], &arr[j]);
    }
  }
  swap(&arr[i + 1], &arr[high]);
  return (i + 1);
}

void printArray(int arr[], int n)
{
  int i;
  for (i = 0; i < n; i++)
    printf("%d ", arr[i]);
  printf("\n");
}

void quickSort(int arr[], int low, int high)
{
  if (low < high)
  {
    /* pi is partitioning index, arr[p] is now
    at right place */
    int pi = partition(arr, low, high);

    // Separately sort elements before
    // partition and after partition
    quickSort(arr, low, pi - 1);
    quickSort(arr, pi + 1, high);
  }
}

long readFile(FILE* fp) //reads amount of lines in file minus new line chracter and sets pointer back
{
  fseek(fp, 0, SEEK_SET);

  if (fp == NULL)
  {
    printf("File doesn't exist \n");
    exit(1);
  }

  long counter = 0;
  char fileLine[100];

  //Count how many lines the file has
  while (!feof(fp))
  {
    fgets(fileLine, 20, fp);
    counter++;
  }

  long nlines = counter - 1;//counter - 1 because counter includes the new line character at the end of the file
  printf("\nThere is a total of %ld lines!\n", nlines);

  fseek(fp, 0, SEEK_SET);//set pointer to beginning of FILE

  return nlines;
}

void fillArray(FILE* fp, int* arr)
{
  fseek(fp, 0, SEEK_SET);

  char fileLine[100];
  int conversion = 0;
  long counter = 1;

  while (!feof(fp))
  {
    fgets(fileLine, 20, fp);
    conversion = atoi(fileLine);
    arr[counter - 1] = conversion;
    counter++;
  }

  fseek(fp, 0, SEEK_SET);
}

//driver
int main(int argc, char** argv)
{
  FILE* fp;
  fp = fopen(argv[1], "r");
  int* arr;

  /* SET UP CLOCKS */
  clock_t start, end;
  double ticks = 0;


  long nlines = readFile(fp);//count amount of lines in file minus new line at the end

  ///////////////////////////////////////
  //Printing array before being sorted if compiled as PRINTARRAY
  ///////////////////////////////////////

  #ifdef PRINTARRAY
  arr = (int*)malloc(nlines * sizeof(int));
  printf("\nUnsorted Array:\n");
  fillArray(fp, arr);
  printArray(arr, nlines);
  free(arr);
  #endif
  ///////////////////////////////////////

  //PREPARE FOR QUICK SORT
  int conversion;
  int i;

  long counter = 0;
  counter = atoi(argv[2]);

  ///////////////////////////////////////
  //RUN LOOP QUICKSORT
  ///////////////////////////////////////
  printf("\nQuick Sort\n");

  for(i = 0; i < counter; i++)
  {
    arr = (int*)malloc(nlines * sizeof(int));
    fillArray(fp, arr);
    start = clock();
    quickSort(arr, 0, nlines-1);
    end = clock();
    ticks += (double)(end) - (double)(start);
    free(arr);
  }

  //if copmile "-D PRINTARRAY", print sorted array
  #ifdef PRINTARRAY
  arr = (int*)malloc(nlines * sizeof(int));
  fillArray(fp,arr);

  printf("\n");

  quickSort(arr, 0, nlines-1);
  printArray(arr, nlines);
  free(arr);
  #endif

  ///////////////////////////////////////

  //print ticks
  printf("\nNet Ticks: %f\n", ticks);
  printf("\nAverage Ticks: %f\n", ticks / (double)counter);

  fseek(fp, 0, SEEK_SET);//set pointer to beginning of FILE
  fclose(fp);

  return 0;
}
