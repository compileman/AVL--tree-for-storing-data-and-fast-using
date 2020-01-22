
#include "BSTree.h"


template<typename T>
void BSTree<T>::Insert(T key)//рекурсивная функция вставки нового узла в бинарное древо поиска
{
	if ((left==0) && (right==0))
	{value=key;right=new BSTree;left=new BSTree;}
	else if (key>=value) {right->Insert(key);}
	else if (key<value) {left->Insert(key);};
};//method Insert


template<typename T>
void BSTree<T>::PrintNode()//печать value в узле,value его детей и высоты поддрева
{
cout<<"\n"<<value<<" [left:";
if ((left->left==0)&&(left->right==0)) cout<<"NULL";else cout<<left->value;//if (left==&NILL)
	cout<<"; right:";
	if ((right->left==0)&&(right->right==0)) cout<<"NULL";else cout<<right->value;//if (right==&NILL)
	cout<<"] Height: "<<Height();
}//method PrintNode


template<typename T>
int BSTree<T>::Height()//рекурсивный метод,возвращает высоту древа
{
	if ((right==0)&&(left==0)) return 0;
	int bufleft=left->Height();
	int bufright=right->Height();
	if (bufleft>bufright) return 1+bufleft;
	else return 1+bufright;
}//method Height


template<typename T>
void BSTree<T>::PrintNodeTraverse()//рекурсивный метод,обход древа с вызовом у каждого узла метода PrintNode
{
	if ((left==0)&&(right==0)) return;
	else PrintNode();
	left->PrintNodeTraverse();
	right->PrintNodeTraverse();
}//method PrintNodeTraverse


template<typename T>
void BSTree<T>::Print()//печать древа
{
	cout<<"\n\nPechat' dreva:\n";
	if ((left==0)&&(right==0)) {cout<<"\nDrevo pustoe\n";return;}
	PrintNodeTraverse();
}//method Print


template<typename T>
void BSTree<T>::Find(T key)
{
	if ((left==0)&&(right==0)) {cout<<"\n\nNode was not found";return;}
	if (key>value) right->Find(key);
	if (key<value) left->Find(key);
	if (key==value) { cout<<"\n\nIskomaya vershina:";PrintNode();};
}//method Find


template<typename T>
void BSTree<T>::Remove(T key)
{
BSTree* buf;//память
if ((left==0)&&(right==0)) return;
if (key>value) right->Remove(key);//рекурсия направо
if (key<value) left->Remove(key);//рекурсия налево
if (key==value)//нашли узел,который надо удалить
{
if ( (left->left==0)&&(left->right==0)&&(right->left==0)&&(right->right==0) )//случай,когда нет детей
	{//делаем нулевой найденную для удаления вершину:
		delete left;
		delete right;
		left=0;right=0;
		return;
	}//случай,когда нет детей
else if ( (left->left!=0)&&(right->left==0)&&(right->right==0) )//случай,когда есть только левый ребёнок
	{
		delete right;//удаляем правый фиктивный ноль
		right=left->right;//перекидываем правое поддрево left-а на место правого поддрева this
		value=left->value;//переписываем значение из left в this
		buf=left;//сохраняем,чтобы удалить
		left=left->left;//перекидываем левое поддрево left-а на место левого поддрева this
		buf->left=0;//обнуляем ветки buf,чтобы они не удалились рекурсивным деструктором
		buf->right=0;
		delete buf;
		return;
    }//случай,когда есть только левый ребёнок
else if ( (left->left==0)&&(left->right==0)&&(right->left!=0) )//случай,когда есть только правый ребёнок
	{
		delete left;//удаляем левый фиктивный ноль
        left=right->left;//перекидываем левое поддрево right-а на место левого поддрева this
		value=right->value;//переписываем значение из right в this
		buf=right;//сохраняем,чтобы удалить
		right=right->right;//перекидываем правое поддрево right-а на место правого поддрева this
		buf->left=0;//обнуляем ветки buf,чтобы они не удалились рекурсивным деструктором
		buf->right=0;
		delete buf;
		return;
    }//случай,когда есть только правый ребёнок
else if ( (left->left!=0)&&(right->right!=0) )//случай,когда есть оба ребёнка
	{
		buf=right->Find_left();//ищем самый левый узел в правом поддреве this: пусть он buf
		value=buf->value;//переписываем значение из найденного узла buf в this
		buf=this;
		right->Remove(value);//рекурсивно удаляем найденный узел buf (а у него нет детей) из правого поддрева узла this
	}//случай,когда есть оба ребёнка

};//if (key==value)
};//Remove

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////






