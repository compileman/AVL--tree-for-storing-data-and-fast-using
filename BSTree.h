#include <iostream>
using namespace std;


template<typename T>
class BSTree
{
void PrintNode();//������ �������� ���� � �������� ��� �����
int Height();//����������� �����,���������� ������ �����
void PrintNodeTraverse();//����������� �����,����� ����� � ������� � ������� ���� ������ PrintNode


public://BSTree

BSTree* Find_left() //����������� ������� ������ � �������� ������ ������ ����
{if ((left->left==0)&(left->right==0)) {PrintNode();return this;}else left->Find_left();}//method Find_left

	BSTree* left;
	T value ;
	BSTree* right;
	BSTree():left(0),right(0){}; ///����������� BSTree
	~BSTree()//���������� BSTree
	{//�������� ���� ������,��������� ��� �������� ����� ������ (���� ����������� ������):
	if (left!=0) {delete left;left=0;};
	if (right!=0) {delete right;right=0;};
	}//���������� BSTree

void Insert(T key);//����������� ����� ������� ������ ���� � �������� ����� ������
void Print();//������ �����
void Find(T key);//����������� �����,����� ����
void Remove(T key);//����������� �����,�������� ����
};//class BSTree
