/// insertion.cpp : Defines the entry point for the console application.
///

#include "stdafx.h"
#include "stdio.h"
#include "iostream"

using namespace std;

/**
@function Merge
Эта функция сливает два массива в один в порядке неубывания (метод слияния) 
@param A - указатель на изначальный массив
@param first - начало левой части
@param last - начало левой части
**/
void Merge(int *A, int first, int last)
{
	int middle; /// инициализация переменной для среднего элемента
	int start;///инициализия переменной для левой части массива
	int final;/// инициализация переменной для правой части массива
	int j; /// инициализация счетчика
	int *mas=new int[100];/// создание временного массива
	middle=(first+last)/2; ///вычисление среднего элемента
	start=first; ///начало левой части
	final=middle+1; ///начало правой части
	for(j=first; j<=last; j++) /// цикл для прохождения по массиву
	if ((start<=middle) && ((final>last) || (A[start]<A[final])))/// условие записи элемента во временный массив из левой части
	{
		mas[j]=A[start];/// запись элемента во временный массив из левой части
		start++;/// переход к следующему элементу левой части
	}
	else ///условие записи элемента во временный массив из правой части
	{
		mas[j]=A[final];/// запись элемента во временный массив из правой части
		final++;/// переход к следующему элементу правой части
	}
	///возвращение результата в список
	for (j=first; j<=last; j++) A[j]=mas[j];
	delete[]mas;/// освобождение памяти
};

/**
@function Merge
Эта функция рекурсивная, последовательно разделяет массив на две части и сортирует их этим же алгоритмо
@param A - указатель на изначальный массив
@param first - начало левой части
@param last - начало левой части
**/

void MergeSort(int *A, int first, int last)
{
	{
	if (first<last)/// проверка, но разделен ли уже массив на единичные элементы
	{
		MergeSort(A, first, (first+last)/2); ///сортировка левой части
		MergeSort(A, (first+last)/2+1, last); ///сортировка правой части
		Merge(A, first, last); ///слияние двух частей
	}
	}
};


/**
@function _tmain
Главная функция
@param srgc
@param argv[] 
**/
int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_ALL, "Rus");
	int i, n;
	int *A=new int[100];
	cout<<"Размер массива > "; cin>>n;
	for (i=1; i<=n; i++)
	{ cout<<i<<" элемент > "; cin>>A[i];}
	MergeSort(A, 1, n); ///вызов сортирующей процедуры
	cout<<"Упорядоченный массив: "; ///вывод упорядоченного массива
	for (i=1; i<=n; i++) cout<<A[i]<<" ";
	delete []A;
	system("pause>>void");
	return 0;
}


