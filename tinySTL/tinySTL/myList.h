#pragma once
#include <iostream>
using namespace std;        

/*�����㶨��*/
template <class T> struct  ListNode
{
	T data;
	ListNode * pre;//ǰ��
	ListNode * suc;//���
	ListNode() : pre(nullptr), suc(nullptr) {}
	ListNode(const T & d,  ListNode *  p = nullptr,  ListNode * s = nullptr) : data(d), pre(p), suc(s) {}
};

/*����ģ����*/
template <class T> class MyList
{
public:
	typedef ListNode<T>* iterator;

private:
/*��Ա����*/
	size_t size;//Ԫ�ظ���
	iterator header;//ͷ�ڵ�ָ��
	iterator tailer; //β�ڵ�ָ��

public:
/*���캯������������*/
	MyList();
	MyList(const MyList & L);
	~MyList();

/*���س�Ա����ֵ�ĺ���*/
	const size_t & getSize() const { return size; }
	const iterator & getHeader() const { return header; }
	const iterator & getTailer() const { return tailer; }

/*���������*/
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
/*��Ա����*/
	bool isEmpty() const;//�Ƿ�Ϊ��
	iterator getIte(const size_t & n) const;//����ָ��λ�õ�ָ��
	iterator find(const T & n) const;//����Ԫ��n�����ؽ��ָ��
	void clear();//��ճ�ͷβ���֮��Ľ��
	const T & at(const size_t n) const;//�������
	MyList & insert(iterator p, MyList & L);//�ڽ��p֮�����һ������
	void insertBefore(iterator p, const T & n);//�ڽ��pǰ�����Ԫ��n
	void insertAfter(iterator p, const T & n);//�ڽ��p�������һ��Ԫ��n
	void pushHead(const T & n);//ͷ����
	void pushTail(const T & n);//β����
	void popHead();//ͷɾ��
	void popTail();//βɾ��
	void remove(iterator p);//ɾ����Ԫ��
	void erase(iterator b, iterator e);//ɾ��һ��
};


/*���캯������������*/
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

/*���������*/
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

template <class T> void MyList<T>::clear()//��ճ�ͷβ���֮��Ľ��
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

/*��Ա����*/
template <class T> bool MyList<T>::isEmpty() const//�Ƿ�Ϊ��
{
	if (size == 0)
		return true;
	return false;
}

template <class T> ListNode<T>* MyList<T>::getIte(const size_t & n) const//����ָ��λ�õ�ָ��
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

template <class T> ListNode<T>* MyList<T>::find(const T & n) const//����Ԫ��n�����ؽ��ָ��
{
	iterator p = header->suc;
	while (p != tailer)
	{
		if (p->data == n)
			return p;
		p = p->suc;
	}
	return nullptr;//δ�ҵ����ؿ�
}


template <class T> const T & MyList<T>::at(const size_t n) const//�������
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

template <class T> MyList<T> & MyList<T>::insert(iterator p, MyList & L)//�ڽ��p֮�����һ������
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

template <class T> void MyList<T>::insertBefore(iterator p, const T & n)//�ڽ��pǰ�����Ԫ��n
{
	iterator q = new ListNode<T>;
	q->data = n;
	q->suc = p;
	q->pre = p->pre;
	p->pre->suc = q;
	p->pre = q;
	++size;
}

template <class T> void MyList<T>::insertAfter(iterator p, const T & n)//�ڽ��p�������һ��Ԫ��n
{
	iterator q = new ListNode<T>;
	q->data = n;
	q->suc = p->suc;
	q->pre = p;
	p->suc->pre = q;
	p->suc = q;
	++size;
}

template <class T> void MyList<T>::pushHead(const T & n)//ͷ����
{
	iterator q = new ListNode<T>;
	q->data = n;
	q->suc = header->suc;
	q->pre = header;
	header->suc->pre = q;
	header->suc = q;
	++size;
}

template <class T> void MyList<T>::pushTail(const T & n)//β����
{
	iterator p = new ListNode<T>;
	p->data = n;
	p->suc = tailer;
	p->pre = tailer->pre;
	tailer->pre->suc = p;
	tailer->pre = p;
	++size;
}

template <class T> void MyList<T>::popHead()//ͷɾ��
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

template <class T> void MyList<T>::popTail()//βɾ��
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

template <class T> void MyList<T>::remove(iterator p)//ɾ����Ԫ��
{
	p->pre->suc = p->suc;
	p->suc->pre = p->pre;
	delete p;
	--size;
}

template <class T> void MyList<T>::erase(iterator b, iterator e)//ɾ��һ��
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