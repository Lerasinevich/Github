/// doxygen.cpp : Defines the entry point for the console application.
///

#include "stdafx.h"
#include "stdio.h"
#include "iostream"

using namespace std;


/**
@function Merge
Эта функция сортирует массив в порядке неубывания методом пузырька
@param _mas - указатель на изначальный массив
@param _n - размер массива
**/

int* bubble(int *_mas, int _n)///ввод функции сортировки
{
	for (int i=0; i <(_n-1); i ++)///цикл количества проверок
	{
		for (int j=0; j<(_n-1); j++)///цикл проверки массива на неубывание
		 {
			 if (_mas[j] >_mas[j+1]) ///проверка на убывание
			{
				int tmp = _mas[j]; ///инициализация временной переменной
				 _mas[j] = _mas[j+1];
				_mas[j+1] = tmp;/// смена мест
			}
		}
	}
	return _mas;
}


/**
@function _tmain
Главная функция
@param srgc
@param argv[] 
**/
int _tmain(int argc, _TCHAR* argv[])
{
	int n =15;
	int *mas = new int[n]; 
	for (int i= 0; i<n; i++)
	{
		mas[i] = rand()%100-1;
	}

	mas = bubble(mas, n);
	for (int i= 0; i<n; i++)
	{
		cout << mas[i] << "   ";
	}

	
	return 0;
}





