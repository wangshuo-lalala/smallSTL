#pragma once
#include <iostream>
using namespace std;        

/*链表结点定义*/
template <class T> struct  ListNode
{
	T data;
	ListNode * pre;//前驱
	ListNode * suc;//后继
	ListNode() : pre(nullptr), suc(nullptr) {}
	ListNode(const T & d,  ListNode *  p = nullptr,  ListNode * s = nullptr) : data(d), pre(p), suc(s) {}
};

/*链表模板类*/
template <class T> class MyList
{
public:
	typedef ListNode<T>* iterator;

private:
/*成员变量*/
	size_t size;//元素个数
	iterator header;//头节点指针
	iterator tailer; //尾节点指针

public:
/*构造函数及析构函数*/
	MyList();
	MyList(const MyList & L);
	~MyList();

/*返回成员变量值的函数*/
	const size_t & getSize() const { return size; }
	const iterator & getHeader() const { return header; }
	const iterator & getTailer() const { return tailer; }

/*运算符重载*/
	MyList & operator = (const MyList & L);
	friend ostream & operator << (ostream & os, const MyList & L)
	{
		iterator p = L.getHeader();
		iterator q = L.getTailer();
		p = p->suc;
		while (p != q)
		{
			os << p->data << ' ';
			p = p->suc;
		}
		return os;
	}
/*成员函数*/
	bool isEmpty() const;//是否为空
	iterator getIte(const size_t & n) const;//返回指定位置的指针
	iterator find(const T & n) const;//查找元素n并返回结点指针
	void clear();//清空出头尾结点之外的结点
	const T & at(const size_t n) const;//随机访问
	MyList & insert(iterator p, MyList & L);//在结点p之后插入一个链表
	void insertBefore(iterator p, const T & n);//在结点p前面插入元素n
	void insertAfter(iterator p, const T & n);//在结点p后面插入一个元素n
	void pushHead(const T & n);//头插入
	void pushTail(const T & n);//尾插入
	void popHead();//头删除
	void popTail();//尾删除
	void remove(iterator p);//删除单元素
	void erase(iterator b, iterator e);//删除一段
};


/*构造函数及析构函数*/
template <class T> MyList<T>::MyList()
{
	size = 0;
	header = new ListNode<T>();
	tailer = new ListNode<T>();
	header->suc = tailer;
	tailer->pre = header;
}

template <class T> MyList<T>::MyList(const MyList & L)
{
	size_t ls = L.getSize();
	this->size = ls;
	this->header = new ListNode<T>();
	this->tailer = new ListNode<T>();
	this->header->suc = tailer;
	this->tailer->pre = header;
	iterator h = L.getHeader();
	iterator t = L.getTailer();
	iterator p, q;
	h = h->suc;
	q = this->header;
	while (h != t)
	{
		p = new ListNode<T>(h->data);
		p->pre = q;
		p->suc = this->tailer;
		q->suc = p;
		this->tailer->pre = p;
		q = q->suc;
		h = h->suc;
	}
}

template <class T> MyList<T>::~MyList()
{
	clear();
	delete header;
	delete tailer;
}

/*运算符重载*/
template <class T> MyList<T> & MyList<T>::operator = (const MyList & L)
{
	if (this == &L)
		return *this;
	this->clear();
	iterator p, q, r, s;
	p = L.getHeader()->suc;
	q = L.getTailer();
	s = this->header;
	while (p != q)
	{
		r = new ListNode<T>(p->data);
		r->pre = s;
		r->suc = this->tailer;
		s->suc = r;
		tailer->pre = r;
		s = s->suc;
		p = p->suc;
	}
	return *this;
}

template <class T> void MyList<T>::clear()//清空出头尾结点之外的结点
{
	iterator p, q;
	p = header->suc;
	while (p != tailer)
	{
		q = p;
		p = p->suc;
		delete q;
	}
	header->suc = tailer;
	size = 0;
}

/*成员函数*/
template <class T> bool MyList<T>::isEmpty() const//是否为空
{
	if (size == 0)
		return true;
	return false;
}

template <class T> ListNode<T>* MyList<T>::getIte(const size_t & n) const//返回指定位置的指针
{
	iterator p = header;
	for (size_t i = 0; i <= n; ++i)
	{
		p = p->suc;
		if (p == tailer)
			abort();
	}
	return p;
}

template <class T> ListNode<T>* MyList<T>::find(const T & n) const//查找元素n并返回结点指针
{
	iterator p = header->suc;
	while (p != tailer)
	{
		if (p->data == n)
			return p;
		p = p->suc;
	}
	return nullptr;//未找到返回空
}


template <class T> const T & MyList<T>::at(const size_t n) const//随机访问
{
	iterator p = header;
	for (size_t i = 0; i <= n; ++i)
	{
		p = p->suc;
		if (p == tailer)
			abort();
	}
	return p->data;
}

template <class T> MyList<T> & MyList<T>::insert(iterator p, MyList & L)//在结点p之后插入一个链表
{
	if (this == &L || L.getSize() == 0)
		return *this;
	this->size += L.getSize();
	iterator q, s, r;
	s = L.getHeader();
	r = L.getTailer();
	q = p->suc;
	p->suc = s->suc;
	q->pre = r->pre;
	p->suc->pre = p;
	q->pre->suc = q;
	s->suc = r;
	r->pre = s;
	L.size = 0;
}

template <class T> void MyList<T>::insertBefore(iterator p, const T & n)//在结点p前面插入元素n
{
	iterator q = new ListNode<T>;
	q->data = n;
	q->suc = p;
	q->pre = p->pre;
	p->pre->suc = q;
	p->pre = q;
	++size;
}

template <class T> void MyList<T>::insertAfter(iterator p, const T & n)//在结点p后面插入一个元素n
{
	iterator q = new ListNode<T>;
	q->data = n;
	q->suc = p->suc;
	q->pre = p;
	p->suc->pre = q;
	p->suc = q;
	++size;
}

template <class T> void MyList<T>::pushHead(const T & n)//头插入
{
	iterator q = new ListNode<T>;
	q->data = n;
	q->suc = header->suc;
	q->pre = header;
	header->suc->pre = q;
	header->suc = q;
	++size;
}

template <class T> void MyList<T>::pushTail(const T & n)//尾插入
{
	iterator p = new ListNode<T>;
	p->data = n;
	p->suc = tailer;
	p->pre = tailer->pre;
	tailer->pre->suc = p;
	tailer->pre = p;
	++size;
}

template <class T> void MyList<T>::popHead()//头删除
{
	iterator q = header->suc;
	if (q != tailer)
	{
		header->suc = q->suc;
		header->suc->pre = header;
		delete q;
		--size;
	}
}

template <class T> void MyList<T>::popTail()//尾删除
{
	iterator q = tailer->pre;
	if (q != header)
	{
		tailer->pre = q->pre;
		tailer->pre->suc = tailer;
		delete q;
		--size;
	}
}

template <class T> void MyList<T>::remove(iterator p)//删除单元素
{
	p->pre->suc = p->suc;
	p->suc->pre = p->pre;
	delete p;
	--size;
}

template <class T> void MyList<T>::erase(iterator b, iterator e)//删除一段
{
	iterator q;
	while (b != e)
	{
		q = b;
		b = b->suc;
		remove(q);
	}
	remove(e);
}