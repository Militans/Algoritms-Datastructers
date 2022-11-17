/*
 * testGen.cpp
 * Дата создания: 26.09.2019
 * Автор: Евдокимов С.А.
 * Генератор случайных последовательностей целых чисел.
 */

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>


int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "ru");

	if(argc == 1) {
		// печать командной строки
		printf("Генератор случайных последовательностей целых чисел\n");
		printf("Разработчик Евдокимов С.А.\n");
		printf("Командная строка: <имя программы> <число данных>\n");
		printf("Файл данных (d<число данных>.txt) содержит челые числа, разделенные пробелом или Enter\n");
		return 0;
	}

	int nCount = atoi(argv[1]);
	printf("nCount = %d\n", nCount);

	char sPath[12] = {0};
	sprintf(sPath, "d%d.txt", nCount);
	printf("Массив целых чисел записывается в файл \"%s\"\n", sPath);

	FILE* fp = fopen(sPath, "w");
	if(fp == NULL) {
		printf("Ошибка открытия файла для записи \"%s\"\n", sPath);
		return 1; 
	}

	// [100, 1000), [1000, 10000)
	int n0 = (nCount <= 500 ? 100 : 1000);
	int nm = (nCount <= 500 ? 900 : 9000);

	srand(nCount);
	for (int i = 0; i < nCount; ++i) {
		int ir = (int)((double)rand()/RAND_MAX*nm) + n0;
		fprintf(fp, "%d\n", ir);
	}

	fclose(fp);
	return 0;
}

