#pragma once
#include <iostream>
using namespace std;

/*树节点类*/
template <class T> struct TreeNode
{
	T data;//结点元素
	size_t height;//子树高度  
	TreeNode * brother;//兄弟结点
	TreeNode * father;//父结点
	TreeNode * child;//子结点
	/*构造函数*/
	TreeNode() { height = 1; father = nullptr; brother = nullptr; child = nullptr; }
	TreeNode(const T & d, TreeNode * f = nullptr, TreeNode * b = nullptr, TreeNode * c = nullptr) { height = 1; father = f; brother = b; child = c; data = d; }
	size_t  size() const;//获取子树规模
	TreeNode * insertAsChild(const T & a);//作为孩子插入
	TreeNode * insertAsBrother(const T & a);//作为兄弟插入
	
	template <class VST> void preTrav(VST & fun) const;//子树前序遍历
	template <class VST> void postTrav(VST & fun) const;//子树后序遍历
};

/*树模板类*/
template <class T> class Tree
{
public:
	typedef TreeNode<T>* iterator;

private:
	size_t height;
	size_t size;//树的规模
	iterator root;//根节点

public:
	/*构造函数及析构函数*/
	Tree();
	~Tree();

	void remove(iterator p);
};

template <class T> size_t  TreeNode<T>::size() const//获取子树规模
{
	if (this == nullptr)
		return 0;
	else
		return 1 + child->size() + brother->size();
}

template <class T> TreeNode<T> * TreeNode<T>::insertAsChild(const T & a)//作为孩子插入
{
	if (this == nullptr)
		return nullptr;
	child = new TreeNode(a, this);
	++height;
	return child;
}

template <class T> TreeNode<T> * TreeNode<T>::insertAsBrother(const T & a)//作为兄弟插入
{
	if (this == nullptr)
		return nullptr;
	brother = new TreeNode(a, this);
	return brother;
}


template <class T> template <class VST> void TreeNode<T>::preTrav(VST & fun) const//子树前序遍历
{
	if (this == nullptr)
		return;
	fun(this->data);
	this->child->preTrav(fun);
	this->brother->preTrav(fun);
}

template <class T> template <class VST> void TreeNode<T>::postTrav(VST & fun) const//子树后序遍历
{
	if (this == nullptr)
		return;
	fun(this->data);
	this->brother->postTrav(fun);
	this->child->postTrav(fun);
}

/*构造函数及析构函数*/
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