#pragma once
#include <iostream>
using namespace std;
template <class T>
class MyVector
{
public:
	typedef T* iterator;
/*成员变量*/
private:
	static const size_t min_capacity = 3;//最小容量
	size_t size;//元素个数
	size_t capacity;//容量
	iterator vec;//首地址
	iterator begin;//头迭代器
	iterator end;//尾迭代器

public:
/*构造函数及析构函数*/
	MyVector();
	MyVector(const size_t & n);
	MyVector(const size_t & n, const T & a);
	MyVector(const MyVector& v);//拷贝构造*/
	~MyVector() { delete[] vec; };//析构函数，释放空间

/*返回成员变量值的函数*/
	const size_t & getSize() const { return size; }//返回元素个数
	const size_t & getCapacity() const{ return capacity; }//返回空间容量
	const iterator & getAddress() const { return vec; }//返回元素首地址
	iterator getBegin() const { return begin; }//返回头迭代器
	iterator getEnd() const { return end; }//返回尾迭代器

/*运算符重载*/
	MyVector & operator = (const MyVector & v);
	bool  operator != (const MyVector & v) const;
	bool  operator == (const MyVector & v) const;
	bool  operator > (const MyVector & v) const;
	bool  operator < (const MyVector & v) const;
	T & operator [] (size_t n);
	friend ostream & operator << (ostream & os, const MyVector & v)
	{
		for (size_t i = 0; i < v.size; ++i)
			os << v.vec[i] << ' ';
		return os;
	}

/*容量操作*/
	void expand();//扩容
	void shrink();//缩容

/*元素操作*/
	bool isEmpty() const;//判断是否为空
	const T & at(const size_t & n) const;//返回指定元素
	void insert(const size_t & n, const T & a);//在第n个位置上插入元素n
	void pushBack(const T & a);//尾插入
	void remove(const size_t & n);//删除单元素
	void erase(const size_t & b, const size_t & e);////从第b个元素起删除到第e个元素
	void popBack();//尾删除
	void clear();//清空
	int find(const size_t & b, const size_t & e, const T & a) const;//从b-e查找元素a，成功返回其下标，失败返回-1
	void unique();//元素唯一化
};

template <class T> MyVector<T>::MyVector()
{
	size = 0;
	capacity = min_capacity;
	vec = new T[capacity];
	begin = end = vec;
}

template <class T> MyVector<T>::MyVector(const size_t & n)
{
	size = n;
	if (n < min_capacity)
		capacity = min_capacity;
	else
		capacity = n;
	vec = new T[capacity];
	begin = vec;
	end = &vec[size - 1];
}

template <class T> MyVector<T>::MyVector(const size_t & n, const T & a)
{
	size = n;
	if (n < min_capacity)
		capacity = min_capacity;
	else
		capacity = n;
	vec = new T[capacity];
	for (size_t i = 0; i < size; ++i)
		vec[i] = a;
	begin = vec;
	end = &vec[size - 1];
}

template <class T> MyVector<T>::MyVector(const MyVector& v)//拷贝构造
{
	size_t vs = v.getSize();
	this->size = vs;
	this->capacity = v.getCapacity();
	this->vec = new T[this->capacity];
	for (size_t i; i < this->size; ++i)
		this->vec[i] = v.getAddress()[i];
	this->begin = this->vec;
	this->end = &(this->vec[size - 1]);
}

template <class T> MyVector<T> & MyVector<T>::operator = (const MyVector & v)
{
	if (this = &v)
		return *this;
	delete[] this->vec;
	this->size = v.getSize();
	this->capacity = v.getCapacity();
	this->vec = new T[this->capacity];
	for (size_t i; i < this->size; ++i)
		this->vec[i] = v.getAddress[i];
	this->begin = this->vec;
	this->end = &(this->vec[size - 1]);
	return *this;
}

template <class T> bool  MyVector<T>::operator != (const MyVector & v) const
{
	size_t vs = v.getSize();
	iterator vvec = v.getAddress();
	if (this->size != vs)
		return true;
	else
	{
		for (size_t i = 0; i < this->size; ++i)
			if (this->vec[i] != vvec[i])
				return true;
		return false;
	}
}

template <class T> bool  MyVector<T>::operator == (const MyVector & v) const
{
	if (!(*this != v))
		return true;
	else
		return false;
}

template <class T> bool  MyVector<T>::operator > (const MyVector & v) const
{
	size_t vs = v.getSize();
	iterator vvec = v.getAddress();
	for (size_t i = 0; i < this->size && i < vs; ++i)
	{
		if (this->vec[i] < vvec[i])
			return false;
		else if (this->vec[i] > vvec[i])
			return true;
	}
	return this->size - vs;
}

template <class T> bool  MyVector<T>::operator < (const MyVector & v) const
{
	if ((*this != v) && !(*this > v))
		return true;
	else
		return false;
}

template <class T> T & MyVector<T>::operator [] (size_t n)
{
	if (n < this->size)
		return vec[n];
	abort();
}

/*容量操作*/
template <class T> void MyVector<T>::expand()//扩容
{
	iterator p = vec;
	capacity = 2 * capacity;//扩容倍数
	vec = new T[capacity];
	for (size_t i = 0; i < size; ++i)
	{
		vec[i] = p[i];
	}
	begin = vec;
	end = &vec[size - 1];
	delete[] p;
}

template <class T> void MyVector<T>::shrink()//缩容
{
	if (size == capacity)
		return;
	capacity = size > min_capacity ? size : min_capacity;
	iterator p = vec;
	vec = new T[capacity];
	for (size_t i = 0; i < size; ++i)
	{
		vec[i] = p[i];
	}
	begin = vec;
	end = &vec[size - 1];
	delete[] p;
}

/*元素操作*/
template <class T> bool MyVector<T>::isEmpty() const//判断是否为空
{
	if (size == 0)
		return true;
	return false;
}

template <class T> const T & MyVector<T>::at(const size_t & n) const//返回指定元素
{
	if (n < size)
		return vec[n];
	abort();
}

template <class T> void MyVector<T>::insert(const size_t & n, const T & a)//在第n个位置上插入元素n
{
	if (size == capacity)//若容量不够需先扩容
		expand();
	if (n < size)
	{
		for (size_t i = size; i > n; --i)
			vec[i] = vec[i - 1];
		vec[n] = a;
		++size;
		end = &vec[size - 1];
	}
	else
		abort();
}

template <class T> void MyVector<T>::pushBack(const T & a)//尾插入
{
	if (size == capacity)
		expand();
	vec[size] = a;
	++size;
	end = &vec[size - 1];
}

template <class T> void MyVector<T>::remove(const size_t & n)//删除单元素
{
	if (n < size)
	{
		for (size_t i = n; i < size - 1; ++i)
			vec[i] = vec[i + 1];
		--size;
		shrink();

	}
	else
		abort();
}

template <class T> void MyVector<T>::erase(const size_t & b, const size_t & e)//从第b个元素起删除到第e个元素
{
	if (b < size && e < size)
	{
		for (size_t i = b; i <= e; ++i)
			remove(b);
	}
	else
		abort();
}

template <class T> void MyVector<T>::popBack()//尾删除
{
	--size;
	shrink();
}

template <class T> void MyVector <T>::clear()//清空
{
	size = 0;
	capacity = min_capacity;
	delete[] vec;
	vec = new T[capacity];
	begin = end = vec;
}

template <class T> int MyVector<T>::find(const size_t & b, const size_t & e, const T & a) const//从b-e查找元素a，成功返回其下标，失败返回-1
{
	if (b < size && e < size)
	{
		for (size_t i = b; i <= e; ++i)
			if (vec[i] == a)
				return i;
		return -1;
	}
	else
		abort();
}

template <class T> void MyVector<T>::unique()//元素唯一化
{
	if (size == 1)
		return;
	for (size_t i = 1; i < size;)
	{
		if (find(0, i - 1, vec[i]) != -1)
			remove(i);
		else
			++i;
	}
}