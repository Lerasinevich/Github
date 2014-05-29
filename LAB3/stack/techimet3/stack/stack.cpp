// stack.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <locale.h>

#define MAX 100

/**@brief указатель на область свободной памяти */
int *p;   
/**@ указатель на вершину стека */
int *tos; 
/**@ указатель на дно стека */
int *bos; 

void push(int i);
int pop(void);

 


int _tmain(int argc, _TCHAR* argv[])
{

	setlocale( LC_CTYPE, ".1251" );
	
  char s[80];

  p = (int *) malloc(MAX*sizeof(int)); /// получить память для стека */
  if(!p) {
    printf("Ошибка при выделении памяти\n");
    exit(1);
  }
  tos = p;///получить указатель на вершину стека
  bos = p + MAX-1;


  do {
    printf("1 - push, 2- pop");/// предоставление выбора пользователю
    gets(s);///считывание выбора пользователя
    switch(*s) {
       case '1':///случай "1":
		int a;
		printf(": ");
		scanf("%d", a);
		push(a);///добавить элемент
		break;
      case '2':{/// случай "2":
        int b = pop();///удалить элемент
        printf("%d", b);
        break;
	  default:
		  {
			  break;
		  }
		}
	     
    }
  }
  while(*s != 'q');///
	
  return 0;
}


/**
@function push
@brief Занесение элемента в стек.
@param У данной функции нет параметров
@return Функция возвращает пустое значение
/* Занесение элемента в стек. */
void push(int i)
{
  if(p > bos) {
    printf("Стек полон\n");
    return;
  }
  *p = i;
   p++;
}

/**
@function pop
@brief Извлечение элемента
@param У данной функции нет параметров
@return Функция возвращает указатель на элемент*/
int pop(void)
{
  p--;
  if(p < tos) {
    printf("Стек пуст\n");
    return 0;
  }
  return *p;
}

