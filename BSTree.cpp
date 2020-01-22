
#include "BSTree.h"


template<typename T>
void BSTree<T>::Insert(T key)//����������� ������� ������� ������ ���� � �������� ����� ������
{
	if ((left==0) && (right==0))
	{value=key;right=new BSTree;left=new BSTree;}
	else if (key>=value) {right->Insert(key);}
	else if (key<value) {left->Insert(key);};
};//method Insert


template<typename T>
void BSTree<T>::PrintNode()//������ value � ����,value ��� ����� � ������ ��������
{
cout<<"\n"<<value<<" [left:";
if ((left->left==0)&&(left->right==0)) cout<<"NULL";else cout<<left->value;//if (left==&NILL)
	cout<<"; right:";
	if ((right->left==0)&&(right->right==0)) cout<<"NULL";else cout<<right->value;//if (right==&NILL)
	cout<<"] Height: "<<Height();
}//method PrintNode


template<typename T>
int BSTree<T>::Height()//����������� �����,���������� ������ �����
{
	if ((right==0)&&(left==0)) return 0;
	int bufleft=left->Height();
	int bufright=right->Height();
	if (bufleft>bufright) return 1+bufleft;
	else return 1+bufright;
}//method Height


template<typename T>
void BSTree<T>::PrintNodeTraverse()//����������� �����,����� ����� � ������� � ������� ���� ������ PrintNode
{
	if ((left==0)&&(right==0)) return;
	else PrintNode();
	left->PrintNodeTraverse();
	right->PrintNodeTraverse();
}//method PrintNodeTraverse


template<typename T>
void BSTree<T>::Print()//������ �����
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
BSTree* buf;//������
if ((left==0)&&(right==0)) return;
if (key>value) right->Remove(key);//�������� �������
if (key<value) left->Remove(key);//�������� ������
if (key==value)//����� ����,������� ���� �������
{
if ( (left->left==0)&&(left->right==0)&&(right->left==0)&&(right->right==0) )//������,����� ��� �����
	{//������ ������� ��������� ��� �������� �������:
		delete left;
		delete right;
		left=0;right=0;
		return;
	}//������,����� ��� �����
else if ( (left->left!=0)&&(right->left==0)&&(right->right==0) )//������,����� ���� ������ ����� ������
	{
		delete right;//������� ������ ��������� ����
		right=left->right;//������������ ������ �������� left-� �� ����� ������� �������� this
		value=left->value;//������������ �������� �� left � this
		buf=left;//���������,����� �������
		left=left->left;//������������ ����� �������� left-� �� ����� ������ �������� this
		buf->left=0;//�������� ����� buf,����� ��� �� ��������� ����������� ������������
		buf->right=0;
		delete buf;
		return;
    }//������,����� ���� ������ ����� ������
else if ( (left->left==0)&&(left->right==0)&&(right->left!=0) )//������,����� ���� ������ ������ ������
	{
		delete left;//������� ����� ��������� ����
        left=right->left;//������������ ����� �������� right-� �� ����� ������ �������� this
		value=right->value;//������������ �������� �� right � this
		buf=right;//���������,����� �������
		right=right->right;//������������ ������ �������� right-� �� ����� ������� �������� this
		buf->left=0;//�������� ����� buf,����� ��� �� ��������� ����������� ������������
		buf->right=0;
		delete buf;
		return;
    }//������,����� ���� ������ ������ ������
else if ( (left->left!=0)&&(right->right!=0) )//������,����� ���� ��� ������
	{
		buf=right->Find_left();//���� ����� ����� ���� � ������ �������� this: ����� �� buf
		value=buf->value;//������������ �������� �� ���������� ���� buf � this
		buf=this;
		right->Remove(value);//���������� ������� ��������� ���� buf (� � ���� ��� �����) �� ������� �������� ���� this
	}//������,����� ���� ��� ������

};//if (key==value)
};//Remove

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////






