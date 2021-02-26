#pragma once
#include <iostream>
using namespace std;

/*���ڵ���*/
template <class T> struct TreeNode
{
	T data;//���Ԫ��
	size_t height;//�����߶�  
	TreeNode * brother;//�ֵܽ��
	TreeNode * father;//�����
	TreeNode * child;//�ӽ��
	/*���캯��*/
	TreeNode() { height = 1; father = nullptr; brother = nullptr; child = nullptr; }
	TreeNode(const T & d, TreeNode * f = nullptr, TreeNode * b = nullptr, TreeNode * c = nullptr) { height = 1; father = f; brother = b; child = c; data = d; }
	size_t  size() const;//��ȡ������ģ
	TreeNode * insertAsChild(const T & a);//��Ϊ���Ӳ���
	TreeNode * insertAsBrother(const T & a);//��Ϊ�ֵܲ���
	
	template <class VST> void preTrav(VST & fun) const;//����ǰ�����
	template <class VST> void postTrav(VST & fun) const;//�����������
};

/*��ģ����*/
template <class T> class Tree
{
public:
	typedef TreeNode<T>* iterator;

private:
	size_t height;
	size_t size;//���Ĺ�ģ
	iterator root;//���ڵ�

public:
	/*���캯������������*/
	Tree();
	~Tree();

	void remove(iterator p);
};

template <class T> size_t  TreeNode<T>::size() const//��ȡ������ģ
{
	if (this == nullptr)
		return 0;
	else
		return 1 + child->size() + brother->size();
}

template <class T> TreeNode<T> * TreeNode<T>::insertAsChild(const T & a)//��Ϊ���Ӳ���
{
	if (this == nullptr)
		return nullptr;
	child = new TreeNode(a, this);
	++height;
	return child;
}

template <class T> TreeNode<T> * TreeNode<T>::insertAsBrother(const T & a)//��Ϊ�ֵܲ���
{
	if (this == nullptr)
		return nullptr;
	brother = new TreeNode(a, this);
	return brother;
}


template <class T> template <class VST> void TreeNode<T>::preTrav(VST & fun) const//����ǰ�����
{
	if (this == nullptr)
		return;
	fun(this->data);
	this->child->preTrav(fun);
	this->brother->preTrav(fun);
}

template <class T> template <class VST> void TreeNode<T>::postTrav(VST & fun) const//�����������
{
	if (this == nullptr)
		return;
	fun(this->data);
	this->brother->postTrav(fun);
	this->child->postTrav(fun);
}

/*���캯������������*/
template <class T> Tree<T>::Tree()
{
	size = 0;
	height = 0;
	root = new TreeNode;
}

template <class T> Tree<T>::~Tree()
{
	remove(root);
}

template <class T> void Tree<T>::remove(iterator p)
{
	if (p != nullptr)
	{
		remove(p->child);
		remove(p->brother);
		remove(p);
	}
}