// АВЛ-древы.cpp : Defines the entry point for the console application.
//

//#include "BSTree.h"
#include "AVLTree.h"

int main()
{

//BSTree B;
//cout<<"\n\nRabota s binarnim drevom poiska :";

AVLTree<double> B;

cout<<"\n\nRabota s AVL-drevom:";
cout<<"\n\nVershini dreva:\n";


//различные древы =) :
//char s[80]="8 6 12 5 7 10 14 9 11 13 15";
//char s[80]="16 4 18 2 8 1 3 6 12 5 7 10 14 9 11 13 15";
//char s[80]="1 2 3 4 5 6 7 8 9 10";
//char s[80]="50 20 60 10 40 70 5 30 45";
//char s[80]="40 20 10 30 25 50 45 60 70";
//char s[80]="50 30 70 65 20 40 35";
//char s[80]="1 2 3 4 5";


char s[80] = "3.4 -2.0 1 5 -4 7";
///char s[80]="";


//cout<<"\n\nVvedite drevo:\n";
//gets_s(s);
//cout<<s<<endl;

cout<<"\n\nProverka korrektnosti razbora stroki na leksemi:\n";

char* next_token;
auto token = strtok_s(s, " " , &next_token );


while( token!=NULL )
{
	cout<<"\n"<<token;
	B.Insert( strtod(token,NULL) ); ///добавление в АВЛ-древо
	token = strtok_s(NULL, " ", &next_token);

};//while( token!=NULL )


cout<<"\n\nEnter node which you want to insert :";
gets_s(s);
   double ff = strtod(s, NULL);
   B.Insert( ff );
   B.Print();//печать AVL-древа

cout<<"\n\nEnter node which you want to find :";
gets_s(s);
   B.Find(atoi(s));
   B.Print(); ///печать AVL-древа

cout<<"\n\nEnter node which you want to delete :";
gets_s(s);

  B.Remove( strtod(s,NULL) );
  B.Print();//печать AVL-древа

cin.get();

}//int main()