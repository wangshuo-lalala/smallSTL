#pragma once
#include <iostream>
using namespace std;
#define HEIGHT(p)  ((p) ? (p)->height : 0)//节点高度，规定空树高度为0
#define Balanced(x) (HEIGHT((x)->lchild) == HEIGHT((x)->rchild))//理想平衡
#define BalFac(x) (HEIGHT((x)->lchild) - HEIGHT((x)->rchild))//平衡因子
#define AvlBalanced(x) ((-2 < BalFac(x)) && (BalFac(x) < 2))//AVL树平衡条件
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
	BinTree(char* filename);
	~BinTree();
};

/*构造函数及析构函数*/
template <class T> BinTree<T>::BinTree()
{
	root = nullptr;
	height = 0;
	size = 0;
}

template <class T> BinTree<T>::BinTree(char* filename)
{
	FILE *fp = fopen(filename, "r");
	T n;
	root = new BinNode<T>;
	fscanf(fp, "%d", n);
	while (n != 0)
	{
		
	}

}

template <class T> BinTree<T>::~BinTree()
{

}
