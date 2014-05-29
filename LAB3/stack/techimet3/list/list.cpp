// list.cpp : Defines the entry point for the console application.
//

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

/** struct адрес*/
struct address {
  char name[40];
  char street[40];
  char city[20];
  char state[3];
  char zip[11];
  struct address *next; /* ссылка на следующий адрес */
}

/**function sls_store
@brief  Вставка в упорядоченный односвязный список
@param i - новый элемент
@param start - начало списка
@param last - конец списка
@return Функция возвращает пустое значение*/

void sls_store(struct address *i, 
               struct address **start, 
               struct address **last) 
{
  struct address *old, *p;

  p = *start;

  if(!*last) {/// первый элемент в списке */
    i->next = NULL;
    *last = i;
    *start = i;
    return;
  }

  old = NULL;
  while(p) {
    if(strcmp(p->name, i->name)<0) {
      old = p;
      p = p->next;
    }
    else {
      if(old) { ///вставка в середину */
        old->next = i;
        i->next = p;
        return;
      }
      i->next = p;/// вставка в начало */
      *start = i;
      return;
    }
  }
  (*last)->next = i; /// вставка в конец */
  i->next = NULL;
  *last = i;
}

/**function display
@brief  Отображение элемента
@param start - начало списка
@return Функция возвращает пустое значение*/
void display(struct address *start)
{
  while(start) {
    printf("%s\n", start->name);
    start = start->next;
  }
}
struct address *search(struct address *start, char *n)
{
  while(start) {
    if(!strcmp(n, start->name)) return start;
    start = start->next;
  }
  return NULL;  /* подходящий элемент не найден */
}



/**function sdelete
@brief  Отображение элемента
@param i - удаляемый элемент
@param start - начало списка
@param last - конец списка
@param p - предыдущий элемент
@return Функция возвращает пустое значение*/
void sldelete(
     struct address *p, 
     struct address *i, 
     struct address **start, 
     struct address **last) 
{
  if(p) p->next = i->next;
  else *start = i->next;

  if(i==*last && p) *last = p;
}





int _tmain(int argc, _TCHAR* argv[])
{
	address *a, *b, *c;
	a = new address;
	a->next = b;
	b->next = c;
	address *d = new address;
	sls_store(d, *a, *b);

	return 0;
}

