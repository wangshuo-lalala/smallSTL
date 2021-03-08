#pragma once
#include <iostream>
using namespace std;
#define MaxSize 100
/*�����㷨*/
template <class T> int myFind(T a[], int n, T x) const//˳�����
{
	for (int i = 0; i < n; ++i)
	{
		if (x == a[i])
			return i;
	}
	return -1;//δ���ҵ���Ԫ�ط���-1
}

/*�����㷨*/
//ֱ�Ӳ�������
void insertSort(int A[], int n);

//��������
void bubbleSort(int A[], int n);

//��������
void quickSort(int A[], int low, int high);

//��ѡ������
void selectSort(int A[], int n);

//������
void heapSort(int A[], int n);

//��·�鲢����
void mergeSort(int A[], int low, int high);

//ֱ�Ӳ�������
void insertSort(int A[], int n)
{
	if (n <= 1)
		return;
	int i, j, temp;
	for (i = 1; i < n; ++i)
	{
		j = i - 1;
		temp = A[i];
		while (j >= 0 && temp < A[j])
		{
			A[j + 1] = A[j];
			--j;
		}
		A[j + 1] = temp;
	}
}

//��������
void bubbleSort(int A[], int n)
{
	if (n <= 1)
		return;
	int i, j, temp;
	int flag;
	for (i = n - 1; i > 0; --i)
	{
		flag = 0;
		for (j = 0; j < i; ++j)
			if (A[j] > A[j + 1])
			{
				temp = A[j];
				A[j] = A[j + 1];
				A[j + 1] = temp;
				flag = 1;
			}
		if (flag == 0)
			return;
	}
}

//��������
void quickSort(int A[], int low, int high)
{
	if (low < high)
	{
		int i = low;
		int j = high;
		int temp = A[low];
		while (i < j)
		{
			while (i < j && A[j] > temp)
				--j;
			if (i < j)
			{
				A[i] = A[j];
				++i;
			}
			while (i < j && A[i] < temp)
				++i;
			if (i < j)
			{
				A[j] = A[i];
				--j;
			}
		}
		A[i] = temp;
		quickSort(A, low, i - 1);
		quickSort(A, i + 1, high);
	}
}

//��ѡ������
void selectSort(int A[], int n)
{
	if (n <= 1)
		return;
	int i, j, k, temp;
	for (i = n - 1; i > 0; --i)
	{
		k = i;
		for (j = 0; j < i; ++j)
			if (A[j] > A[k])
			{
				k = j;
			}
		temp = A[i];
		A[i] = A[k];
		A[k] = temp;
	}
}

//������
//��low��high�ж�low�ϵĽ����е���
void shift(int A[], int low, int high)
{
	int i = low;
	int j = 2 * i + 1;
	int temp = A[i];
	while (j <= high)
	{
		if (j < high && A[j] < A[j + 1])
			++j;
		if (temp < A[j])
		{
			A[i] = A[j];
			i = j;
			j = 2 * i + 1;
		}
		else
			break;
	}
	A[i] = temp;
}
void heapSort(int A[], int n)
{
	int i, temp;
	for (i = (n - 2) / 2; i >= 0; --i)
		shift(A, i, n - 1);
	for (i = n - 1; i >= 1; --i)
	{
		temp = A[0];
		A[0] = A[i];
		A[i] = temp;
		shift(A, 0, i - 1);
	}
}

//��·�鲢����
void Merge(int A[], int low, int mid, int high)
{
	int m = mid - low + 1;
	int n = high - mid;
	int i, j, k = low;
	int * B = (int*)malloc(m * sizeof(int));
	int * C = (int*)malloc(n * sizeof(int));
	i = 0;
	j = 0;
	while (i < m)
		B[i++] = A[k++];
	while (j < n)
		C[j++] = A[k++];
	k = low;
	i = 0;
	j = 0;
	while (i < m && j < n)
	{
		if (B[i] < C[j])
			A[k++] = B[i++];
		else
			A[k++] = C[j++];
	}
	while (i < m)
		A[k++] = B[i++];
	while (j < n)
		A[k++] = C[j++];
}
void mergeSort(int A[], int low, int high)
{
	if (low < high)
	{
		int mid = (low + high) / 2;
		mergeSort(A, low, mid);
		mergeSort(A, mid + 1, high);
		Merge(A, low, mid, high);
	}
}