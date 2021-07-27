// ��������� ��� �������� �������� ��������� �����, � ����������� ���������� �������� � ��������� ����� � ������� 1.txt � �.�.
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// ���� ����� �������
unsigned long int getLengthOfArrays(void){
	unsigned long int length;
   	printf("������� ���������� �����, ������� ����� ������������� (����� �����):\n");
   	if(scanf("%u",&length)!=1){							// ���������� length � �������� ����� �� �� ��������
    	printf("������� �������� ������");				// ������� ��������� �� ������, ���� ������� �� �����
    }
	return length;							            // ���������� ��� ���������
	
}

int main(void) 	
{
	//	������������� ������� ���� � �������
	setlocale(LC_ALL, "rus");
	
	// ������� ����������
	unsigned long int length; 					// ����� �������
    int amountOfArrays=10; 				        // ����� ��������
    srand(time(NULL));					        // ��� ����� ����������� ��������� ��������� �����

   	// ��������� ���������� � ����������
	length = getLengthOfArrays();
   	
   	// �������� ������
   	int i;                          // ���������� ������ ����� ��� �������� ������
   	unsigned long int k;            // ���������� ����� ��� ������ ��������� ����� � ����. P.S. 400000000 ����� ������ ���� �� ����� ����� :))

    for (i=0; i<amountOfArrays;i++){							// ���� ��� �������� ������ ������� .txt
		
		// �������� ������ ���� i.txt
	 	FILE *file;											// ���������� ���� File
	 	char file_name[20];									// ������ ��� ��������� ����� �����
	 	itoa(i+1,file_name,10);								// �������������� ���������� i� ������
		char additionalString[5] = {'.','t','x','t'};		// ��������������� ��������� ����������
		strcat(file_name,additionalString);					// ����������� ����� filename � additionalString		
	 	file = fopen(file_name,"wb");						// ��������,��������, �������� ����� ��� ������	
	 	
	 	// ���� ������ �����
	 	for (k=0;k<length;k++){
	 		long long randomNumber = rand()%100000;
	 		fprintf(file, "%d " , randomNumber );			// ������ ����������� �������
	 	}
	 	
	 	// �������� ������
	 	fclose(file);	
	}
	printf("����� ������� �������� :)");
    return 0;
}
