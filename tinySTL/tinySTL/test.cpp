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
	BinNode<int> *r = new BinNode<int>(0);
	BinNode<int> * p, *q;
	p = q = r;
	for (int i = 1; i < 10; ++i)
	{
		p = p->insertAsLc(i);
		q = q->insertAsRc(2 * i);
	}
	cout << r->getHeight() << endl;
	while (1);
	return 0;
}