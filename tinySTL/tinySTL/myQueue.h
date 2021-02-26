#pragma once
#include <iostream>
using namespace std;

template <class T> class MyQueue
{
public:
	typedef T* iterator;
private:
	static const size_t min_capacity = 100;//��С����
	iterator que;//�׵�ַ
	size_t size;//Ԫ�ظ���
	size_t capacity;//����
	size_t front;//ͷָ��
	size_t rear;//βָ��

public:
	/*���캯������������*/
	MyQueue();
	MyQueue(const size_t & n);//��������
	MyQueue(const MyQueue & Q);
	~MyQueue();

	/*���س�Ա����ֵ����*/
	iterator getAddress() const { return que; }//�����׵�ַ
	const size_t & getSize() const { return size; }//����Ԫ�ظ���
	const size_t & getCapacity() const { return capacity; }//��������
	const T & getFront() const { return que[front]; }//���ض���Ԫ��
	const T & getRear() const { return que[rear - 1]; }//���ض�βԪ��

	/*��Ա����*/
	bool isEmpty() const;//�ж϶����Ƿ�Ϊ��
	void expand();//����
	void push(const T & n);//���
	T pop();//����
};

/*���캯������������*/
template <class T> MyQueue<T>::MyQueue()
{
	size = 0;
	capacity = min_capacity;
	que = new T[capacity];
	front = rear = 0;
}

template <class T> MyQueue<T>::MyQueue(const size_t & n)//��������
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

/*��Ա����*/
template <class T> bool MyQueue<T>::isEmpty() const//�ж϶����Ƿ�Ϊ��
{
	if (size == 0)
		return true;
	return false;
}

template <class T> void MyQueue<T>::expand()//����
{
	iterator p = que;
	capacity = 2 * capacity;
	que = new T[capacity];
	for (size_t i = front; i < rear; ++i)
		que[i] = p[i];
	delete[] p;
}

template <class T> void MyQueue<T>::push(const T & n)//���
{
	if (size == capacity)
		expand();
	que[rear++] = n;
	++size;
}

template <class T> T MyQueue<T>::pop()//����
{
	if (size == 0)
		abort();
	T re = que[front];
	front++;
	--size;
	return re;
}