// Программа тестирует различные методы сортировки, замеряя время выполнения.
// на языке С, но немного в перемешку с C++ :).

#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>    /* GetTickCount */
#include <sys/time.h>   /* gettimeofday, timeval */

int array[10000000];

// Получение способа сортировки
int getSortType (void){
	int sortType;
   	printf("Введите число, в соотвествии со с методом сортировки(целое):\n");
   	if(scanf("%u",&sortType)!=1){												// Считывание sortType и проверям число ли мы получили
    	printf("Введены неверные данные\n");									// Выводим результат об ошибке, если введено не число
    }
	return sortType;							            					// Возвращаем как результат
}

// Информация по методам сортировки
void sortInfo(void){
	printf("1 - Cортировка методом «пузырька»\n");
	printf("2 - Сортировка выбором (Selection sort)\n");
	printf("3 - Сортировка деревом\n");
	printf("4 - Сортировка методом Шелла\n");
	printf("5 - Сортировка методом Хоора\n");
}

// Сортировка. Метод «пузырька»
void bubblesort(int *a, unsigned long int n)
{	
  	int i, j; 						// Переменные цикла

	for(i = 0 ; i < n - 1; i++) {
		   // сравниваем два соседних элемента.
		for(j = 0 ; j < n - i - 1 ; j++) {
			if(a[j] > a[j+1]) {
				// если они идут в неправильном порядке, то
				//  меняем их местами.
				int tmp = a[j]; a[j] = a[j+1] ; a[j+1] = tmp;
			}
		}
	}
}

// Сортировка Выбором
void choicesSort(int* array, unsigned long int n){
    for (int i = 0; i < n-1; i++){
    	int min = i; 	    						// Переменная с индексом минимального элоемента
        for (int j = i + 1; j < n; j++){
            if (array[j] < array[min]){
				min = j;							// Поиск минимального элемента в массиве, нашли индекс, записали
            }
        }
        // Ставим мин. элемент на нужное место в массиве
        int temp = array[i];
        array[i] = array[min];
        array[min] = temp;
    }
}

// Сортировка деревом ( много кода очень) Начало //////////////////////////
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
    for (i = (array_size / 2)-1; i >= 0; i--)                   // i изменяется от N/2 до 0
        siftDown(numbers, i, array_size);
    for (i = array_size-1; i >= 1; i--) {
        temp = numbers[0];
        numbers[0] = numbers[i];
        numbers[i] = temp;
        siftDown(numbers, 0, i-1);
    }
}
// Сортировка Деревом Конец ///////////////////////////////////////////

// Cортировка м. Шелла
void shellSort(int v[], int n)
{
    int gap; // Расстояние между элементами
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

// Сортировка м. Хоара
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

// Получение времени выполнения функции способ 1. Через clock()
double getTimeWithClock_t(int *array,unsigned long int j,int sortType){

    clock_t time;                       // Переменная времени
    double timeInSeconds;               // Вспомогательная переменная для преобразования в милисекунды формата double

    //// Способ 1. Метод «пузырька»
    if (sortType==1){
        time = clock();                         // Получение времени
		bubblesort(array,j);                    // Сортировка пузырьком
		time = clock() - time;                  // Разность времени до и после сортировки
        printf("    Сортировка завершена за %f милисекунд\n",(double) time/CLOCKS_PER_SEC);
	}
	//// Способ 2. Сортировка выбором
	else if (sortType==2){
	    time = clock();                         // Получение времени
        choicesSort(array,j);                   // Сортировка Выбором
        time = clock() - time;                  // Разность времени до и после сортировки
        printf("    Сортировка завершена за %f милисекунд\n",(double) time/CLOCKS_PER_SEC);
	}
	//// Способ 3. Cортировка деревом
	else if (sortType==3){
	    time = clock();                         // Получение времени
        heapSort(array,j);                      // Сортировка деревом
        time = clock() - time;                  // Разность времени до и после сортировки
        printf("    Сортировка завершена за %f милисекунд\n",(double) time/CLOCKS_PER_SEC);
    }
	//// Способ 4. Cортировка м.Шелла
	else if (sortType==4){
        time = clock();                         // Получение времени
        shellSort(array,j);                     // Сортировка м.Шелла
        time = clock() - time;                  // Разность времени до и после сортировки
        printf("    Сортировка завершена за %f милисекунд\n",(double) time/CLOCKS_PER_SEC);
	}
	//// Способ 5. Cортировка м.Хоора
	else if (sortType==5){
        time = clock();                         // Получение времени
        QuickSort(array,0,j-1);                 // Сортировка м.Шелла
        time = clock() - time;                  // Разность времени до и после сортировки
        printf("    Сортировка завершена за %f милисекунд\n",(double) time/CLOCKS_PER_SEC);
	}

	timeInSeconds = (double) time/CLOCKS_PER_SEC; // преобразование к секундам
	return timeInSeconds; // Возврат времени в секундах

}

// Получение времени выполнения функции способ 2. Через GetTickCount()
long getTimeWithGetTickCount(int *array,unsigned long int j,int sortType){

    long time;                                  // Переменная времени

    //// Способ 1. Метод «пузырька»
    if (sortType==1){
        time = GetTickCount();                 // Получение времени
		bubblesort(array,j);                   // Сортировка пузырьком
		time = GetTickCount() - time;          // Разность времени до и после сортировки
        printf("    Сортировка завершена за %ld милисекунд\n",time);
	}
		//// Способ 2. Сортировка выбором
    else if (sortType==2){
        time = GetTickCount();                 // Получение времени
        choicesSort(array,j);                  // Сортировка Выбором
        time = GetTickCount() - time;          // Разность времени до и после сортировки
        printf("    Сортировка завершена за %ld милисекунд\n",time);
    }
    //// Способ 3. Cортировка деревом
    else if (sortType==3){
        time = GetTickCount();                 // Получение времени
        heapSort(array,j);                     // Сортировка деревом
        time = GetTickCount() - time;          // Разность времени до и после сортировки
        printf("    Сортировка завершена за %ld милисекунд\n",time);
    }
    //// Способ 4. Cортировка м.Шелла
    else if (sortType==4){
        time = GetTickCount();                 // Получение времени
        shellSort(array,j);                    // Сортировка м.Шелла
        time = GetTickCount() - time;          // Разность времени до и после сортировки
        printf("    Сортировка завершена за %ld милисекунд\n",time);
    }
    //// Способ 5. Cортировка м.Хоора
    else if (sortType==5){
        time = GetTickCount();                 // Получение времени
        QuickSort(array,0,j-1);                // Сортировка м.Шелла
        time = GetTickCount() - time;          // Разность времени до и после сортировки
        printf("    Сортировка завершена за %ld милисекунд\n",time);
    }

    return time;                                // Возврат времени в милисукундах

}

// Получение времени выполнения функции способ 3. Через QueryPerformanceCounter()
double getTimeWithQP(int *array,unsigned long int j,int sortType){

    __int64 start,end,tps;          // Переменные для подстчета времени
    double timeInMSeconds;          // Для перевода времени в формат double

    //// Способ 1. Метод «пузырька»
    if (sortType==1){
        QueryPerformanceFrequency((LARGE_INTEGER *)&tps);
        QueryPerformanceCounter((LARGE_INTEGER *)&start);
		bubblesort(array,j);                                                // Сортировка пузырьком
		QueryPerformanceCounter((LARGE_INTEGER *)&end);                     // Разность времени до и после сортировки
        printf("    Сортировка завершена за %f милисекунд\n",((double)(end-start)/tps)*1000);
	}
		//// Способ 2. Сортировка выбором
    else if (sortType==2){
        QueryPerformanceFrequency((LARGE_INTEGER *)&tps);
        QueryPerformanceCounter((LARGE_INTEGER *)&start);                   // Получение времени
        choicesSort(array,j);                                               // Сортировка Выбором
        QueryPerformanceCounter((LARGE_INTEGER *)&end);                     // Разность времени до и после сортировки
        printf("    Сортировка завершена за %f милисекунд\n",((double)(end-start)/tps)*1000);
    }
    //// Способ 3. Cортировка деревом
    else if (sortType==3){
        QueryPerformanceFrequency((LARGE_INTEGER *)&tps);
        QueryPerformanceCounter((LARGE_INTEGER *)&start);                 // Получение времени
        heapSort(array,j);                                                // Сортировка деревом
        QueryPerformanceCounter((LARGE_INTEGER *)&end);                   // Разность времени до и после сортировки
        printf("    Сортировка завершена за %f милисекунд\n",((double)(end-start)/tps)*1000);
    }
    //// Способ 4. Cортировка м.Шелла
    else if (sortType==4){
        QueryPerformanceFrequency((LARGE_INTEGER *)&tps);
        QueryPerformanceCounter((LARGE_INTEGER *)&start);                 // Получение времени
        shellSort(array,j);                                               // Сортировка м.Шелла
        QueryPerformanceCounter((LARGE_INTEGER *)&end);                   // Разность времени до и после сортировки
        printf("    Сортировка завершена за %f милисекунд\n",((double)(end-start)/tps)*1000);
    }
    //// Способ 5. Cортировка м.Хоора
    else if (sortType==5){
        QueryPerformanceFrequency((LARGE_INTEGER *)&tps);
        QueryPerformanceCounter((LARGE_INTEGER *)&start);                // Получение времени
        QuickSort(array,0,j-1);                                          // Сортировка м.Шелла
        QueryPerformanceCounter((LARGE_INTEGER *)&end);                  // Разность времени до и после сортировки
        printf("    Сортировка завершена за %f милисекунд\n",((double)(end-start)/tps)*1000);
    }

    timeInMSeconds = (double)(end-start)/tps*1000;              // Время в милисекундах
    return timeInMSeconds;                                      // Врозврат времени

}

// Получение имени файла для печати результата сортировки
void printResult(int sortType, unsigned long int length, double ms){

        FILE *file;	                            // Переменная, содержащая ссылку на файл
        const char *file_name;                  // Переменная, содержащая ссылку на название файла.

        // Имя сойзадаемого файла в зависимоси от метода сортировки
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

        if (file == NULL){                                      // Проверка на открытие файла
            printf("Ошибка открытия и/или создания файла");     // Вывод сообщение об ошибке
        }
        else {
            file=fopen(file_name,"a");                          // Открытие или создание файла для записи
            fprintf(file, "%d %f\n" ,length,ms);				// Печать полученного массива
            fclose(file);		                                // Закрытие файла
		}
}

void oneSortCycle(unsigned long int j){

	//  Создаем переменные
	int i = 1,t=1;				// Счетчик количества файлов
	unsigned long int d;        // Счетчик диапазона
	int sortType;				// Способ сортировки
	FILE *file;					// Файл
	double time;                // Переменная времени

	// Основное тело программы, в котором происходит считывание и обработка информации.
	while (true){

		// Переменные внутри цикла
		char file_name[20];									// Строка для генерации имени файла
	 	itoa(i,file_name,10);								// Преобразование переменной iв строку
		char additionalString[5] = {'.','t','x','t'};		// Вспомогательная текстовая переменная
		strcat(file_name,additionalString);					// Обьединение строк filename и additionalString

		// Выход из внешнего цикла while, предназначенного для считывание файлов
		file=fopen(file_name,"r");
		if (file==NULL){                                    // Проверка на наличие файлов нужного типа
			i = i - 1;										// Переменная, содержащая кол-во найденных файлов
			break;                                          // Выход из цикла для поиска массивов
		}
        fclose(file);

        // Сортировка и получение времени;
        for ( t = 1; t <= 5; t++){

            file=fopen(file_name,"r");
            // Заполнение массива
            for(d = 0; d < j; d++){
                if(fscanf(file, "%d", &array[d]) == EOF){
                    break;
                }
            }
            fclose(file);

        	printf("Сортировка массива. Количество элементов массива=%u, метод номер t=%u\n",j,t);
    	    time = getTimeWithQP(array,j,t);

    	    // Закрытие потока чтения
    	    fclose(file);
    	    
    	    // Печатаем результат
			printResult(t, j,time);
    	}

        // Увеличивает счетчик количества файлов
		i++;
	}

}

int main (void){

	//	Устанавливаем русский язык в консоле
	setlocale(LC_ALL, "rus");

	// Вводим переменные
	unsigned long int j;
	int i=1;
	int t=1;

    // Получаем нужные данные
    for( j = 10; j <= 25000; j=i*100){
    	oneSortCycle(j);
    	i=t+2+i;
    	t=0;
    }
    return 0;
}
