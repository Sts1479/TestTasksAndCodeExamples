/*
 ============================================================================
 Name        : example3_1.c
 Author      : Me
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

void* LinearSearch(void* Array, size_t ArraySize, void* SearchElemVal, size_t SizeOfElem)
{
	uintptr_t ptr = (uintptr_t)Array; // устанавливаем указатель на первое значение в массиве
	while (ptr < (uintptr_t)Array + SizeOfElem * ArraySize) //перебираем все элементы
	{
		if (0 == memcmp(SearchElemVal, (void*)ptr, ArraySize)) //если искомый элемент найден..
		{
			return (void*)ptr; //...то возвращаем указатель на него
		}
		ptr += SizeOfElem; //..иначе продолжаем искать
	}
	return NULL; //..если элемент не найден - возвращаем NULL
}

double DoubleArray[8] = {-1, -10, 1.3, 100.111, 22, 33.22, 40.5, -50.5 };


int main(void)
{
	double ElememtVal = -10;
	size_t ArrSize = sizeof(DoubleArray)/sizeof(DoubleArray[0]);
	if (LinearSearch(DoubleArray, ArrSize, &ElememtVal, sizeof(ElememtVal)) == NULL)
	{
		printf("The value isn't found");
	}
	else
	{
		printf("The value is found");
	}
	return 0;
}
