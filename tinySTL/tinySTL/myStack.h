#pragma once
#include <iostream>
using namespace std;

/*ջ��*/
template <class T> class MyStack
{
public:
	typedef T* iterator;
private:
	static const size_t min_capacity = 100;//��С����
	iterator s;//�׵�ַ
	size_t size;//Ԫ�ظ���
	size_t capacity;//����
	int top;//ջ��ָ��

public:
/*���캯������������*/
	MyStack();
	MyStack(const size_t & c);//��������
	MyStack(const MyStack & S);
	~MyStack();

/*���س�Ա����ֵ����*/
	const size_t & getAddress() const { return s; }//����Ԫ���׵�ַ
	const size_t & getSize() const { return size; }//����Ԫ�ظ���
	const size_t & getCapacity() const { return capacity; }//����ջ��ǰ����
	const T & getTop() const { if (top != -1) return s[top]; abort(); }//����ջ��Ԫ��

/*��Ա����*/
	bool isEmpty() const;//�Ƿ�Ϊ��
	void expand();//����
	void push(const T & n);//��ջ
	T pop();//��ջ
};

/*���캯��*/
template <class T> MyStack<T>::MyStack()
{
	size = 0;
	capacity = min_capacity;
	top = -1;
	s = new T[capacity];
}

template <class T> MyStack<T>::MyStack(const size_t & c)//��������
{
	size = 0;
	capacity = c > min_capacity ? c : min_capacity;
	top = -1;
	s = new T[capacity];
}

template <class T> MyStack<T>::MyStack(const MyStack & S)
{
	this->size = S.size;
	this->capacity = S.capacity;
	this->top = S.capacity;
	this->s = new T[capacity];
}

template <class T> MyStack<T>::~MyStack()
{
	delete[] s;
}

/*��Ա����*/
template <class T> bool MyStack<T>::isEmpty() const//�Ƿ�Ϊ��
{
	if (size == 0)
		return true;
	return false;
}

template <class T> void MyStack<T>::expand()//����
{
	iterator p = s;
	capacity = 2 * capacity;
	s = new T[capacity];
	for (size_t i = 0; i < size; ++i)
		s[i] = p[i];
	delete[] p;
}

template <class T> void MyStack<T>::push(const T & n)//��ջ
{
	if (size == capacity)
		expand();
	s[++top] = n;
	++size;
}

template <class T> T MyStack<T>::pop()//��ջ
{
	if (top == -1)
		abort();
	--size;
	T a = s[top];
	--top;
	return a;
}

