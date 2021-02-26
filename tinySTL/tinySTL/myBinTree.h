#pragma once
#include <iostream>
using namespace std;
#define HEIGHT(p)  ((p) ? (p)->height : 0)//�ڵ�߶ȣ��涨�����߶�Ϊ0
#define Balanced(x) (HEIGHT((x)->lchild) == HEIGHT((x)->rchild))//����ƽ��
#define BalFac(x) (HEIGHT((x)->lchild) - HEIGHT((x)->rchild))//ƽ������
#define AvlBalanced(x) ((-2 < BalFac(x)) && (BalFac(x) < 2))//AVL��ƽ������
#define MaxSize 100

/*�����������*/
template <class T> struct BinNode
{
	T data;
	BinNode * lchild;
	BinNode * rchild;

	BinNode() { lchild = nullptr; rchild = nullptr; height = 1; }
	BinNode(const T & d, BinNode * l = nullptr, BinNode * r = nullptr) : data(d), lchild(l), rchild(r) { }

	//���ú���
	int getSize() const;//��ȡ������ģ
	int getHeight() const;//��ȡ�����߶�
	BinNode* insertAsLc(const T & a);//��Ϊ���Ӳ���
	BinNode* insertAsRc(const T & a);//��Ϊ�Һ��Ӳ���
	//BinNode* succ() const;//��������µ�ֱ�Ӻ��
	template<typename VST> void travLevel(VST & fun) ;//������α���
	template<typename VST> void travPre(VST & fun) const;//�����������
	template<typename VST> void travMid(VST & fun) const;//�����������
	template<typename VST> void travPost(VST & fun) const;//�����������
};

//���ú���
template <class T> int BinNode<T>::getSize() const//��ȡ������ģ
{
	if (this == nullptr)
		return 0;
	else
		return 1 + lchild->getSize() + rchild->getSize();
}

template <class T> int BinNode<T>::getHeight() const//��ȡ�����߶�
{
	if (this == nullptr)
		return 0;
	int a;
	int b;
	a = lchild->getHeight();
	b = rchild->getHeight();
	return a > b ? (a + 1) : (b + 1);
}

template <class T> BinNode<T>* BinNode<T>::insertAsLc(const T & a)//��Ϊ���Ӳ���
{
	if (this != nullptr)
	{
		BinNode * p = new BinNode(a);
		lchild = p;
		return p;
	}
	return this;
}

template <class T> BinNode<T>* BinNode<T>::insertAsRc(const T & a)//��Ϊ�Һ��Ӳ���
{
	if (this != nullptr)
	{
		BinNode * p = new BinNode(a);
		rchild = p;
		return p;
	}
	return this;
}

template <class T> template<typename VST> void BinNode<T>::travLevel(VST & fun) //������α���
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

template <class T> template<typename VST> void BinNode<T>::travPre(VST & fun) const//�����������
{
	if (this != nullptr)
	{
		fun(data);
		lchild->travPre(fun);
		rchild->travPre(fun);
	}
}

template <class T> template<typename VST> void BinNode<T>::travMid(VST & fun) const//�����������
{
	if (this != nullptr)
	{
		lchild->travMid(fun);
		fun(data);
		rchild->travMid(fun);
	}
}

template <class T> template<typename VST> void BinNode<T>::travPost(VST & fun) const//�����������
{
	if (this != nullptr)
	{
		lchild->travPost(fun);
		rchild->travPost(fun);
		fun(data);
	}
}

/*������ģ����*/
template <class T> class BinTree
{
public:
	typedef BinNode<T>* iterator;
private:
	iterator root;//���ڵ�ָ��
	int height;//���߶�
	int size;//���Ĺ�ģ

public:
	/*���캯������������*/
	BinTree();
	BinTree(char* filename);
	~BinTree();
};

/*���캯������������*/
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
