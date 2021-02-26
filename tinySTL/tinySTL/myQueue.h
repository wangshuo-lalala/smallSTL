#pragma once
#include <iostream>
using namespace std;

template <class T> class MyQueue
{
public:
	typedef T* iterator;
private:
	static const size_t min_capacity = 100;//最小容量
	iterator que;//首地址
	size_t size;//元素个数
	size_t capacity;//容量
	size_t front;//头指针
	size_t rear;//尾指针

public:
	/*构造函数及析构函数*/
	MyQueue();
	MyQueue(const size_t & n);//传入容量
	MyQueue(const MyQueue & Q);
	~MyQueue();

	/*返回成员变量值函数*/
	iterator getAddress() const { return que; }//返回首地址
	const size_t & getSize() const { return size; }//返回元素个数
	const size_t & getCapacity() const { return capacity; }//返回容量
	const T & getFront() const { return que[front]; }//返回队首元素
	const T & getRear() const { return que[rear - 1]; }//返回队尾元素

	/*成员函数*/
	bool isEmpty() const;//判断队列是否为空
	void expand();//扩容
	void push(const T & n);//入队
	T pop();//出队
};

/*构造函数及析构函数*/
template <class T> MyQueue<T>::MyQueue()
{
	size = 0;
	capacity = min_capacity;
	que = new T[capacity];
	front = rear = 0;
}

template <class T> MyQueue<T>::MyQueue(const size_t & n)//传入容量
{
	size = 0;
	capacity = n > min_capacity ? n : min_capacity;
	que = new T[capacity];
	front = rear = 0;
}

template <class T> MyQueue<T>::MyQueue(const MyQueue & Q)
{
	this->size = Q.size;
	this->capacity = Q.capacity;
	this->que = new T[capacity];
	this->front = Q.front;
	this->rear = Q.rear;
	for (size_t i = this->front; i < this->rear; ++i)
		this->que[i] = Q.que[i];
}

template <class T> MyQueue<T>::~MyQueue()
{
	delete[] que;
}

/*成员函数*/
template <class T> bool MyQueue<T>::isEmpty() const//判断队列是否为空
{
	if (size == 0)
		return true;
	return false;
}

template <class T> void MyQueue<T>::expand()//扩容
{
	iterator p = que;
	capacity = 2 * capacity;
	que = new T[capacity];
	for (size_t i = front; i < rear; ++i)
		que[i] = p[i];
	delete[] p;
}

template <class T> void MyQueue<T>::push(const T & n)//入队
{
	if (size == capacity)
		expand();
	que[rear++] = n;
	++size;
}

template <class T> T MyQueue<T>::pop()//出队
{
	if (size == 0)
		abort();
	T re = que[front];
	front++;
	--size;
	return re;
}