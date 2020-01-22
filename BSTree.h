#include <iostream>
using namespace std;


template<typename T>
class BSTree
{
void PrintNode();//печать значения узла и значения его детей
int Height();//рекурсивный метод,возвращает высоту древа
void PrintNodeTraverse();//рекурсивный метод,обход древа с вызовом у каждого узла метода PrintNode


public://BSTree

BSTree* Find_left() //рекурсивная функция поиска в поддреве самого левого узла
{if ((left->left==0)&(left->right==0)) {PrintNode();return this;}else left->Find_left();}//method Find_left

	BSTree* left;
	T value ;
	BSTree* right;
	BSTree():left(0),right(0){}; ///конструктор BSTree
	~BSTree()//деструктор BSTree
	{//Удаление всей памяти,отведённой под бинарное древо поиска (всех фактических вершин):
	if (left!=0) {delete left;left=0;};
	if (right!=0) {delete right;right=0;};
	}//деструктор BSTree

void Insert(T key);//рекурсивный метод вставки нового узла в бинарное древо поиска
void Print();//печать древа
void Find(T key);//рекурсивный метод,поиск узла
void Remove(T key);//рекурсивный метод,удаление узла
};//class BSTree
