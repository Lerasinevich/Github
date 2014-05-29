//** @file techimet3.cpp : Defines the entry point for the console application.
//
//*@brief создание очереди*/
//*@detailed в проекте создается очередь и несколько функций для работы с ней: добавление и удаление */

#include "stdafx.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <locale.h>

/**
namespace std;
@brief Пространство имен A
*/

#define MAX 100

char *p[MAX], *qretrieve(void);
int spos = 0;
int rpos = 0;
void enter(void);
/** function enter
@brief Вставка в очередь нового элемента
@detailed Данная функция позволяет добавить в очередь новый элемент при условии, что количество элементов не будет превышать ограничения
@param У данной функции нет параметров
@return Функция возвращает пустое значение*/

void qstore(char *q);
/** function qstore
@brief Вставка в очередь нового элемента
@detailed Данная функция позволяет добавить в очередь новый элемент при условии, что количество элементов не будет превышать ограничения
@param У данной функции нет параметров
@return Функция возвращает пустое значение*/

void review(void);
/** function review
@brief Вставка в очередь нового элемента
@detailed Данная функция позволяет просмотреть все элементы очереди по очереди
@param У данной функции нет параметров
@return Функция возвращает пустое значение */

void delete_ap(void);
/**function delete_ap
@brief Удаление элемента из очереди
@detailed Данная функция позволяет удалить элемент из очереди по принципу FIFO 
@param У данной функции нет параметров
@return Функция возвращает пустое значение*/

char retrieve (void);
/**
@function retrieve
@brief Извлечение элемента
@detailed Данная функция позволяет извлечь элемент из очереди. Извлечение производится по принципу FIFO 
@param У данной функции нет параметров
@return Функция возвращает указатель на элемент*/



int _tmain(int argc, _TCHAR* argv[])
{
	setlocale( LC_CTYPE, ".1251" );
	char s[80]; /// инициализация массива очереди
	int t; /// инициализация счетчика

	for(t=0; t < MAX; ++t) p[t] = NULL;  

	for(;;)
	{
		printf("Ввести (E), Список (L), Удалить (R), Выход (Q): ");/// вывод меню функций на экран
		gets(s);
		*s = toupper(*s);

		switch(*s) {
			case 'E':
			enter();
			break;
		case 'L':
			review();
			break;
		case 'R':
			delete_ap();
			break;
		case 'Q':
			exit(0);
    }/// выбор функции пользователем
  }
  return 0;
}


void enter(void)
{
  char s[256], *p;

  do {
    printf("Введите встречу %d: ", spos+1);
    gets(s);
    if(*s==0) break; 
    p = (char *) malloc(strlen(s)+1);/// выделение памяти, если возможно
    if(!p) {
      printf("Не хватает памяти.\n");
      return;
    }
    strcpy(p, s);/// вставка элемента
    if(*s) qstore(p);
  } while(*s);
}


void review(void)
{
  int t;///инициализация счетчика

  for(t=rpos; t < spos; ++t)
    printf("%d. %s\n", t+1, p[t]);///
}


void delete_ap(void)
{
  char *p;///инициализация дополнительного массива

  if((p=qretrieve())==NULL) return;///удаление элемента
  printf("%s\n", p);
}

void qstore(char *q)
{
  if(spos==MAX) {
    printf("List Full\n");
    return;
  }
  p[spos] = q;///добавление элемента
  spos++;///увеличение счетчика
}


char *qretrieve(void)
{
  if(rpos==spos) {
    printf("Встречь больше нет.\n");
    return NULL;
  }
  rpos++;///увеличение счетчика
  return p[rpos-1];///извлечение элемента
}

