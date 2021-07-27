// ��������� ������ ����� �� ����� � ������
// �� �����  �� ����� �.

#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>

//
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
    for (i = (array_size / 2)-1; i >= 0; i--)
        siftDown(numbers, i, array_size);
    for (i = array_size-1; i >= 1; i--) {
        temp = numbers[0];
        numbers[0] = numbers[i];
        numbers[i] = temp;
        siftDown(numbers, 0, i-1);
    }
}

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

void choicesSort(int* arrayPtr, unsigned long int length_array){
    for (int repeat_counter = 0; repeat_counter < length_array; repeat_counter++){
        int temp = arrayPtr[0]; // ��������� ���������� ��� �������� �������� ������������
        for (int element_counter = repeat_counter + 1; element_counter < length_array; element_counter++){
            if (arrayPtr[repeat_counter] > arrayPtr[element_counter]){
                temp = arrayPtr[repeat_counter];
                arrayPtr[repeat_counter] = arrayPtr[element_counter];
                arrayPtr[element_counter] = temp;
            }
        }
    }
}

// ��������������� ������� ��� ���������� ����� qsort
int cmp(const void *a, const void *b) {
    return *(int*)a - *(int*)b;
}

int main (void){
	
	//	������������� ������� ���� � �������
	setlocale(LC_ALL, "rus");
	
	//  ������� ����������
	int i=1,j,k,t,d;			// ���������� �����
	int sortType;				// ������ ����������
	int end=0;					// ��������������� ���������� ��� ������ �� �����
	int forBreak=0;				// ��� ������ �� ����� for - ���� ����� �� �� ���� ����
	FILE *file;					// ����
	
	//���������� �� ������� ����������
	printf("1 - C��������� ������� ���������\n");
	printf("2 - C��������� ��������� qsort �� ���������� stdlib\n");
	printf("3 - ���������� ��������� (Insertion sort)\n");
	printf("4 - ���������� ������� (Selection sort)\n");
	
	// ��������� ������� ����������
	printf("������� �����, � ����������� �� � ������� ����������(����� �� 1 �� ):\n");
   	scanf("%u",&sortType); 															
	
	printf("����� ������ ��� ����������(������� 1.txt, 2.txt; � ����� � ����������)\n");
	
	while (end!=1){
		
		// ���������� ������ �����
		int array[100];										// ������ � ����������� �������
		char file_name[30];									// ������ ��� ��������� ����� �����
	 	itoa(i,file_name,20);								// �������������� ���������� i� ������
		char additionalString[100] = {'.','t','x','t'};		// ��������������� ��������� ����������									
		strcat(file_name,additionalString);					// ����������� ����� filename � additionalString
		
		// ����� �� �������� ����� while, ���������������� ��� ���������� ������
		file=fopen(file_name,"r");
		if (file==NULL){
			end=1;											// ���������������, ����� �� �����
			i=i-1;											// ����������, ���������� ���-�� ��������� ������
			printf("���������� ������ ���������. ����� ������� %u �����(��)\n",i);
			break;
		}
		
		// ���������� �������
		for(j=0;forBreak!=1; j++){
      		if(fscanf(file, "%d", &array[j]) == EOF){
      			break;
      			forBreak=1;
      		} 
      		printf(" %d, ", array[j]);
    	}
    	
    	fclose(file);					// �������� ������ ������
    	
    	// ���������� �������
    	//// ������ 1. ����� ���������
    	if (sortType==1){
    		for(k = 0 ; k < j-1; k++) { 
       			// ���������� ��� �������� ��������.
       			for(t = 0 ; t < j-k-1 ; t++) {  
           			if(array[t] > array[t+1]) {           
              		// ���� ��� ���� � ������������ �������, ��  
              		//  ������ �� �������. 
              	int tmp = array[t]; array[t] = array[t+1] ; array[t+1] = tmp; 
           			}
        		}
    		}
		}
		//// ������ 2. C��������� ��������� qsort
		else if (sortType==2){
			qsort(array, j, sizeof(int), cmp ); // ���������?? ������ 2-� for
		}
		//// ������ 3. C��������� ��������� 
		else if (sortType==3){
			for(k = 1; k < j; k++){
				int value;
				value = array[k];
		        for (t = k - 1; t >= 0 && array[t] > value; t--){
		            array[t + 1] = array[t];
		        }
				array[t + 1] = value;
		    }
		}
		//// ������ 4. ���������� �������
		else if (sortType==4){
			choicesSort(array,j);
		}
	
		// ����������� �������
		file=fopen(file_name,"w+");
		for (d=0;d<j;d++){	
	 		fprintf(file, "%d " , array[d]);				// ������ ����������� �������
	 	}
		
		i++;				// ����������� ������� ���������� ������
		fclose(file);		// �������� �����
	} 
	
}
