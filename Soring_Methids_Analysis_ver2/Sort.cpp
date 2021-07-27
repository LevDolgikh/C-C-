// ��������� ��������� ��������� ������ ����������, ������� ����� ����������.
// �� ����� �, �� ������� � ��������� � C++ :).

#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>    /* GetTickCount */
#include <sys/time.h>   /* gettimeofday, timeval */

int array[10000000];

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

// ���������� �������
void choicesSort(int* array, unsigned long int n){
    for (int i = 0; i < n-1; i++){
    	int min = i; 	    						// ���������� � �������� ������������ ���������
        for (int j = i + 1; j < n; j++){
            if (array[j] < array[min]){
				min = j;							// ����� ������������ �������� � �������, ����� ������, ��������
            }
        }
        // ������ ���. ������� �� ������ ����� � �������
        int temp = array[i];
        array[i] = array[min];
        array[min] = temp;
    }
}

// ���������� ������� ( ����� ���� �����) ������ //////////////////////////
void siftDown(int *numbers, int root, int bottom) {
    int done, maxChild, temp;
    done = 0;
    while ((root*2 <= bottom) && (!done)) {
        if (root*2 == bottom)
            maxChild = root * 2;
        else if (numbers[root * 2] > numbers[root * 2 + 1])
            maxChild = root * 2;
        else
            maxChild = root * 2 + 1;
        if (numbers[root] < numbers[maxChild]) {
            temp = numbers[root];
            numbers[root] = numbers[maxChild];
            numbers[maxChild] = temp;
            root = maxChild;
        }
        else
            done = 1;
    }
}

void heapSort(int *numbers, unsigned long int array_size) {
    int i, temp;
    for (i = (array_size / 2)-1; i >= 0; i--)                   // i ���������� �� N/2 �� 0
        siftDown(numbers, i, array_size);
    for (i = array_size-1; i >= 1; i--) {
        temp = numbers[0];
        numbers[0] = numbers[i];
        numbers[i] = temp;
        siftDown(numbers, 0, i-1);
    }
}
// ���������� ������� ����� ///////////////////////////////////////////

// C��������� �. �����
void shellSort(int v[], int n)
{
    int gap; // ���������� ����� ����������
    int i,j,temp;

    for(gap = n/2; gap > 0; gap /= 2)
        for(i = gap; i < n; i++){
            for(j = i - gap; j >= 0 && v[j] > v[j + gap]; j -= gap)
            {
                temp = v[j];
                v[j] = v[j + gap];
                v[j + gap] = temp;
            }
        }
}

// ���������� �. �����
void QuickSort ( int A[], int from, int to )
{
    int x, i, j, temp;
    if ( from >= to ) return;
    i = from;
    j = to;
    x = A[(from+to)/2];
    while ( i <= j ) {
        while ( A[i] < x ) i ++;
        while ( A[j] > x ) j --;
        if ( i <= j ) {
            temp = A[i]; A[i] = A[j]; A[j] = temp;
            i ++;
            j --;
        }
    }
    QuickSort ( A, from, j );
    QuickSort ( A, i, to );
}

// ��������� ������� ���������� ������� ������ 1. ����� clock()
double getTimeWithClock_t(int *array,unsigned long int j,int sortType){

    clock_t time;                       // ���������� �������
    double timeInSeconds;               // ��������������� ���������� ��� �������������� � ����������� ������� double

    //// ������ 1. ����� ���������
    if (sortType==1){
        time = clock();                         // ��������� �������
		bubblesort(array,j);                    // ���������� ���������
		time = clock() - time;                  // �������� ������� �� � ����� ����������
        printf("    ���������� ��������� �� %f ����������\n",(double) time/CLOCKS_PER_SEC);
	}
	//// ������ 2. ���������� �������
	else if (sortType==2){
	    time = clock();                         // ��������� �������
        choicesSort(array,j);                   // ���������� �������
        time = clock() - time;                  // �������� ������� �� � ����� ����������
        printf("    ���������� ��������� �� %f ����������\n",(double) time/CLOCKS_PER_SEC);
	}
	//// ������ 3. C��������� �������
	else if (sortType==3){
	    time = clock();                         // ��������� �������
        heapSort(array,j);                      // ���������� �������
        time = clock() - time;                  // �������� ������� �� � ����� ����������
        printf("    ���������� ��������� �� %f ����������\n",(double) time/CLOCKS_PER_SEC);
    }
	//// ������ 4. C��������� �.�����
	else if (sortType==4){
        time = clock();                         // ��������� �������
        shellSort(array,j);                     // ���������� �.�����
        time = clock() - time;                  // �������� ������� �� � ����� ����������
        printf("    ���������� ��������� �� %f ����������\n",(double) time/CLOCKS_PER_SEC);
	}
	//// ������ 5. C��������� �.�����
	else if (sortType==5){
        time = clock();                         // ��������� �������
        QuickSort(array,0,j-1);                 // ���������� �.�����
        time = clock() - time;                  // �������� ������� �� � ����� ����������
        printf("    ���������� ��������� �� %f ����������\n",(double) time/CLOCKS_PER_SEC);
	}

	timeInSeconds = (double) time/CLOCKS_PER_SEC; // �������������� � ��������
	return timeInSeconds; // ������� ������� � ��������

}

// ��������� ������� ���������� ������� ������ 2. ����� GetTickCount()
long getTimeWithGetTickCount(int *array,unsigned long int j,int sortType){

    long time;                                  // ���������� �������

    //// ������ 1. ����� ���������
    if (sortType==1){
        time = GetTickCount();                 // ��������� �������
		bubblesort(array,j);                   // ���������� ���������
		time = GetTickCount() - time;          // �������� ������� �� � ����� ����������
        printf("    ���������� ��������� �� %ld ����������\n",time);
	}
		//// ������ 2. ���������� �������
    else if (sortType==2){
        time = GetTickCount();                 // ��������� �������
        choicesSort(array,j);                  // ���������� �������
        time = GetTickCount() - time;          // �������� ������� �� � ����� ����������
        printf("    ���������� ��������� �� %ld ����������\n",time);
    }
    //// ������ 3. C��������� �������
    else if (sortType==3){
        time = GetTickCount();                 // ��������� �������
        heapSort(array,j);                     // ���������� �������
        time = GetTickCount() - time;          // �������� ������� �� � ����� ����������
        printf("    ���������� ��������� �� %ld ����������\n",time);
    }
    //// ������ 4. C��������� �.�����
    else if (sortType==4){
        time = GetTickCount();                 // ��������� �������
        shellSort(array,j);                    // ���������� �.�����
        time = GetTickCount() - time;          // �������� ������� �� � ����� ����������
        printf("    ���������� ��������� �� %ld ����������\n",time);
    }
    //// ������ 5. C��������� �.�����
    else if (sortType==5){
        time = GetTickCount();                 // ��������� �������
        QuickSort(array,0,j-1);                // ���������� �.�����
        time = GetTickCount() - time;          // �������� ������� �� � ����� ����������
        printf("    ���������� ��������� �� %ld ����������\n",time);
    }

    return time;                                // ������� ������� � ������������

}

// ��������� ������� ���������� ������� ������ 3. ����� QueryPerformanceCounter()
double getTimeWithQP(int *array,unsigned long int j,int sortType){

    __int64 start,end,tps;          // ���������� ��� ��������� �������
    double timeInMSeconds;          // ��� �������� ������� � ������ double

    //// ������ 1. ����� ���������
    if (sortType==1){
        QueryPerformanceFrequency((LARGE_INTEGER *)&tps);
        QueryPerformanceCounter((LARGE_INTEGER *)&start);
		bubblesort(array,j);                                                // ���������� ���������
		QueryPerformanceCounter((LARGE_INTEGER *)&end);                     // �������� ������� �� � ����� ����������
        printf("    ���������� ��������� �� %f ����������\n",((double)(end-start)/tps)*1000);
	}
		//// ������ 2. ���������� �������
    else if (sortType==2){
        QueryPerformanceFrequency((LARGE_INTEGER *)&tps);
        QueryPerformanceCounter((LARGE_INTEGER *)&start);                   // ��������� �������
        choicesSort(array,j);                                               // ���������� �������
        QueryPerformanceCounter((LARGE_INTEGER *)&end);                     // �������� ������� �� � ����� ����������
        printf("    ���������� ��������� �� %f ����������\n",((double)(end-start)/tps)*1000);
    }
    //// ������ 3. C��������� �������
    else if (sortType==3){
        QueryPerformanceFrequency((LARGE_INTEGER *)&tps);
        QueryPerformanceCounter((LARGE_INTEGER *)&start);                 // ��������� �������
        heapSort(array,j);                                                // ���������� �������
        QueryPerformanceCounter((LARGE_INTEGER *)&end);                   // �������� ������� �� � ����� ����������
        printf("    ���������� ��������� �� %f ����������\n",((double)(end-start)/tps)*1000);
    }
    //// ������ 4. C��������� �.�����
    else if (sortType==4){
        QueryPerformanceFrequency((LARGE_INTEGER *)&tps);
        QueryPerformanceCounter((LARGE_INTEGER *)&start);                 // ��������� �������
        shellSort(array,j);                                               // ���������� �.�����
        QueryPerformanceCounter((LARGE_INTEGER *)&end);                   // �������� ������� �� � ����� ����������
        printf("    ���������� ��������� �� %f ����������\n",((double)(end-start)/tps)*1000);
    }
    //// ������ 5. C��������� �.�����
    else if (sortType==5){
        QueryPerformanceFrequency((LARGE_INTEGER *)&tps);
        QueryPerformanceCounter((LARGE_INTEGER *)&start);                // ��������� �������
        QuickSort(array,0,j-1);                                          // ���������� �.�����
        QueryPerformanceCounter((LARGE_INTEGER *)&end);                  // �������� ������� �� � ����� ����������
        printf("    ���������� ��������� �� %f ����������\n",((double)(end-start)/tps)*1000);
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
            file_name="BubbleSort.txt";
        }
        else if (sortType == 2){
            file_name="SelectSort.txt";
        }
        else if (sortType == 3){
            file_name="HeapSort.txt";
        }
        else if (sortType == 4){
            file_name="ShellSort.txt";
        }
        else if (sortType == 5){
            file_name="HoarSort.txt";
        }

        if (file == NULL){                                      // �������� �� �������� �����
            printf("������ �������� �/��� �������� �����");     // ����� ��������� �� ������
        }
        else {
            file=fopen(file_name,"a");                          // �������� ��� �������� ����� ��� ������
            fprintf(file, "%d %f\n" ,length,ms);				// ������ ����������� �������
            fclose(file);		                                // �������� �����
		}
}

void oneSortCycle(unsigned long int j){

	//  ������� ����������
	int i = 1,t=1;				// ������� ���������� ������
	unsigned long int d;        // ������� ���������
	int sortType;				// ������ ����������
	FILE *file;					// ����
	double time;                // ���������� �������

	// �������� ���� ���������, � ������� ���������� ���������� � ��������� ����������.
	while (true){

		// ���������� ������ �����
		char file_name[20];									// ������ ��� ��������� ����� �����
	 	itoa(i,file_name,10);								// �������������� ���������� i� ������
		char additionalString[5] = {'.','t','x','t'};		// ��������������� ��������� ����������
		strcat(file_name,additionalString);					// ����������� ����� filename � additionalString

		// ����� �� �������� ����� while, ���������������� ��� ���������� ������
		file=fopen(file_name,"r");
		if (file==NULL){                                    // �������� �� ������� ������ ������� ����
			i = i - 1;										// ����������, ���������� ���-�� ��������� ������
			break;                                          // ����� �� ����� ��� ������ ��������
		}
        fclose(file);

        // ���������� � ��������� �������;
        for ( t = 1; t <= 5; t++){

            file=fopen(file_name,"r");
            // ���������� �������
            for(d = 0; d < j; d++){
                if(fscanf(file, "%d", &array[d]) == EOF){
                    break;
                }
            }
            fclose(file);

        	printf("���������� �������. ���������� ��������� �������=%u, ����� ����� t=%u\n",j,t);
    	    time = getTimeWithQP(array,j,t);

    	    // �������� ������ ������
    	    fclose(file);
    	    
    	    // �������� ���������
			printResult(t, j,time);
    	}

        // ����������� ������� ���������� ������
		i++;
	}

}

int main (void){

	//	������������� ������� ���� � �������
	setlocale(LC_ALL, "rus");

	// ������ ����������
	unsigned long int j;
	int i=1;
	int t=1;

    // �������� ������ ������
    for( j = 10; j <= 25000; j=i*100){
    	oneSortCycle(j);
    	i=t+2+i;
    	t=0;
    }
    return 0;
}
