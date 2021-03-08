#include <iostream>
using namespace std;
void fun(int a)
{
	cout << a << endl;
}
#include "myString.h"
#include <string>
#include "myTree.h"
#include "myBinTree.h"


class A
{
private:
	int a;
public:
	A(int da)
	{
		a = da;
	}
	A(const A & a1) { a = a1.a; }
	void show()
	{
		cout << a << endl;
	}
};
  
int main()
{
	BinTree<int> bt("tree.txt");
	bt.travMid(fun);
	cout << bt.getHeight() << endl << bt.getSize() << endl;
	while (1);
	return 0;
}