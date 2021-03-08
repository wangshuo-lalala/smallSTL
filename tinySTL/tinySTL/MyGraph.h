#pragma once
#include <iostream>
using namespace std;
#define MaxSize 100
//图的结构定义

//邻接表表示法
//边结点定义
typedef struct EdgeNode
{
	int ver;//边指向的顶点序号
	struct EdgeNode * nextEdge;
}EdgeNode;
//顶点结点定义
typedef struct
{
	char verName;
	EdgeNode * fistEdge;
}Vertex;
//表定义
typedef struct
{
	Vertex ver[MaxSize];
	int n, e;//n，e分别表示顶点数和边数
}AGraph;

//邻接矩阵表示
typedef struct
{
	char verName[MaxSize];
	int edge[MaxSize][MaxSize];
	int n, e;//n，e分别表示顶点数和边数
}MGraph;

//邻接矩阵建图。
MGraph* createMGraph();
//邻接表建图
AGraph* createAGraph();
//深度优先搜索DFS
void DFS(AGraph* g, int v, int visit[]);
//广度优先搜索BFS
void BFS(AGraph* g, int v);
//Prim构建最小生成树
int Prim(MGraph* g, int v);
//克鲁斯卡尔构建最小生成树
typedef struct
{
	int a;
	int b;
	int w;
}Road;
int getRoot(int a);
int Kruskal(MGraph* g, Road road[], int n);
//迪杰斯特拉最短路径
void Dijkstra(MGraph* g, int v);
//弗洛伊德最短路径
void Floyd(MGraph* g);
//拓扑排序
int topSort(AGraph* g);
//关键路径

//邻接矩阵建图。
MGraph* createMGraph()
{
	int n, i, j, w;
	MGraph * g = (MGraph*)malloc(sizeof(MGraph));
	printf("please enter the number of the vertex:");
	scanf("%d", &n);
	g->n = n;
	for (i = 0; i < n; ++i)
		for (j = 0; j < n; ++j)
		{
			if (i == j)
				g->edge[i][j] = 0;
			else
				g->edge[i][j] = 12581;
		}
	g->e = 0;
	for (i = 0; i < n; ++i)
	{
		while (1)
		{
			printf("please enter the vertex and weight that connect with the %dth vertex(if no, enter -1):", i);
			scanf("%d,%d", &j, &w);
			if (j != -1)
			{
				g->edge[i][j] = w;
				++(g->e);
			}
			else
				break;
		}
		printf("over\n");
	}
	return g;
}
//邻接表建图
AGraph* createAGraph()
{
	int n, i, j;
	AGraph * g = (AGraph*)malloc(sizeof(AGraph));
	printf("please enter the number of the vertex:");
	scanf("%d", &n);
	g->n = n;
	for (i = 0; i < n; ++i)
	{
		g->ver[i].fistEdge = NULL;
	}
	for (i = 0; i < n; ++i)
	{
		EdgeNode * f = g->ver[i].fistEdge;
		while (1)
		{
			printf("please enter the vertex that connect with the %dth vertex(if no, enter -1):", i);
			scanf("%d", &j);
			if (j != -1)
			{
				EdgeNode * p = (EdgeNode*)malloc(sizeof(EdgeNode));
				p->ver = j;
				p->nextEdge = g->ver[i].fistEdge;
				g->ver[i].fistEdge = p;
				++(g->e);
			}
			else
				break;
		}
	}
	return g;
}

//深度优先搜索DFS

void DFS(AGraph* g, int v, int visit[])
{
	printf("%d\t", v);
	visit[v] = 1;
	EdgeNode * p = g->ver[v].fistEdge;
	while (p != NULL)
	{
		if (visit[p->ver] == 0)
			DFS(g, p->ver, visit);
		p = p->nextEdge;
	}
}
//广度优先搜索BFS
void BFS(AGraph* g, int v)
{
	int visit[MaxSize] = { 0 };
	int que[MaxSize];
	int front = 0, rear = 0;
	printf("%d\t", v);
	visit[v] = 1;
	que[rear++] = v;
	EdgeNode * p = NULL;
	while (front != rear)
	{
		v = que[front++];
		p = g->ver[v].fistEdge;
		while (p != NULL)
		{
			if (visit[p->ver] == 0)
			{
				printf("%d\t", p->ver);
				visit[p->ver] = 1;
				que[rear++] = p->ver;
			}
			p = p->nextEdge;
		}
	}
}

//Prim构建最小生成树
int Prim(MGraph* g, int v)
{
	int lowwight[MaxSize], visit[MaxSize] = { 0 };
	int i, j, k, min, sum = 0;
	for (i = 0; i < g->n; ++i)
	{
		lowwight[i] = g->edge[v][i];
	}
	printf("%d\t", v);
	visit[v] = 1;
	for (i = 0; i < g->n - 1; ++i)
	{
		min = 12580;
		for (j = 0; j < g->n; ++j)
			if (visit[j] == 0 && lowwight[j] < min)
			{
				min = lowwight[j];
				k = j;
			}
		printf("%d\t", k);
		visit[k] = 1;
		sum += lowwight[k];
		for (j = 0; j < g->n; ++j)
			if (visit[j] == 0 && g->edge[k][j] < lowwight[j])
				lowwight[j] = g->edge[k][j];
	}
	return sum;
}

//克鲁斯卡尔构建最小生成树
int father[MaxSize];//每个结点所指向的父节点
int getRoot(int a)
{
	while (a != father[a])
		a = father[a];
	return a;
}
int Kruskal(MGraph* g, Road road[], int n)
{
	int i;
	int a, b, sum = 0;
	for (i = 0; i < g->n; ++i)
		father[i] = i;
	for (i = 0; i < n; ++i)
	{
		a = getRoot(road[i].a);
		b = getRoot(road[i].b);
		if (a != b)
		{
			father[road[i].b] = road[i].a;
			sum += road[i].w;
		}
	}
	return sum;
}

//迪杰斯特拉最短路径
void Dijkstra(MGraph* g, int v)
{
	int path[MaxSize], visit[MaxSize], distance[MaxSize];
	int i, j, k, min, v0 = v;
	for (i = 0; i < g->n; ++i)
	{
		visit[i] = 0;
		distance[i] = g->edge[v][i];
		if (g->edge[v][i] < 12581)
			path[i] = v;
		else
			path[i] = -1;
	}
	path[v] = -1;
	printf("the shortest distance from %d to %d is %d\nthe path is:", v0, v, distance[v]);
	while (path[v] != -1)
	{
		printf("%d<-", v);
		v = path[v];
	}
	printf("%d", v0);
	printf("\n");
	v = v0;
	visit[v] = 1;

	for (i = 0; i < g->n - 1; ++i)
	{
		min = 10000;
		for (j = 0; j < g->n; ++j)
			if (visit[j] == 0 && distance[j] < min)
			{
				min = distance[j];
				k = j;
			}
		path[k] = v;
		v = k;
		printf("the shortest distance from %d to %d is %d\nthe path is:", v0, v, distance[v]);
		while (path[v] != -1)
		{
			printf("%d<-", v);
			v = path[v];
		}
		printf("%d", v0);
		printf("\n");
		v = k;
		visit[v] = 1;

		for (j = 0; j < g->n; ++j)
			if (visit[j] == 0 && g->edge[v][j] + distance[v] < distance[j])
			{
				distance[j] = g->edge[v][j] + distance[v];
				path[j] = v;
			}
	}
}

//弗洛伊德最短路径
void Floyd(MGraph* g)
{
	int path[MaxSize][MaxSize], A[MaxSize][MaxSize];
	int i, j, k;
	for (i = 0; i < g->n; ++i)
		for (j = 0; j < g->n; ++j)
		{
			A[i][j] = g->edge[i][j];
			path[i][j] = -1;
		}
	for (k = 0; k < g->n; ++k)
		for (i = 0; i < g->n; ++i)
			for (j = 0; j < g->n; ++j)
				if (A[i][j] > A[i][k] + A[k][j])
				{
					path[i][j] = k;
					A[i][j] = A[i][k] + A[k][j];
				}
	for (i = 0; i < g->n; ++i)
		for (j = 0; j < g->n; ++j)
		{
			printf("the shortest distance from %d to %d is %d\n", i, j, A[i][j]);
			printf("the path is:%d", j);
			k = path[i][j];
			while (k != -1)
			{
				printf("<-%d", k);
				k = path[i][k];
			}
			printf("<-%d\n", i);
		}
}

//拓扑排序
int topSort(AGraph* g)
{
	int deg[MaxSize] = { 0 };
	int i, n = 0;
	EdgeNode * p = NULL;
	int s[MaxSize], top = -1;
	for (i = 0; i < g->n; ++i)
	{
		p = g->ver[i].fistEdge;
		while (p != NULL)
		{
			++deg[p->ver];
			p = p->nextEdge;
		}
	}
	for (i = 0; i < g->n; ++i)
		if (deg[i] == 0)
			s[++top] = i;
	printf("\n");
	while (top != -1)
	{
		i = s[top--];
		printf("%d\t", i);
		++n;
		p = g->ver[i].fistEdge;
		while (p != NULL)
		{
			--deg[p->ver];
			if (deg[p->ver] == 0)
				s[++top] = p->ver;
			p = p->nextEdge;
		}
	}
	if (n == g->n)
		return 1;
	return 0;
}