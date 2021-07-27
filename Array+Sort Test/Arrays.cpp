// ��������� ��� �������� �������� ��������� �����, � ����������� ���������� �������� � ��������� ����� � ������� 1.txt � �.�.
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int main(void) 	
{
	//	������������� ������� ���� � �������
	setlocale(LC_ALL, "rus");
	
	// ������� ����������
	int max; 					// ������������ �������� ����� �������
	int min; 					// ����������� �������� ����� �������
	int length; 				// ����� �������
    int amountOfArrays; 		// ����� ��������
    srand(time(NULL));			// ��� ����� ����������� ��������� ��������� �����

   	//��������� ���������� � ����������
   	printf("����� ����� ����� ��� ����������� ��������� Enter!\n");
   	printf("������� ����������� �������� ����� � ������e(����� �����):\n");
   	scanf("%d",&min); 															// ���������� min
   	printf("������� ������������ �������� ����� � �������(����� �����):\n");
   	scanf("%d",&max); 															// ���������� max
   	printf("������� ����� �������(����� �����):\n");
   	scanf("%u",&length); 														// ���������� length
   	printf("������� ���������� ��������(����� �����):\n");
   	scanf("%u",&amountOfArrays); 												// ���������� amountOfArrays
   	printf("���������� ������: �������� �������� �� %d �� %d, ����� �������� %u, ���������� �������� %u.\n",min,max,length,amountOfArrays);
   	
   	// �������� ������
   	int i,j,k; 										// ���������� �����
   	
    for (i=0; i<amountOfArrays;i++){				// ���� ��� �������� ������ ������� .txt
	
		int array[length];							// ������� ������� c� ������� ������� ������� legth
		
		// ���������� �������
		for (j=0;j<length;j++){						// ���� ��� ���������� ������� ���������� �������
			int randomNumber = min+ rand()% max;	// ��������� ���������� �����
			array[j]=randomNumber;					// ���������� �������
		}
		
		// �������� ������ ���� i.txt
	 	FILE *file;											// ���������� ���� File
	 	char file_name[30];									// ������ ��� ��������� ����� �����
	 	itoa(i+1,file_name,20);								// �������������� ���������� i� ������
		char additionalString[100] = {'.','t','x','t'};		// ��������������� ��������� ����������									
		strcat(file_name,additionalString);					// ����������� ����� filename � additionalString		
	 	file = fopen(file_name,"wb");						// ��������,��������, �������� ����� ��� ������	
	 	
	 	// ���� ������ �����
	 	for (k=0;k<length;k++){	
	 		fprintf(file, "%d " , array[k]);				// ������ ����������� �������
	 	}
	 	
	 	// �������� ������
	 	fclose(file);	
	}
	printf("����� ������� �������� :)");
    return 0;
}
