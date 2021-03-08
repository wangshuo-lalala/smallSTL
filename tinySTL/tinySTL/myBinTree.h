#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;
//#define HEIGHT(p)  ((p) ? (p)->height : 0)//�ڵ�߶ȣ��涨�����߶�Ϊ0
//#define Balanced(x) (HEIGHT((x)->lchild) == HEIGHT((x)->rchild))//����ƽ��
//#define BalFac(x) (HEIGHT((x)->lchild) - HEIGHT((x)->rchild))//ƽ������
//#define AvlBalanced(x) ((-2 < BalFac(x)) && (BalFac(x) < 2))//AVL��ƽ������
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
	BinTree(T A[], T B[], int a1, int a2, int b1, int b2);//������1ǰ�����򹹽�������
	BinTree(char* filename);
	~BinTree();

	/*���ú���*/
	BinNode<T>* fileCon(FILE * f);
	BinNode<T>* preMid(T A[], T B[], int a1, int a2, int b1, int b2);//������1ǰ�����򹹽���������㹹��
	const int & getSize() const { return size; }//������Ĺ�ģ
	const int & getHeight() const { return height; }//��������
	BinNode<T>* getRoot() const { return root; }//��������ָ��
	bool isEmpty() const { return !root; }//�п�
	BinNode<T>* insertAsLc(BinNode<T>* x, const T & a, bool j);//��ڵ����
	BinNode<T>* insertAsRc(BinNode<T>* x, const T & a, bool j);//�ҽڵ����

	template<typename VST> void travLevel(VST & fun);//��α���
	/*�ݹ�*/
	template<typename VST> void travPreRe(VST & fun) const;//�������
	template<typename VST> void travMidRe(VST & fun) const;//�������
	template<typename VST> void travPostRe(VST & fun) const;//�������
	/*�ǵݹ�*/
	template<typename VST> void travPre(VST & fun) const;//�������
	template<typename VST> void travMid(VST & fun) const;//�������
	template<typename VST> void travPost(VST & fun) const;//�������

	
	void remove(BinNode<T>* x);/*ɾ����������*/
};

/*���캯������������*/
template <class T> BinTree<T>::BinTree()
{
	root = nullptr;
	height = 0;
	size = 0;
}

template <class T> BinNode<T>* BinTree<T>::preMid(T A[], T B[], int a1, int a2, int b1, int b2)//������1ǰ�����򹹽���������㹹��
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
template <class T> BinTree<T>::BinTree(T A[], T B[], int a1, int a2, int b1, int b2)//������1ǰ�����򹹽�������
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

template <class T> BinNode<T>* BinTree<T>::insertAsLc(BinNode<T>* x, const T & a, bool j)//��ڵ����
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
template <class T> BinNode<T>* BinTree<T>::insertAsRc(BinNode<T>* x, const T & a, bool j)//�ҽڵ����
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

template <class T> template<typename VST> void BinTree<T>::travLevel(VST & fun)//��α���
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

/*�ݹ�*/
template <class T> template<typename VST> void BinTree<T>::travPreRe(VST & fun) const//�������
{
	if (root != nullptr)
	{
		root->travPre(fun);
	}
}

template <class T> template<typename VST> void BinTree<T>::travMidRe(VST & fun) const//�������
{
	if (root != nullptr)
	{
		root->travMid(fun);
	}
}

template <class T> template<typename VST> void BinTree<T>::travPostRe(VST & fun) const//�������
{
	if (root != nullptr)
	{
		root->travPost(fun);
	}
}

/*�ǵݹ�*/
template <class T> template<typename VST> void BinTree<T>::travPre(VST & fun) const//�������
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

template <class T> template<typename VST> void BinTree<T>::travMid(VST & fun) const//�������
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

template <class T> template<typename VST> void BinTree<T>::travPost(VST & fun) const//�������
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