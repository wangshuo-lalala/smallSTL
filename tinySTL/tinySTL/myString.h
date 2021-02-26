#pragma once
#include <iostream>
using namespace std;
class MyString
{
public:
	typedef char* iterator;
private:
	static const size_t min_capacity = 3;
	size_t npos;//������βָ���±�
	size_t size;//�ַ�����
	size_t length;//�ַ�������
	size_t capacity;//����
	iterator str;//�׵�ַ
	iterator begin;//ͷ������
	iterator end;//β������

public:
/*���캯������������*/
	MyString();
	MyString(const size_t & n);//��������
	MyString(const size_t & n, const char & c);//�ַ�����ʼ��Ϊn���ַ�c
	MyString(const iterator s);//�ַ�����ʼ��Ϊs
	MyString(const iterator s, const size_t & b, const size_t & e);//��ʼ��Ϊs��ǰn���ַ�
	MyString(const MyString & S);
	MyString(const MyString & S, const size_t & b ,const size_t & e);//��ʼ����b����β���ߴ�b��e
	~MyString();

/*���س�Ա����ֵ����*/
	const size_t & getSize() const { return size; }//����Ԫ�ظ���
	const size_t & getCapacity() const { return capacity; }//��������
	const size_t getLength() const { return length; }//�����ַ�������
	iterator getAddress() const { return str; }//�����׵�ַ
	iterator getBegin() const { return begin; }//����ͷ������
	iterator getEnd() const { return end; }//����β������
	const size_t & getNpos() const { return npos; }//��������βָ��


/*���������*/
	const MyString & operator = (const MyString & S);
	MyString operator + (const MyString & S);
	const MyString & operator +=(const MyString & S);
	char & operator [](const size_t & n) const;
	bool operator > (const MyString & S) const;
	bool operator < (const MyString & S) const;
	bool operator >= (const MyString & S) const;
	bool operator <= (const MyString & S) const;
	bool operator == (const MyString & S) const;
	bool operator != (const MyString & S) const;
	friend ostream & operator << (ostream & os, const MyString & S)
	{
		os << S.str << '\n';
		return os;
	}
	friend istream & operator >> (istream & is, MyString & S)
	{
		is >> S.str;
		for (size_t i = 0; S.str[i] != '\0'; ++i)
		{
			S.size++;
			S.length++;
			S.str[S.length] = '\0';
			S.begin = &(S.str[0]);
			S.end = &(S.str[S.length]);
		}
		return is;
	}

/*��Ա����*/
	void expand();//����
	void shrink();//����
	bool isEmpty() const;//�Ƿ�Ϊ��
	const char & at(const size_t & n) const;//����ָ��λ��Ԫ��
	void remove(const size_t & n);//ɾ����Ԫ��
	void erase(const size_t & b, const size_t & e);//ɾ��һ��Ԫ��
	void insert(const size_t & n, const char & ch, const size_t & num);//��λ��n�������ַ�ch,Ĭ��Ϊһ��
	bool compare(const char * s, const size_t & b , const size_t & e);//�ַ����Ƚ�
	void copy(const char * s, const size_t & b, const size_t & e);//�ַ�������
	void connect(const char * s, const size_t & b, const size_t & e);//�ַ�������
	int KMP(const char * s);//�����Ӵ�,���ڷ������������±�λ��
};

/*���캯������������*/
MyString::MyString()
{
	size = 0;
	length = 0;
	capacity = min_capacity;
	npos = capacity - 1;
	str = new char[capacity];
	str[0] = '\0';
	begin = end = &str[0];
}

MyString::MyString(const size_t & n)//��������
{
	size = 0;
	length = 0;
	capacity = min_capacity > n ? min_capacity : n;
	npos = capacity - 1;
	str = new char[capacity];
	str[0] = '\0';
	begin = end = &str[0];
}

MyString::MyString(const size_t & n, const char & c)//�ַ�����ʼ��Ϊn���ַ�c
{
	size = n;
	length = n;
	capacity = n + min_capacity;
	npos = capacity - 1;
	str = new char[capacity];
	size_t i;
	for (i = 0; i < n; ++i)
		str[i] = c;
	str[i] = '\0';
	begin = &str[0];
	end = &str[n];
}

MyString::MyString(const iterator s)//�ַ�����ʼ��Ϊs
{
	length = size = 0;
	while (s[length] != '\0')
	{
		if (s[length] != ' ' && s[length] != '	' && s[length] != '\n')
			++size;
		++length;
	}
	capacity = length + min_capacity;
	npos = capacity - 1;
	str = new char[capacity];
	size_t i;
	for (i = 0; i < length; ++i)
		str[i] = s[i];
	str[length] = '\0';
	begin = &str[0];
	end = &str[length];
}

MyString::MyString(const iterator s, const size_t & b, const size_t & e)//��ʼ��Ϊs�Ĵ�b��e����
{
	length = e - b + 1;
	capacity = length + min_capacity;
	npos = capacity - 1;
	str = new char[capacity];
	size_t i, j;
	for (i = 0, j = b; i < length; ++i, ++j)
	{
		if (s[j] != ' ' && s[j] != '	' && s[j] != '\n')
			++size;
		str[i] = s[j];
	}
	str[length] = '\0';
	begin = &str[0];
	end = &str[length];
}

MyString::MyString(const MyString & S)
{
	this->length = S.length;
	this->size = S.size;
	this->capacity = S.capacity;
	this->npos = S.capacity;
	this->str = new char[capacity];
	size_t i;
	for (i = 0; i < this->length; ++i)
		this->str[i] = S.str[i];
	this->str[i] = '\0';
	begin = &(this->str[0]);
	end = &(this->str[length]);
}

MyString::MyString(const MyString & S, const size_t & b, const size_t & e)//��ʼ����b����β���ߴ�b��e
{
	this->length = e - b + 1;
	this->capacity = this->length + this->min_capacity;
	this->npos = this->capacity - 1;
	this->str = new char[capacity];
	size_t i, j;
	for (i = 0, j = b; i < length; ++i, ++j)
	{
		if (S.str[j] != ' ' && S.str[j] != '	' && S.str[j] != '\n')
			++(this->size);
		this->str[i] = S.str[j];
	}
	this->str[i] = '\0';
	begin = &(this->str[0]);
	end = &(this->str[length]);
}

MyString::~MyString()
{
	delete[] str;
}

/*���������*/
const MyString & MyString::operator = (const MyString & S)
{
	if (this == &S)
		return *this;
	this->size = S.size;
	this->length = S.length;
	this->capacity = S.capacity;
	this->npos = S.npos;
	delete[] (this->str);
	this->str = new char[this->capacity];
	size_t i;
	for (i = 0; i < this->length; ++i)
		this->str[i] = S.str[i];
	this->str[i] = '\0';
	begin = &(this->str[0]);
	end = &(this->str[length]);
	return *this;
}

MyString MyString::operator + (const MyString & S)
{
	size_t c = this->length + S.length;
	MyString Res(c, '\0');
	Res.length = this->length + S.length - 1;
	Res.size = this->size + S.size;
	size_t i, j;
	for (i = 0, j = 0; j < this->length; ++i, ++j)
		Res.str[i] = this->str[j];
	for (j = 0; j < S.length; ++j)
		Res.str[i] = S.str[j];
	Res.str[i] = '\0';
	Res.begin = &(Res.str[0]);
	Res.end = &(Res.str[length]);
	return Res;
}

const MyString & MyString::operator +=(const MyString & S)
{
	*this = *this + S;
	return *this;
}

char & MyString::operator [](const size_t & n) const
{
	return str[n];
}

bool MyString::operator > (const MyString & S) const
{
	size_t i, j;
	for (i = 0, j = 0; i < this->length && j < S.length; ++i, ++j)
	{
		if (this->str[i] > S.str[j])
			return true;
		else if (this->str[i] < S.str[j])
			return false;
	}
	if (i != this->length && j == S.length)
		return true;
	return false;
}

bool MyString::operator < (const MyString & S) const
{
	size_t i, j;
	for (i = 0, j = 0; i < this->length && j < S.length; ++i, ++j)
	{
		if (this->str[i] > S.str[j])
			return false;
		else if (this->str[i] < S.str[j])
			return true;
	}
	if (i == this->length && j != S.length)
		return true;
	return false;
}

bool MyString::operator >= (const MyString & S) const
{
	if (!(*this < S))
		return true;
	return false;
}

bool MyString::operator <= (const MyString & S) const
{
	if (!(*this > S))
		return true;
	return false;
}

bool MyString::operator == (const MyString & S) const
{
	if (!(*this < S) && !(*this > S))
		return true;
	return false;
}

bool MyString::operator != (const MyString & S) const
{
	if (!(*this == S))
		return true;
	return false;
}

/*��Ա����*/
void MyString::expand()//����
{
	capacity = 2 * capacity;
	npos = capacity - 1;
	iterator p = str;
	str = new char[capacity];
	for (size_t i = 0; i <= length; ++i)
		str[i] = p[i];
	delete[] p;
	begin = &str[0];
	end = &str[length];
}

void MyString::shrink()//����
{
	capacity = length > min_capacity ? length : min_capacity;
	npos = capacity - 1;
	iterator p = str;
	str = new char[capacity];
	for (size_t i = 0; i <= length; ++i)
		str[i] = p[i];
	delete[] p;
	begin = &str[0];
	end = &str[length];
}

bool MyString::isEmpty() const//�Ƿ�Ϊ��
{
	if (size == 0)
		return true;
	return false;
}

const char & MyString::at(const size_t & n) const//����ָ��λ��Ԫ��
{
	return str[n];
}

void MyString::remove(const size_t & n)//ɾ����Ԫ��
{
	if (n < length)
	{
		if (str[n] != ' ' && str[n] != '	' && str[n] != '\n')
			--size;
		for (size_t i = n; i < length; ++i)
			str[i] = str[i + 1];
		--length;
		end = &str[length];
	}
	else
		abort();
}

void MyString::erase(const size_t & b, const size_t & e)//ɾ��һ��Ԫ��
{
	if (b <= e && e < length)
	{
		for (size_t i = b; i <= e; ++i)
			remove(i);
	}
	else
		abort();
}

void MyString::insert(const size_t & n, const char &  ch, const size_t & num = 1)//��λ��n�������ַ�ch,Ĭ��Ϊһ��
{
	if (n < length)
	{
		if (length + num < capacity)
			expand();
		if (ch != ' ' && ch != '	' && ch != '\n')
		{
			size += num;
		}
		length += num;
		size_t i;
		for (i = length; i >= n; --i)
		{
			str[i + num] = str[i];
		}
		while (i >= n - num)
		{
			str[i + num] = ch;
			--i;
		}
	}
	else
		abort();
}

bool MyString::compare(const char * s, const size_t & b = -1, const size_t & e = -1)//�ַ����Ƚ�
{
	size_t b_s, e_s;
	if (b == -1)
		b_s = 0;
	else
		b_s = b;
	if (e == -1)
	{
		size_t i;
		for (i = 0; i < length && s[b_s] != '\0'; ++i, ++b_s)
		{
			if (str[i] != s[b_s])
				return false;
		}
		if (i == length && s[b_s] == '\0')
			return true;
		return false;
	}
	else
	{
		e_s = e;
		size_t i;
		for (i = 0; i < length && b_s <= e_s; ++i, ++b_s)
		{
			if (str[i] != s[b_s])
				return false;
		}
		if (i == length && b_s == e_s)
			return true;
		return false;
	}
}

void MyString::copy(const char * s, const size_t & b = -1, const size_t & e = -1)//�ַ�������
{
	size_t sl = 0, ss = 0;
	if (b == -1 && e == -1)
	{
		for (size_t i = 0; s[i] != '\0'; ++i)
		{
			if (s[i] != ' ' && s[i] != '	' && s[i] != '\n')
				ss++;
			sl++;
		}
		if (capacity < sl)
		{
			capacity = sl + min_capacity;
			npos = capacity - 1;
			delete[] str;
			str = new char[capacity];
		}
		size = ss;
		for (size_t i = 0; i <= sl; ++i)
			str[i] = s[i];
		begin = &str[0];
		end = &str[length];
	}
	else if (b < e)
	{
		sl = e - b + 1;
		for (size_t i = b; i <= e; ++i)
		{
			if (s[i] != ' ' && s[i] != '	' && s[i] != '\n')
				ss++;
		}
		if (capacity < sl)
		{
			capacity = sl + min_capacity;
			npos = capacity - 1;
			delete[] str;
			str = new char[capacity];
		}
		size = ss;
		for (size_t i = 0, j = b; i <= sl; ++i, ++j)
			str[i] = s[j];
		begin = &str[0];
		end = &str[length];
	}
}

void MyString::connect(const char * s, const size_t & b = -1, const size_t & e = -1)//�ַ�������
{
	size_t sl = 0, ss = 0;
	if (b == -1 && e == -1)
	{
		for (size_t i = 0; s[i] != '\0'; ++i)
		{
			if (s[i] != ' ' && s[i] != '	' && s[i] != '\n')
				ss++;
			sl++;
		}
		while (capacity < sl + length)
		{
			expand();
		}
		size += ss;
		for (size_t i = length; i <= length + sl; ++i)
			str[i] = s[i];
		begin = &str[0];
		end = &str[length];
	}
	else if (b < e)
	{
		sl = e - b + 1;
		for (size_t i = b; i <= e; ++i)
		{
			if (s[i] != ' ' && s[i] != '	' && s[i] != '\n')
				ss++;
		}
		while (capacity < sl + length)
		{
			expand();
		}
		size += ss;
		for (size_t i = length, j = b; j <= e; ++i, ++j)
		{
			str[i] = s[j];
		}
		length += sl;
		str[length] = '\0';
		begin = &str[0];
		end = &str[length];
	}
}

int MyString::KMP(const char * s)//�����Ӵ�,���ڷ������������±�λ��
{
	int sl = 0;
	for (size_t i = 0; s[i] != '\0'; ++i)
		++sl;
	//����next����
	int * next = new int[sl];
	int i = 0, j = -1;
	next[0] = -1;
	while (s[i] != '\0')
	{
		if (j == -1 || s[i] == s[j])
		{
			++i;
			++j;
			next[i] = j;
		}
		else
			j = next[j];
	}
	i = j = 0;
	while (str[i] != '\0' && s[j] != '\0')
	{
		if (j == -1 || str[i] == s[j])
		{
			++i;
			++j;
		}
		else
			j = next[j];
	}
	delete[] next;
	if (s[j] == '\0')
		return i - j;
	return -1;
}