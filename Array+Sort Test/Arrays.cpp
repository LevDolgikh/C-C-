// Программа для создания массивов случайных чисел, с последующим помещением массивов в текстовые файлы с именами 1.txt и т.д.
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int main(void) 	
{
	//	Устанавливаем русский язык в консоле
	setlocale(LC_ALL, "rus");
	
	// Создаем переменные
	int max; 					// Максимальное значение чисел массива
	int min; 					// Минимальное значение чисел массива
	int length; 				// Длина массива
    int amountOfArrays; 		// Число массивов
    srand(time(NULL));			// Для более эффективной генерации случайных чисел

   	//Считываем переменные с клавиатуры
   	printf("После ввода числа для продолжения нажимайте Enter!\n");
   	printf("Введите минимальное значение чисел в массивe(целое число):\n");
   	scanf("%d",&min); 															// Считывание min
   	printf("Введите максимальное значение чисел в массиве(целое число):\n");
   	scanf("%d",&max); 															// Считывание max
   	printf("Введите длину массива(целое чисор):\n");
   	scanf("%u",&length); 														// Считывание length
   	printf("Введите количество массивов(челое число):\n");
   	scanf("%u",&amountOfArrays); 												// Считывание amountOfArrays
   	printf("Полученные данные: диапозон значений от %d до %d, длина массивов %u, количество массивов %u.\n",min,max,length,amountOfArrays);
   	
   	// Создание файлов
   	int i,j,k; 										// Переменные цикла
   	
    for (i=0; i<amountOfArrays;i++){				// Цикл для создания файлов формата .txt
	
		int array[length];							// Задание массива cо числами числами размера legth
		
		// Заполнение массива
		for (j=0;j<length;j++){						// Цикл для заполнения массива случайными числами
			int randomNumber = min+ rand()% max;	// Генерация случайного числа
			array[j]=randomNumber;					// Заполнение массива
		}
		
		// Создание файлов вида i.txt
	 	FILE *file;											// Переменная типа File
	 	char file_name[30];									// Строка для генерации имени файла
	 	itoa(i+1,file_name,20);								// Преобразование переменной iв строку
		char additionalString[100] = {'.','t','x','t'};		// Вспомогательная текстовая переменная									
		strcat(file_name,additionalString);					// Обьединение строк filename и additionalString		
	 	file = fopen(file_name,"wb");						// Открытие,создание, отчистка файла для записи	
	 	
	 	// Сама запись чисел
	 	for (k=0;k<length;k++){	
	 		fprintf(file, "%d " , array[k]);				// Печать полученного массива
	 	}
	 	
	 	// Закрытие потока
	 	fclose(file);	
	}
	printf("Файлы успешно созданны :)");
    return 0;
}
