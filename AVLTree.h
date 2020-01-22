#include <iostream>
using namespace std;


//class AVL-drevo :
template<typename T>
class AVLTree
{

int balance;

void PrintNode(); ///������ �������� ���� � �������� ��� �����
int Height(); ///����������� �����,���������� ������ �����
void PrintNodeTraverse(); ///����������� �����,����� ����� � ������� � ������� ���� ������ PrintNode

void Refresh()//���������� ������� ���� �����:
{ 
	balance=right->Height()-left->Height();

};//method Refresh


AVLTree* Find_left()//����������� ������� ������ � �������� ������ ������ ����
{if ((left->left==0)&(left->right==0)) {PrintNode();return this;} else left->Find_left();}//method Find_left
void Rotate();//�������� �������(+������ ��������������� Refresh)
void SingleLeftRotate();//����� ����� ��������
void SingleRightRotate();//����� ������ ��������
void DoubleLeftRotate();//������� ����� ��������
void DoubleRightRotate();//������� ������ ��������


public:

AVLTree<T>* left;
T value;
AVLTree<T>* right;

AVLTree():balance(0),left(0),right(0){}; ///����������� AVLTree
//~AVLTree(){};

~AVLTree()//���������� AVLTree
{//�������� ���� ������,��������� ��� ���-�����(���� ����������� ������):
	if (left!=0) {delete left;left=0;};
	if (right!=0) {delete right;right=0;};
};//���������� AVLTree

void Insert(T key); //avl-insert ���� ��� ������������� ����������
void Print();//������ �����
void Find(T key);///����������� �����,����� ����
void Remove(T key); ///����������� �����,�������� ����

};//class AVLTree







template<typename T>
void AVLTree<T>::Insert(T key)//avl-insert
{
	if ((left == 0) && (right == 0))
	{
		value = key; right = new AVLTree<T>; left = new AVLTree<T>;
	} //balance ��� == 0
	else
	{
		if (key >= value) right->Insert(key);
		else left->Insert(key);//key<value
		Rotate();//�������� �� �������� �������
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
void AVLTree<T>::PrintNode() //������ value � ����,value ��� ����� � ������
{
	cout << "\n" << value << " [left:";
	if ((left->left == 0) && (left->right == 0)) cout << "NULL"; else cout << left->value;//if (left==&NILL)
	cout << "; right:";
	if ((right->left == 0) && (right->right == 0)) cout << "NULL"; else cout << right->value;//if (right==&NILL)
	cout << "; balance:" << balance;
	cout << "] Height: " << Height();

}//method PrintNode


template<typename T>
int AVLTree<T>::Height()//����������� �����,���������� ������ �����
{
	if ((right == 0) && (left == 0)) return 0;
	int bufleft = left->Height();
	int bufright = right->Height();
	if (bufleft > bufright) return 1 + bufleft;
	else return 1 + bufright;
}//method Height


template<typename T>
void AVLTree<T>::PrintNodeTraverse()//����������� �����,����� ����� � ������� � ������� ���� ������ PrintNode
{
	if ((left == 0) && (right == 0)) return;
	else PrintNode();
	left->PrintNodeTraverse();
	right->PrintNodeTraverse();
}//method PrintNodeTraverse

template<typename T>
void AVLTree<T>::Print()//������ �����
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
	Refresh();//��������� ������ ����
	if (balance == -2)
	{
		if (left->balance <= 0) SingleLeftRotate();//����� ����� ��������
		else DoubleLeftRotate();//������� ����� ��������
	}//if (balance==-2)
	else if (balance == 2)
	{
		if (right->balance >= 0) SingleRightRotate();//����� ������ ��������
		else DoubleRightRotate();//������� ������ ��������
	};//if (balance==2)
}; ///Rotate


template<typename T>
void AVLTree<T>::SingleLeftRotate()
{
	T buf_value = value;//��������� �������� ������� a
	value = left->value;//�������� �������� �� ������� b � ������� �
	left->value = buf_value;//���������� �������� a �������� � ������� b
	AVLTree<T>* buf = left->left;//��������� ����� L
	left->left = left->right;//L:=C
	left->right = right;//C=R
	right = left;//������������ a(new) �������
	left = buf;//������ �� ������ ����� L
		//��������� ������� ������ a � b:
	Refresh();//������� b(new)
	right->Refresh();//������� a(new)
};//SingleLeftRotate


template<typename T>
void AVLTree<T>::SingleRightRotate()
{
	T buf_value = value;//��������� �������� ������� a
	value = right->value;//�������� �������� �� ������� b � ������� �
	right->value = buf_value;//���������� �������� a �������� � ������� b
	AVLTree<T>* buf = right->right;//��������� ����� R
	right->right = right->left;//R=C
	right->left = left;//C=L
	left = right;//������������ a(new) ������
	right = buf;//������ �� ������ ����� R
		//��������� ������� ������ a � b:
	Refresh();//������� b(new)
	left->Refresh();//������� a(new)
};//SingleRightRotate


template<typename T>
void AVLTree<T>::DoubleLeftRotate()//������� ����� ��������
{//����� ����������� ������������ �������� � ��������� � ������ ��� ���-�������(�� ����.: ��������� ���-�����):
//���: ������� � ������������ ������� � �������� �: �.�. ��� �������� �������
//����� ���� �������� ��� ����,����� ���������� ������� � �������� �� ����� � �� ���� ���� ��
//������ �����-���� �������� �������������� �������
	AVLTree<T>* buf = left->right;//��������� ����� c
	T buf_value = value;//��������� �������� ������� a
	value = buf->value;//�������� �������� �� ������� � � ������� �
	left->right = buf->left;//b.right=M
	buf->value = buf_value;//������ ������� � - ��� ������� �
	buf->left = buf->right;//c.left=N(��� � ������(=a(new)) )
	buf->right = right;//c.right=R(��� � ������(=a(new)) )
	right = buf;//c(new).left=a(new)
	//��������� ������� ������ a,b � c:
	Refresh();//������� �(new)
	left->Refresh();//������� b(new=old)
	right->Refresh();//������� a(new)
};//DoubleLeftRotate


template<typename T>
void AVLTree<T>::DoubleRightRotate()//������� ������ ��������
{//����� ����������� ������������ �������� � ��������� � ������ ��� ���-�������(�� ����.: ��������� ���-�����):
//���: ������� � ������������ ������� � �������� �: �.�. ��� �������� �������
//����� ���� �������� ��� ����,����� ���������� ������� � �������� �� ����� � �� ���� ���� ��
//������ �����-���� �������� �������������� �������
	AVLTree<T>* buf = right->left;//��������� ����� c
	T buf_value = value;//��������� �������� ������� a
	value = buf->value;//�������� �������� �� ������� � � ������� �
	right->left = buf->right;//b.left=N
	buf->value = buf_value;//������ ������� � - ��� ������� �
	buf->right = buf->left;//c.right=M(��� � ������)
	buf->left = left;//c.left=L(��� � ������)
	left = buf;//c(new).left=a(new)
	//��������� ������� ������ a,b � c:
	Refresh();//������� �(new)
	left->Refresh();//������� a(new)
	right->Refresh();//������� b(new=old)
};//DoubleRightRotate;


template<typename T>
void AVLTree<T>::Remove(T key)
{
	AVLTree<T>* buf;//������
	if ((left == 0) && (right == 0)) return;
	if (key > value) right->Remove(key);//�������� �������
	else if (key < value) left->Remove(key);//�������� ������
	else if (key == value)//����� ����,������� ���� �������
	{
		if ((left->left == 0) && (left->right == 0) && (right->left == 0) && (right->right == 0))//������,����� ��� �����
		{//������ ������� ��������� ��� �������� �������:
			delete left;
			delete right;
			left = 0; right = 0;
			return;
		}//������,����� ��� �����
		else if ((left->left != 0) && (right->left == 0) && (right->right == 0))//������,����� ���� ������ ����� ������
		{
			delete right;//������� ������ ��������� ����
			right = left->right;//������������ ������ �������� left-� �� ����� ������� �������� this
			value = left->value; balance = left->balance;//������������ �������� � ������ �� left � this
			buf = left;//���������,����� �������
			left = left->left;//������������ ����� �������� left-� �� ����� ������ �������� this
			buf->left = 0;//�������� ����� buf,����� ��� �� ��������� ����������� ������������
			buf->right = 0;
			delete buf;
		}//������,����� ���� ������ ����� ������
		else if ((left->left == 0) && (left->right == 0) && (right->left != 0))//������,����� ���� ������ ������ ������
		{
			delete left;//������� ����� ��������� ����
			left = right->left;//������������ ����� �������� right-� �� ����� ������ �������� this
			value = right->value; balance = right->balance;//������������ �������� � ������ �� right � this
			buf = right;//���������,����� �������
			right = right->right;//������������ ������ �������� right-� �� ����� ������� �������� this
			buf->left = 0;//�������� ����� buf,����� ��� �� ��������� ����������� ������������
			buf->right = 0;
			delete buf;
		}//������,����� ���� ������ ������ ������
		else if ((left->left != 0) && (right->right != 0))//������,����� ���� ��� ������
		{
			buf = right->Find_left();//���� ����� ����� ���� � ������ �������� this: ����� �� buf
			value = buf->value;//������������ �������� �� ���������� ���� buf � this
			right->Remove(value);//���������� ������� ��������� ���� buf (� � ���� ��� �����) �� ������� �������� ���� this
		}//������,����� ���� ��� ������
	};//if (key==value)
	Rotate();//�������� ������

};//Remove