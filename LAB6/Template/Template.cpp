// Template.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "stdio.h"
#include "iostream"
#include "conio.h"

using namespace std;

/** @brief какой-то класс.*/
class A
{
public:
	/**@brief поле int*/
	int var1;
	/**@brief поле int*/
	int var2;
	/** @brief конструктор по умолчанию*/
	A()
	{
		var1 = 0;
		var2 = 0;
	}
//*@funcltion swap1 функци€, осуществл€юща€ проверку на убывание и мен€ющую элементы массива местами в случае положительного ответа
	//*@param b ссылка на предыдущий элемент
	void swap1 (A &a)
	{
	if (this->var1 < a.var1)
		{
			A tmp;/// вводим временную переменную
			tmp.var1 = this->var1;///приравниваем временную к текущему
			tmp.var2= this->var2;
			this->var1 = a.var1;///приравниваем текущий к предыдущему
			this->var2 = a.var2;
			a.var1 = tmp.var1;///приравниваем предыдущий к текущему
			a.var2 = tmp.var2;
		}
	}

	void print ()
	{
		cout << this->var1 << " ";
	}

   
};

/**@brief какой-то класс*/
class B
{
public:
	/**@brief поле double*/
	double var1;
	/**@brief поле char*/
	char var2;
	/** @brief конструктор по умолчанию*/
	B()
	{
		var1 = 0;
		var2= 0;
	}
	//*@funcltion swap1 функци€, осуществл€юща€ проверку на убывание и мен€ющую элементы массива местами в случае положительного ответа
	//*@param b ссылка на предыдущий элемент
	void swap1 (B &b)
	{
		if (this->var1 < b.var1)/// если предыдущий элемент больше
		{
			B tmp;/// вводим временную переменную
			tmp.var1 = this->var1;///приравниваем временную к текущему
			tmp.var2= this->var2;
			this->var1 = b.var1;///приравниваем текущий к предыдущему
			this->var2 = b.var2;
			b.var1 = tmp.var1;///приравниваем предыдущий к текущему
			b.var2 = tmp.var2;
		}
	}

	void print ()
	{
		cout << this->var1 << " ";
	}

	
};

/**@function sort
@brief шаблонна€ функци€, производ€ща€ сортировку массива по возрастанию
@param mas указатель на массив
@param count количество элементов массива*/
template <class T>
void sort(T *mas, int count)
{

	
	for (int i = count-1; i>0; i--)///основной цикл прохождени€ по массиву
	{
		for (int j = 1; j < i+1; j++) ///внутренний цикл прохождени€ по массиву
		{
			mas[j].swap1(mas[j-1]);///осуществл€ем проверку и смену местами
		}
	}

		
	for (int j = 0; j<count; j++)
	{
		mas[j].print();
	}
}





/**@function _tmain
@brief главна€ функци€
*/
int _tmain(int argc, _TCHAR* argv[])
{
	A *masA = new A[10];
	B *masB = new B[10];
	cout << "Enter class A elements (10)";
	for (int i = 0; i <10; i++)
	{
		cin >> masA[i].var1;
	}

	cout << "\n\n";

	sort <A> (masA, 10);
		
	cout << "\n\n";


	cout << "Enter class B elements (10)";
	for (int i = 0; i <10; i++)
	{
		cin >> masB[i].var1;
	}

	
	cout << "\n\n";
	
	sort <B> (masB, 10);

	return 0;
}

