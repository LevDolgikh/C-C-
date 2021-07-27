// ��������� ��������� ��������� ������ ����������, ������� ����� ����������.
// �� ����� �, �� ������� � ��������� � C++ :).

#define _XOPEN_SOURCE 600
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>    /* GetTickCount */
#include <sys/time.h>   /* gettimeofday, timeval */
#include  <omp.h>
#include <assert.h>
#include <pthread.h>

// Macro for swapping two values.
#define SWAP(x,y) do {\
    __typeof__(x) tmp = x;\
    x = y;\
    y = tmp;\
} while(0)

int array[10000000];


/****************** ����� ��� ����� http://www.cs.swan.ac.uk/~csdavec/HPC/sort.c.html ������ *********************/

/**
 * Partition the array.  Takes the index of the pivot point as the pivot
 * argument.  Puts all of the values lower than this point into the first part
 * of the array and returns the new location of the pivot point.
 */
int partition(int *array, int left, int right, int pivot)
{
    int pivotValue = array[pivot];
    SWAP(array[pivot], array[right]);
    int storeIndex = left;
    for (int i=left ; i<right ; i++)
    {
        if (array[i] <= pivotValue)
        {
            SWAP(array[i], array[storeIndex]);
            storeIndex++;
        }
    }
    SWAP(array[storeIndex], array[right]);
    return storeIndex;
}
/**
 * Dumps the array.  Use this if you want to see intermediate steps
 */
void dump(int *array, int size)
{
    for (int i=0 ; i<size ; i++)
    {
        printf("[%d] %d\n", i, array[i]);
    }
}

/**
 * Serial Quicksort implementation.
 */
void quicksort(int *array, int left, int right)
{
     if (right > left)
     {
        int pivotIndex = left + (right - left)/2;
        pivotIndex = partition(array, left, right, pivotIndex);
        quicksort(array, left, pivotIndex-1);
        quicksort(array, pivotIndex+1, right);
     }
}
/**
 * Structure containing the arguments to the parallel_quicksort function.  Used
 * when starting it in a new thread, because pthread_create() can only pass one
 * (pointer) argument.
 */
struct qsort_starter
{
    int *array;
    int left;
    int right;
    int depth;
};

void parallel_quicksort(int *array, int left, int right, int depth);

/**
 * Thread trampoline that extracts the arguments from a qsort_starter structure
 * and calls parallel_quicksort.
 */
void* quicksort_thread(void *init)
{
    struct qsort_starter *start = (struct qsort_starter *)init;
    parallel_quicksort(start->array, start->left, start->right, start->depth);
    return NULL;
}
/**
 * Parallel version of the quicksort function.  Takes an extra parameter:
 * depth.  This indicates the number of recursive calls that should be run in
 * parallel.  The total number of threads will be 2^depth.  If this is 0, this
 * function is equivalent to the serial quicksort.
 */
void parallel_quicksort(int *array, int left, int right, int depth)
{
    if (right > left)
    {
        int pivotIndex = left + (right - left)/2;
        pivotIndex = partition(array, left, right, pivotIndex);
        // Either do the parallel or serial quicksort, depending on the depth
        // specified.
        if (depth-- > 0)
        {
            // Create the thread for the first recursive call
            struct qsort_starter arg = {array, left, pivotIndex-1, depth};
            pthread_t thread;
            int ret = pthread_create(&thread, NULL, quicksort_thread, &arg);
            assert((ret == 0) && "Thread creation failed");
            // Perform the second recursive call in this thread
            parallel_quicksort(array, pivotIndex+1, right, depth);
            // Wait for the first call to finish.
            pthread_join(thread, NULL);
        }
        else
        {
            quicksort(array, left, pivotIndex-1);
            quicksort(array, pivotIndex+1, right);
        }
    }
}

/****************** ����� ��� *********************/


// ��������� ������� ����������
int getSortType (void){
	int sortType;
   	printf("������� �����, � ����������� �� � ������� ����������(�����):\n");
   	if(scanf("%u",&sortType)!=1){												// ���������� sortType � �������� ����� �� �� ��������
    	printf("������� �������� ������\n");									// ������� ��������� �� ������, ���� ������� �� �����
    }
	return sortType;							            					// ���������� ��� ���������
}

// ���������� �� ������� ����������
void sortInfo(void){
	printf("1 - C��������� ������� ���������\n");
	printf("2 - ���������� ������� (Selection sort)\n");
	printf("3 - ���������� �������\n");
	printf("4 - ���������� ������� �����\n");
	printf("5 - ���������� ������� �����\n");
}

// ����������. ����� ���������
void bubblesort(int *a, unsigned long int n)
{	
  	int i, j; 						// ���������� �����

	for(i = 0 ; i < n - 1; i++) {
		   // ���������� ��� �������� ��������.
		for(j = 0 ; j < n - i - 1 ; j++) {
			if(a[j] > a[j+1]) {
				// ���� ��� ���� � ������������ �������, ��
				//  ������ �� �������.
				int tmp = a[j]; a[j] = a[j+1] ; a[j+1] = tmp;
			}
		}
	}
}

void swap(int *i, int *j) {
   int t = *i;
   *i = *j;
   *j = t;
}


// ��������� ������� ���������� ������� ������ 3. ����� QueryPerformanceCounter()
double getTimeWithQP(int *array,unsigned long int j,int sortType){

    __int64 start,end,tps;          // ���������� ��� ��������� �������
    double timeInMSeconds;          // ��� �������� ������� � ������ double

    //// ������ 1. ����� ���������
    if (sortType==1){
        QueryPerformanceFrequency((LARGE_INTEGER *)&tps);
        QueryPerformanceCounter((LARGE_INTEGER *)&start);
		parallel_quicksort(array,0,j,0);                                      // ���������� ���������
		QueryPerformanceCounter((LARGE_INTEGER *)&end);                     // �������� ������� �� � ����� ����������
        printf("    ���������������� ���������� ��������� �� %f ����������\n",((double)(end-start)/tps)*1000);
	}
    timeInMSeconds = (double)(end-start)/tps*1000;              // ����� � ������������
    return timeInMSeconds;                                      // �������� �������
}

// ��������� ����� ����� ��� ������ ���������� ����������
void printResult(int sortType, unsigned long int length, double ms){

        FILE *file;	                            // ����������, ���������� ������ �� ����
        const char *file_name;                  // ����������, ���������� ������ �� �������� �����.

        // ��� ������������ ����� � ���������� �� ������ ����������
        if (sortType == 1){
            file_name="UsualSort.txt";
        }
        else if (sortType == 2){
            file_name="PallalelSort.txt";
        }

        file=fopen(file_name,"a");                          // �������� ��� �������� ����� ��� ������
        fprintf(file, "%d %f\n" ,length,ms);				// ������ ����������� �������
        fclose(file);		                                // �������� �����

}

void oneSortCycle(unsigned long int j){

	//  ������� ����������
	int i = 1,t=1;				// ������� ���������� ������
	unsigned long int d;        // ������� ���������
	int sortType;				// ������ ����������
	FILE *file;					// ����
	double time;                // ���������� �������
	char *file_name = "1.txt";	// ��� �����

    // ���������� � ��������� �������;


	file=fopen(file_name,"r");
	// ���������� �������
	for(d = 0; d < j; d++){
		if(fscanf(file, "%d", &array[d]) == EOF){
			break;
		}
	}
	fclose(file);

	printf("\n���������� �������. ���������� ��������� �������=%u, ����� ����� t=%u\n",j,t);
	time = getTimeWithQP(array,j,t);

	// �������� ������ ������
	fclose(file);

	// �������� ���������
	printResult(t, j,time);
	
    for (int i=0 ; i<j ; i++)
    {
    	if (array[i]<=array[i+1]){
		}
		else printf("������ �� ������������");
    }
    printf("������ ������������");
}

int main (void){

	//	������������� ������� ���� � �������
	setlocale(LC_ALL, "rus");

	// ������ ����������
	unsigned long int j;
	int i=1;
	int d=1;

    // �������� ������ ������
    for( i = 1; i <= 15; i++){
		switch (i){
		case 1: j=0; break;
		case 2: j=10; break;
		case 3: j=100; break;
		case 4: j=250; break;
		case 5: j=500; break;
		case 6: j=1000; break;
		case 7: j=2500; break;
		case 8: j=5000; break;
		case 9: j=10000; break;
		case 10: j=25000; break;
		case 11: j=50000; break;
		case 12: j=100000; break;
		case 13: j=250000; break;
		case 14: j=500000; break;
		case 15: j=1000000; break;
		}
		oneSortCycle(j);
		
    }
    return 0;
}
