#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;
//#define HEIGHT(p)  ((p) ? (p)->height : 0)//节点高度，规定空树高度为0
//#define Balanced(x) (HEIGHT((x)->lchild) == HEIGHT((x)->rchild))//理想平衡
//#define BalFac(x) (HEIGHT((x)->lchild) - HEIGHT((x)->rchild))//平衡因子
//#define AvlBalanced(x) ((-2 < BalFac(x)) && (BalFac(x) < 2))//AVL树平衡条件
#define MaxSize 100

/*二叉树结点类*/
template <class T> struct BinNode
{
	T data;
	BinNode * lchild;
	BinNode * rchild;

	BinNode() { lchild = nullptr; rchild = nullptr; height = 1; }
	BinNode(const T & d, BinNode * l = nullptr, BinNode * r = nullptr) : data(d), lchild(l), rchild(r) { }

	//常用函数
	int getSize() const;//获取子树规模
	int getHeight() const;//获取子树高度
	BinNode* insertAsLc(const T & a);//作为左孩子插入
	BinNode* insertAsRc(const T & a);//作为右孩子插入
	//BinNode* succ() const;//中序遍历下的直接后继
	template<typename VST> void travLevel(VST & fun) ;//子树层次遍历
	template<typename VST> void travPre(VST & fun) const;//子树先序遍历
	template<typename VST> void travMid(VST & fun) const;//子树中序遍历
	template<typename VST> void travPost(VST & fun) const;//子树后序遍历
};

//常用函数
template <class T> int BinNode<T>::getSize() const//获取子树规模
{
	if (this == nullptr)
		return 0;
	else
		return 1 + lchild->getSize() + rchild->getSize();
}

template <class T> int BinNode<T>::getHeight() const//获取子树高度
{
	if (this == nullptr)
		return 0;
	int a;
	int b;
	a = lchild->getHeight();
	b = rchild->getHeight();
	return a > b ? (a + 1) : (b + 1);
}

template <class T> BinNode<T>* BinNode<T>::insertAsLc(const T & a)//作为左孩子插入
{
	if (this != nullptr)
	{
		BinNode * p = new BinNode(a);
		lchild = p;
		return p;
	}
	return this;
}

template <class T> BinNode<T>* BinNode<T>::insertAsRc(const T & a)//作为右孩子插入
{
	if (this != nullptr)
	{
		BinNode * p = new BinNode(a);
		rchild = p;
		return p;
	}
	return this;
}

template <class T> template<typename VST> void BinNode<T>::travLevel(VST & fun) //子树层次遍历
{
	if (this == nullptr)
		return;
	BinNode * que[MaxSize], *p;
	int front = 0, rear = 0;
	que[rear++] = this;
	while (front != rear)
	{
		p = que[front++];
		fun(p->data);
		if (p->lchild != nullptr)
			que[rear++] = p->lchild;
		if (p->rchild != nullptr)
			que[rear++] = p->rchild;
	}
}

template <class T> template<typename VST> void BinNode<T>::travPre(VST & fun) const//子树先序遍历
{
	if (this != nullptr)
	{
		fun(data);
		lchild->travPre(fun);
		rchild->travPre(fun);
	}
}

template <class T> template<typename VST> void BinNode<T>::travMid(VST & fun) const//子树中序遍历
{
	if (this != nullptr)
	{
		lchild->travMid(fun);
		fun(data);
		rchild->travMid(fun);
	}
}

template <class T> template<typename VST> void BinNode<T>::travPost(VST & fun) const//子树后序遍历
{
	if (this != nullptr)
	{
		lchild->travPost(fun);
		rchild->travPost(fun);
		fun(data);
	}
}

/*二叉树模板类*/
template <class T> class BinTree
{
public:
	typedef BinNode<T>* iterator;
private:
	iterator root;//根节点指针
	int height;//树高度
	int size;//树的规模
	
public:
	/*构造函数及析构函数*/
	BinTree();
	BinTree(T A[], T B[], int a1, int a2, int b1, int b2);//二叉树1前序、中序构建二叉树
	BinTree(char* filename);
	~BinTree();

	/*常用函数*/
	BinNode<T>* fileCon(FILE * f);
	BinNode<T>* preMid(T A[], T B[], int a1, int a2, int b1, int b2);//二叉树1前序、中序构建二叉树结点构造
	const int & getSize() const { return size; }//返回书的规模
	const int & getHeight() const { return height; }//返回树高
	BinNode<T>* getRoot() const { return root; }//返回树根指针
	bool isEmpty() const { return !root; }//判空
	BinNode<T>* insertAsLc(BinNode<T>* x, const T & a, bool j);//左节点插入
	BinNode<T>* insertAsRc(BinNode<T>* x, const T & a, bool j);//右节点插入

	template<typename VST> void travLevel(VST & fun);//层次遍历
	/*递归*/
	template<typename VST> void travPreRe(VST & fun) const;//先序遍历
	template<typename VST> void travMidRe(VST & fun) const;//中序遍历
	template<typename VST> void travPostRe(VST & fun) const;//后序遍历
	/*非递归*/
	template<typename VST> void travPre(VST & fun) const;//先序遍历
	template<typename VST> void travMid(VST & fun) const;//中序遍历
	template<typename VST> void travPost(VST & fun) const;//后序遍历

	
	void remove(BinNode<T>* x);/*删除树中子树*/
};

/*构造函数及析构函数*/
template <class T> BinTree<T>::BinTree()
{
	root = nullptr;
	height = 0;
	size = 0;
}

template <class T> BinNode<T>* BinTree<T>::preMid(T A[], T B[], int a1, int a2, int b1, int b2)//二叉树1前序、中序构建二叉树结点构造
{
	if (a1 < a2)
		return nullptr;
	iterator p = new BinNode<T>;
	int i;
	for (i = b1; i <= b2; ++i)
		if (A[a1] == B[i])
			break;
	p->data = B[i];
	p->lchild = preMid(A, B, a1 + 1, a1 + i - b1, b1, i - 1);
	p->rchild = preMid(A, B, a1 + i - b1 + 1, a2, i + 1, b2);
	return p;
}
template <class T> BinTree<T>::BinTree(T A[], T B[], int a1, int a2, int b1, int b2)//二叉树1前序、中序构建二叉树
{
	root = preMid(A, B, a1, a2, b1, b2);
	height = root->getHeight();
	size = root->getSize();
}

template <class T> BinNode<T>* BinTree<T>::fileCon(FILE * f)
{
	int n;
	fscanf_s(f, "%d", &n);
	BinNode<T>* r;
	if (n != 0)
	{
		r = new BinNode<T>(n);
		r->lchild = fileCon(f);
		r->rchild = fileCon(f);
		return r;
	}
	else
		return nullptr;
}

template <class T> BinTree<T>::BinTree(char* filename)
{

	FILE *fp;
	fopen_s(&fp, filename, "r");
	root = fileCon(fp);
	size = root->getSize();
	height = root->getHeight();
	fclose(fp);
}

template <class T> BinTree<T>::~BinTree()
{
	remove(root);
}

template <class T> BinNode<T>* BinTree<T>::insertAsLc(BinNode<T>* x, const T & a, bool j)//左节点插入
{
	if (x->lchild == nullptr)
	{
		BinNode<T> * p = BinNode<T>(a);
		x->lchild = p;
	}
	else if (j == 0)
	{
		BinNode<T> * q = x->lchild;
		BinNode<T> * p = BinNode<T>(a);
		x->lchild = p;
		p->lchild = q;
	}
	else
	{
		BinNode<T> * q = x->lchild;
		BinNode<T> * p = BinNode<T>(a);
		x->lchild = p;
		p->rchild = q;
	}
	size = root->getSize();
	height = root->getHeight();
	return x->lchild;
}
template <class T> BinNode<T>* BinTree<T>::insertAsRc(BinNode<T>* x, const T & a, bool j)//右节点插入
{
	if (x->rchild == nullptr)
	{
		BinNode<T> * p = BinNode<T>(a);
		x->rchild = p;
	}
	else if (j == 0)
	{
		BinNode<T> * q = x->rchild;
		BinNode<T> * p = BinNode<T>(a);
		x->rchild = p;
		p->lchild = q;
	}
	else
	{
		BinNode<T> * q = x->rchild;
		BinNode<T> * p = BinNode<T>(a);
		x->rchild = p;
		p->rchild = q;
	}
	size = root->getSize();
	height = root->getHeight();
	return x->rchild;
}

template <class T> template<typename VST> void BinTree<T>::travLevel(VST & fun)//层次遍历
{
	if (root == nullptr)
		return;
	iterator que[MaxSize];
	int front = 0, rear = 0;
	que[rear++] = root;
	iterator p;
	while (front != rear)
	{
		p = que[front++];
		fun(p->data);
		if (p->lchild != nullptr)
			que[rear++] = p->lchild;
		if (p->rchild != nullptr)
			que[rear++] = p->rchild;
	}
}

/*递归*/
template <class T> template<typename VST> void BinTree<T>::travPreRe(VST & fun) const//先序遍历
{
	if (root != nullptr)
	{
		root->travPre(fun);
	}
}

template <class T> template<typename VST> void BinTree<T>::travMidRe(VST & fun) const//中序遍历
{
	if (root != nullptr)
	{
		root->travMid(fun);
	}
}

template <class T> template<typename VST> void BinTree<T>::travPostRe(VST & fun) const//后序遍历
{
	if (root != nullptr)
	{
		root->travPost(fun);
	}
}

/*非递归*/
template <class T> template<typename VST> void BinTree<T>::travPre(VST & fun) const//先序遍历
{
	if (root == nullptr)
		return;
	iterator s[MaxSize], p;
	int top = -1;
	s[++top] = root;
	while (top != -1)
	{
		p = s[top--];
		fun(p->data);
		if (p->rchild != nullptr)
			s[++top] = p->rchild;
		if (p->lchild != nullptr)
			s[++top] = p->lchild;
	}
}

template <class T> template<typename VST> void BinTree<T>::travMid(VST & fun) const//中序遍历
{
	if (root == nullptr)
		return;
	iterator s[MaxSize], p = root;
	int top = -1;
	while (top != -1 || p != nullptr)
	{
		while (p != nullptr)
		{
			s[++top] = p;
			p = p->lchild;
		}
		p = s[top--];
		fun(p->data);
		p = p->rchild;
	}
}

template <class T> template<typename VST> void BinTree<T>::travPost(VST & fun) const//后序遍历
{
	if (root == nullptr)
		return;
	iterator s1[MaxSize], s2[MaxSize], p;
	int top1 = -1, top2 = -1;
	s1[top1++] = root;
	while (top1 != -1)
	{
		p = s1[top1--];
		s2[++top2] = p;
		if (p->lchild != nullptr)
			s1[++top1] = p->lchild;
		if (p->rchild != nullptr)
			s2[++top1] = p->rchild;
	}
	while (top2 != -1)
	{
		p = s2[top2--];
		fun(p->data);
	}
}

template <class T> void BinTree<T>::remove(BinNode<T>* x)
{
	if (x == nullptr)
		return;
	remove(x->lchild);
	remove(x->rchild);
	delete x;
}