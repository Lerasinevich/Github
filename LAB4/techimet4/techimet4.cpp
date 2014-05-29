// techimet4.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "stdio.h"
#include "malloc.h"
#include <stdlib.h>
#include <iostream>
#include <cstdlib>
#include <locale.h>

/** @struct tree
@brief структура дерева
@var info данные.
@var left указатель на левого сына.
@var right указатель на правого сына.
 **/
struct tree {
  char info;
  struct tree *left;
  struct tree *right;
  };

/**
@function stree
@brief добавление нового элемента
@param root корневой элемент
@param r новый элемент
@param info данные
@return root корневой элемент с указателем на новый**/
tree *stree(
  tree *root,
  tree *r,
  char info  
  )
{
  if(!r)/**проверка наличия сына. В случае его отсутствия создается новый,
		в противном случае указатель спускается ниже в соответствии с правилом
		и повторяет данное действие за счет рекурсии **/ {
    r = new tree;
    if(!r) {
      printf("Не хватает памяти\n");
      exit(0);
    }
    r->left = NULL;
    r->right = NULL;
    r->info = info;
    if(!root)
		{
			
			return r;}/* первый вход */
    if(info < root->info) 
		{
			root->left = r;
			
	}

    else 
		{
			root->right = r;
			
	}
	return r;
  }
  if(info < r->info) 
    stree(r,r->left,info);
  else
    stree(r,r->right,info);

  return root; 
}

/**
@function inorder
@brief симметрический обход
@param root дерево
@return функция возвращает пустое значение**/
void inorder(struct tree *root)
{
  if(!root) return;

  inorder(root->left);
  if(root->info) printf("%c ", root->info);
  inorder(root->right);
}


/**
@function preorder
@brief прямой обход
@param root дерево
@return функция возвращает пустое значение**/
void preorder(struct tree *root)
{
  if(!root) return;

  if(root->info) printf("%c ", root->info);
  preorder(root->left);
  preorder(root->right);
}


/**
@function postorder
@brief обратный обход
@param root дерево
@return функция возвращает пустое значение**/
void postorder(struct tree *root)
{
  if(!root) return;

  postorder(root->left);
  postorder(root->right);
  if(root->info) printf("%c ", root->info);
}






int _tmain(int argc, _TCHAR* argv[])
{
	setlocale( LC_CTYPE, ".1251" );
	char s[80];
	tree* root;

	root = NULL;  /* инициализация корня дерева */

	do {
    printf("Введите букву: ");
    gets(s);
    root = stree(root, root, *s);
  } while(*s);

	std::cout << "Симметричный обход";
	inorder(root);
	std::cout << std::endl;
	std::cout << "Прямой обход";
	preorder(root);
	std::cout << std::endl;
	std::cout << "Обратный обход";
	
	postorder(root);
	std::cout << std::endl;


	return 0;
}

