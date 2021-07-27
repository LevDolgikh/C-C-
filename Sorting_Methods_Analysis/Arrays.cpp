// Программа для создания массивов случайных чисел, с последующим помещением массивов в текстовые файлы с именами 1.txt и т.д.
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// Ввод длины массива
unsigned long int getLengthOfArrays(void){
	unsigned long int length;
   	printf("Введите количество чисел, которое нужно сгенерировать (целое число):\n");
   	if(scanf("%u",&length)!=1){							// Считывание length и проверям число ли мы получили
    	printf("Введены неверные данные");				// Выводим результат об ошибке, если введено не число
    }
	return length;							            // Возвращаем как результат
	
}

int main(void) 	
{
	//	Устанавливаем русский язык в консоле
	setlocale(LC_ALL, "rus");
	
	// Создаем переменные
	unsigned long int length; 					// Длина массива
    int amountOfArrays=10; 				        // Число массивов
    srand(time(NULL));					        // Для более эффективной генерации случайных чисел

   	// Считываем переменные с клавиатуры
	length = getLengthOfArrays();
   	
   	// Создание файлов
   	int i;                          // Переменные малого цикла для создания файлов
   	unsigned long int k;            // Переменные цикла для записи случайных чисел в файл. P.S. 400000000 чисел грузит комп на очень долго :))

    for (i=0; i<amountOfArrays;i++){							// Цикл для создания файлов формата .txt
		
		// Создание файлов вида i.txt
	 	FILE *file;											// Переменная типа File
	 	char file_name[20];									// Строка для генерации имени файла
	 	itoa(i+1,file_name,10);								// Преобразование переменной iв строку
		char additionalString[5] = {'.','t','x','t'};		// Вспомогательная текстовая переменная
		strcat(file_name,additionalString);					// Обьединение строк filename и additionalString		
	 	file = fopen(file_name,"wb");						// Открытие,создание, отчистка файла для записи	
	 	
	 	// Сама запись чисел
	 	for (k=0;k<length;k++){
	 		long long randomNumber = rand()%100000;
	 		fprintf(file, "%d " , randomNumber );			// Печать полученного массива
	 	}
	 	
	 	// Закрытие потока
	 	fclose(file);	
	}
	printf("Файлы успешно созданны :)");
    return 0;
}
