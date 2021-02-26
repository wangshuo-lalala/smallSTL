#pragma once
#include <iostream>
using namespace std;

/*栈类*/
template <class T> class MyStack
{
public:
	typedef T* iterator;
private:
	static const size_t min_capacity = 100;//最小容量
	iterator s;//首地址
	size_t size;//元素个数
	size_t capacity;//容量
	int top;//栈顶指针

public:
/*构造函数及析构函数*/
	MyStack();
	MyStack(const size_t & c);//传入容量
	MyStack(const MyStack & S);
	~MyStack();

/*返回成员变量值函数*/
	const size_t & getAddress() const { return s; }//返回元素首地址
	const size_t & getSize() const { return size; }//返回元素个数
	const size_t & getCapacity() const { return capacity; }//返回栈当前容量
	const T & getTop() const { if (top != -1) return s[top]; abort(); }//返回栈顶元素

/*成员函数*/
	bool isEmpty() const;//是否为空
	void expand();//扩容
	void push(const T & n);//入栈
	T pop();//出栈
};

/*构造函数*/
template <class T> MyStack<T>::MyStack()
{
	size = 0;
	capacity = min_capacity;
	top = -1;
	s = new T[capacity];
}

template <class T> MyStack<T>::MyStack(const size_t & c)//传入容量
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

/*成员函数*/
template <class T> bool MyStack<T>::isEmpty() const//是否为空
{
	if (size == 0)
		return true;
	return false;
}

template <class T> void MyStack<T>::expand()//扩容
{
	iterator p = s;
	capacity = 2 * capacity;
	s = new T[capacity];
	for (size_t i = 0; i < size; ++i)
		s[i] = p[i];
	delete[] p;
}

template <class T> void MyStack<T>::push(const T & n)//入栈
{
	if (size == capacity)
		expand();
	s[++top] = n;
	++size;
}

template <class T> T MyStack<T>::pop()//出栈
{
	if (top == -1)
		abort();
	--size;
	T a = s[top];
	--top;
	return a;
}

