#pragma once
#include <iostream>
using namespace std;
template <class T>
class MyVector
{
public:
	typedef T* iterator;
/*��Ա����*/
private:
	static const size_t min_capacity = 3;//��С����
	size_t size;//Ԫ�ظ���
	size_t capacity;//����
	iterator vec;//�׵�ַ
	iterator begin;//ͷ������
	iterator end;//β������

public:
/*���캯������������*/
	MyVector();
	MyVector(const size_t & n);
	MyVector(const size_t & n, const T & a);
	MyVector(const MyVector& v);//��������*/
	~MyVector() { delete[] vec; };//�����������ͷſռ�

/*���س�Ա����ֵ�ĺ���*/
	const size_t & getSize() const { return size; }//����Ԫ�ظ���
	const size_t & getCapacity() const{ return capacity; }//���ؿռ�����
	const iterator & getAddress() const { return vec; }//����Ԫ���׵�ַ
	iterator getBegin() const { return begin; }//����ͷ������
	iterator getEnd() const { return end; }//����β������

/*���������*/
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

/*��������*/
	void expand();//����
	void shrink();//����

/*Ԫ�ز���*/
	bool isEmpty() const;//�ж��Ƿ�Ϊ��
	const T & at(const size_t & n) const;//����ָ��Ԫ��
	void insert(const size_t & n, const T & a);//�ڵ�n��λ���ϲ���Ԫ��n
	void pushBack(const T & a);//β����
	void remove(const size_t & n);//ɾ����Ԫ��
	void erase(const size_t & b, const size_t & e);////�ӵ�b��Ԫ����ɾ������e��Ԫ��
	void popBack();//βɾ��
	void clear();//���
	int find(const size_t & b, const size_t & e, const T & a) const;//��b-e����Ԫ��a���ɹ��������±꣬ʧ�ܷ���-1
	void unique();//Ԫ��Ψһ��
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

template <class T> MyVector<T>::MyVector(const MyVector& v)//��������
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

/*��������*/
template <class T> void MyVector<T>::expand()//����
{
	iterator p = vec;
	capacity = 2 * capacity;//���ݱ���
	vec = new T[capacity];
	for (size_t i = 0; i < size; ++i)
	{
		vec[i] = p[i];
	}
	begin = vec;
	end = &vec[size - 1];
	delete[] p;
}

template <class T> void MyVector<T>::shrink()//����
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

/*Ԫ�ز���*/
template <class T> bool MyVector<T>::isEmpty() const//�ж��Ƿ�Ϊ��
{
	if (size == 0)
		return true;
	return false;
}

template <class T> const T & MyVector<T>::at(const size_t & n) const//����ָ��Ԫ��
{
	if (n < size)
		return vec[n];
	abort();
}

template <class T> void MyVector<T>::insert(const size_t & n, const T & a)//�ڵ�n��λ���ϲ���Ԫ��n
{
	if (size == capacity)//������������������
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

template <class T> void MyVector<T>::pushBack(const T & a)//β����
{
	if (size == capacity)
		expand();
	vec[size] = a;
	++size;
	end = &vec[size - 1];
}

template <class T> void MyVector<T>::remove(const size_t & n)//ɾ����Ԫ��
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

template <class T> void MyVector<T>::erase(const size_t & b, const size_t & e)//�ӵ�b��Ԫ����ɾ������e��Ԫ��
{
	if (b < size && e < size)
	{
		for (size_t i = b; i <= e; ++i)
			remove(b);
	}
	else
		abort();
}

template <class T> void MyVector<T>::popBack()//βɾ��
{
	--size;
	shrink();
}

template <class T> void MyVector <T>::clear()//���
{
	size = 0;
	capacity = min_capacity;
	delete[] vec;
	vec = new T[capacity];
	begin = end = vec;
}

template <class T> int MyVector<T>::find(const size_t & b, const size_t & e, const T & a) const//��b-e����Ԫ��a���ɹ��������±꣬ʧ�ܷ���-1
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

template <class T> void MyVector<T>::unique()//Ԫ��Ψһ��
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