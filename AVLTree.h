#include <iostream>
using namespace std;


//class AVL-drevo :
template<typename T>
class AVLTree
{

int balance;

void PrintNode(); ///печать значения узла и значения его детей
int Height(); ///рекурсивный метод,возвращает высоту древа
void PrintNodeTraverse(); ///рекурсивный метод,обход древа с вызовом у каждого узла метода PrintNode

void Refresh()//обновление баланса узла древа:
{ 
	balance=right->Height()-left->Height();

};//method Refresh


AVLTree* Find_left()//рекурсивная функция поиска в поддреве самого левого узла
{if ((left->left==0)&(left->right==0)) {PrintNode();return this;} else left->Find_left();}//method Find_left
void Rotate();//вращения вершины(+внутри предварительный Refresh)
void SingleLeftRotate();//малое левое вращение
void SingleRightRotate();//малое правое вращение
void DoubleLeftRotate();//большое левое вращение
void DoubleRightRotate();//большое правое вращение


public:

AVLTree<T>* left;
T value;
AVLTree<T>* right;

AVLTree():balance(0),left(0),right(0){}; ///конструктор AVLTree
//~AVLTree(){};

~AVLTree()//деструктор AVLTree
{//Удаление всей памяти,отведённой под АВЛ-древо(всех фактических вершин):
	if (left!=0) {delete left;left=0;};
	if (right!=0) {delete right;right=0;};
};//деструктор AVLTree

void Insert(T key); //avl-insert пока без корректировки поворотами
void Print();//печать древа
void Find(T key);///рекурсивный метод,поиск узла
void Remove(T key); ///рекурсивный метод,удаление узла

};//class AVLTree







template<typename T>
void AVLTree<T>::Insert(T key)//avl-insert
{
	if ((left == 0) && (right == 0))
	{
		value = key; right = new AVLTree<T>; left = new AVLTree<T>;
	} //balance уже == 0
	else
	{
		if (key >= value) right->Insert(key);
		else left->Insert(key);//key<value
		Rotate();//вращение на обратном проходе
	};//else
}//Insert


template<typename T>
void AVLTree<T>::Find(T key)
{

	if ((left == 0) && (right == 0)) { cout << "\nNode was not found"; return; }
	if (key > value) right->Find(key);
	if (key < value) left->Find(key);
	if (key == value) { cout << "\nIskomaya vershina:"; PrintNode(); };

}//method Find


template<typename T>
void AVLTree<T>::PrintNode() //печать value в узле,value его детей и высоты
{
	cout << "\n" << value << " [left:";
	if ((left->left == 0) && (left->right == 0)) cout << "NULL"; else cout << left->value;//if (left==&NILL)
	cout << "; right:";
	if ((right->left == 0) && (right->right == 0)) cout << "NULL"; else cout << right->value;//if (right==&NILL)
	cout << "; balance:" << balance;
	cout << "] Height: " << Height();

}//method PrintNode


template<typename T>
int AVLTree<T>::Height()//рекурсивный метод,возвращает высоту древа
{
	if ((right == 0) && (left == 0)) return 0;
	int bufleft = left->Height();
	int bufright = right->Height();
	if (bufleft > bufright) return 1 + bufleft;
	else return 1 + bufright;
}//method Height


template<typename T>
void AVLTree<T>::PrintNodeTraverse()//рекурсивный метод,обход древа с вызовом у каждого узла метода PrintNode
{
	if ((left == 0) && (right == 0)) return;
	else PrintNode();
	left->PrintNodeTraverse();
	right->PrintNodeTraverse();
}//method PrintNodeTraverse

template<typename T>
void AVLTree<T>::Print()//печать древа
{
	cout << "\n\nPechat' dreva:\n";
	if ((left == 0) && (right == 0))
	{
		cout << "\nDrevo pustoe\n";
		return;
	}
	PrintNodeTraverse();
}//method Print


template<typename T>
void AVLTree<T>::Rotate()
{
	Refresh();//обнавляем баланс узла
	if (balance == -2)
	{
		if (left->balance <= 0) SingleLeftRotate();//малое левое вращение
		else DoubleLeftRotate();//большое левое вращение
	}//if (balance==-2)
	else if (balance == 2)
	{
		if (right->balance >= 0) SingleRightRotate();//малое правое вращение
		else DoubleRightRotate();//большое правое вращение
	};//if (balance==2)
}; ///Rotate


template<typename T>
void AVLTree<T>::SingleLeftRotate()
{
	T buf_value = value;//сохраняем значение вершины a
	value = left->value;//копируем значение из вершины b в вершину а
	left->value = buf_value;//сохранённое значение a копируем в вершину b
	AVLTree<T>* buf = left->left;//сохраняем ветку L
	left->left = left->right;//L:=C
	left->right = right;//C=R
	right = left;//перекидываем a(new) направо
	left = buf;//достаём из памяти ветку L
		//Обновляем балансы вершин a и b:
	Refresh();//вершина b(new)
	right->Refresh();//вершина a(new)
};//SingleLeftRotate


template<typename T>
void AVLTree<T>::SingleRightRotate()
{
	T buf_value = value;//сохраняем значение вершины a
	value = right->value;//копируем значение из вершины b в вершину а
	right->value = buf_value;//сохранённое значение a копируем в вершину b
	AVLTree<T>* buf = right->right;//сохраняем ветку R
	right->right = right->left;//R=C
	right->left = left;//C=L
	left = right;//перекидываем a(new) налево
	right = buf;//достаём из памяти ветку R
		//Обновляем балансы вершин a и b:
	Refresh();//вершина b(new)
	left->Refresh();//вершина a(new)
};//SingleRightRotate


template<typename T>
void AVLTree<T>::DoubleLeftRotate()//большое левое вращение
{//далее комментарии соответсвуют картинке в Википедии в статье про АВЛ-деревья(моё прим.: правильно АВЛ-древы):
//тут: вершина а обменивается данными с вершиной с: т.о. они меняются местами
//такой приём делается для того,чтобы фактически вершина а осталась на месте и не надо было бы
//менять адрес-поле родителя поворачиваемой вершины
	AVLTree<T>* buf = left->right;//сохраняем ветку c
	T buf_value = value;//сохраняем значение вершины a
	value = buf->value;//копируем значение из вершины с в вершину а
	left->right = buf->left;//b.right=M
	buf->value = buf_value;//теперь вершина с - это вершина а
	buf->left = buf->right;//c.left=N(тут с старое(=a(new)) )
	buf->right = right;//c.right=R(тут с старое(=a(new)) )
	right = buf;//c(new).left=a(new)
	//Обновляем балансы вершин a,b и c:
	Refresh();//вершина с(new)
	left->Refresh();//вершина b(new=old)
	right->Refresh();//вершина a(new)
};//DoubleLeftRotate


template<typename T>
void AVLTree<T>::DoubleRightRotate()//большое правое вращение
{//далее комментарии соответсвуют картинке в Википедии в статье про АВЛ-деревья(моё прим.: правильно АВЛ-древы):
//тут: вершина а обменивается данными с вершиной с: т.о. они меняются местами
//такой приём делается для того,чтобы фактически вершина а осталась на месте и не надо было бы
//менять адрес-поле родителя поворачиваемой вершины
	AVLTree<T>* buf = right->left;//сохраняем ветку c
	T buf_value = value;//сохраняем значение вершины a
	value = buf->value;//копируем значение из вершины с в вершину а
	right->left = buf->right;//b.left=N
	buf->value = buf_value;//теперь вершина с - это вершина а
	buf->right = buf->left;//c.right=M(тут с старое)
	buf->left = left;//c.left=L(тут с старое)
	left = buf;//c(new).left=a(new)
	//Обновляем балансы вершин a,b и c:
	Refresh();//вершина с(new)
	left->Refresh();//вершина a(new)
	right->Refresh();//вершина b(new=old)
};//DoubleRightRotate;


template<typename T>
void AVLTree<T>::Remove(T key)
{
	AVLTree<T>* buf;//память
	if ((left == 0) && (right == 0)) return;
	if (key > value) right->Remove(key);//рекурсия направо
	else if (key < value) left->Remove(key);//рекурсия налево
	else if (key == value)//нашли узел,который надо удалить
	{
		if ((left->left == 0) && (left->right == 0) && (right->left == 0) && (right->right == 0))//случай,когда нет детей
		{//делаем нулевой найденную для удаления вершину:
			delete left;
			delete right;
			left = 0; right = 0;
			return;
		}//случай,когда нет детей
		else if ((left->left != 0) && (right->left == 0) && (right->right == 0))//случай,когда есть только левый ребёнок
		{
			delete right;//удаляем правый фиктивный ноль
			right = left->right;//перекидываем правое поддрево left-а на место правого поддрева this
			value = left->value; balance = left->balance;//переписываем значение и баланс из left в this
			buf = left;//сохраняем,чтобы удалить
			left = left->left;//перекидываем левое поддрево left-а на место левого поддрева this
			buf->left = 0;//обнуляем ветки buf,чтобы они не удалились рекурсивным деструктором
			buf->right = 0;
			delete buf;
		}//случай,когда есть только левый ребёнок
		else if ((left->left == 0) && (left->right == 0) && (right->left != 0))//случай,когда есть только правый ребёнок
		{
			delete left;//удаляем левый фиктивный ноль
			left = right->left;//перекидываем левое поддрево right-а на место левого поддрева this
			value = right->value; balance = right->balance;//переписываем значение и баланс из right в this
			buf = right;//сохраняем,чтобы удалить
			right = right->right;//перекидываем правое поддрево right-а на место правого поддрева this
			buf->left = 0;//обнуляем ветки buf,чтобы они не удалились рекурсивным деструктором
			buf->right = 0;
			delete buf;
		}//случай,когда есть только правый ребёнок
		else if ((left->left != 0) && (right->right != 0))//случай,когда есть оба ребёнка
		{
			buf = right->Find_left();//ищем самый левый узел в правом поддреве this: пусть он buf
			value = buf->value;//переписываем значение из найденного узла buf в this
			right->Remove(value);//рекурсивно удаляем найденный узел buf (а у него нет детей) из правого поддрева узла this
		}//случай,когда есть оба ребёнка
	};//if (key==value)
	Rotate();//обратный проход

};//Remove