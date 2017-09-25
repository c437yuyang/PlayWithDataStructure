#include "stdio.h"    
#include "stdlib.h"   
#include "io.h"  
#include "math.h"  
#include "time.h"

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAXEDGE 20
#define MAXVEX 20
#define INFINITY 65535

typedef int Status;	/* Status是函数的类型,其值是函数结果状态代码，如OK等 */

typedef struct
{
	int arc[MAXVEX][MAXVEX];
	int numVertexes, numEdges;
}MGraph;

void CreateMGraph(MGraph *G)/* 构件图 */
{
	int i, j;

	/* printf("请输入边数和顶点数:"); */
	G->numEdges = 15;
	G->numVertexes = 9;

	for (i = 0; i < G->numVertexes; i++)/* 初始化图 */
	{
		for (j = 0; j < G->numVertexes; j++)
		{
			if (i == j)
				G->arc[i][j] = 0;
			else
				G->arc[i][j] = G->arc[j][i] = INFINITY;
		}
	}

	G->arc[0][1] = 10;
	G->arc[0][5] = 11;
	G->arc[1][2] = 18;
	G->arc[1][8] = 12;
	G->arc[1][6] = 16;
	G->arc[2][8] = 8;
	G->arc[2][3] = 22;
	G->arc[3][8] = 21;
	G->arc[3][6] = 24;
	G->arc[3][7] = 16;
	G->arc[3][4] = 20;
	G->arc[4][7] = 7;
	G->arc[4][5] = 26;
	G->arc[5][6] = 17;
	G->arc[6][7] = 19;

	for (i = 0; i < G->numVertexes; i++) //无向图
	{
		for (j = i; j < G->numVertexes; j++)
		{
			G->arc[j][i] = G->arc[i][j];
		}
	}

}

/* Prim算法生成最小生成树  */

//本身prim算法贪心原则是:每次找到可能加入已知点集中且能够形成树的最小权值边加入到生成树
//这个过程总的来说:
//这个算法的话，就是先从V0开始，找到一个最小的，加入点集，
//然后对找到的这个点，再看它周围的最小权值和之前的一起找最小权值再来加入到最小生成树
void MiniSpanTree_Prim(MGraph G)
{
	int min, i, j, k;
	int adjvex[MAXVEX];		/* 保存相关顶点下标 */
	int lowcost[MAXVEX];	/* 保存相关顶点间边的权值 */
	//adjvex里面装的是一条边的出发顶点
	//lowcost里面装的是所有还未加入最小生成树到当前所有最小生成树上结点的权值
	lowcost[0] = 0;/* 初始化第一个权值为0，即v0加入生成树 */
			/* lowcost的值为0，在这里就是此下标的顶点已经加入生成树 */
	adjvex[0] = 0;			/* 初始化第一个顶点下标为0 */
	for (i = 1; i < G.numVertexes; i++)	/* 循环除下标为0外的全部顶点 */
	{
		lowcost[i] = G.arc[0][i];	/* 将v0顶点与之有边的权值存入数组 */
		adjvex[i] = 0;					/* 初始化都为v0的下标 */
	}
	for (i = 1; i < G.numVertexes; i++)
	{
		min = INFINITY;	/* 初始化最小权值为∞， */
						/* 通常设置为不可能的大数字如32767、65535等 */
		j = 1; k = 0;
		while (j < G.numVertexes)	/* 循环全部顶点 */
		{
			if (lowcost[j] != 0 && lowcost[j] < min)/* 如果权值不为0且权值小于min */
			{
				min = lowcost[j];	/* 则让当前权值成为最小值 */
				k = j;			/* 将当前最小值的下标存入k */
			}
			j++;
		}
		printf("(%d, %d),权值:%d\n", adjvex[k], k,min);/* 打印当前顶点边中权值最小的边 */
		lowcost[k] = 0;/* 将当前顶点的权值设置为0,表示此顶点已经完成任务 */
		for (j = 1; j < G.numVertexes; j++)	/* 循环所有顶点 */
		{
			if (lowcost[j] != 0 && G.arc[k][j] < lowcost[j])
			{/* 如果下标为k顶点各边权值小于此前这些顶点未被加入生成树权值 */
				lowcost[j] = G.arc[k][j];/* 将较小的权值存入lowcost相应位置 */
				adjvex[j] = k;				/* 将下标为k的顶点存入adjvex *///代表这个可能的权值是从k这个顶点出发的
			}
		}
	}
}

#pragma region 自己复写的一遍
void MiniSpanTree_Prim1(MGraph G)
{
	//int min, i, j, k;
	int lowcost[MAXVEX];
	int adjvex[MAXVEX];

	lowcost[0] = 0;
	adjvex[0] = 0;

	for (int i = 1; i < G.numVertexes; ++i)
	{
		lowcost[i] = G.arc[0][i];
		adjvex[i] = 0; //现在找的是从0这个点开始往外的最小权值
	}

	for (int i = 1; i < G.numVertexes; ++i)
	{
		int minCost = INT_MAX;
		int minPos = 0;
		for (int j = 0; j != G.numVertexes; ++j)
		{
			if (lowcost[j] != 0 && lowcost[j] < minCost)
			{
				minPos = j;
				minCost = lowcost[minPos];
			}
		}
		lowcost[minPos] = 0;
		printf("%d->%d,权值:%d\n", adjvex[minPos], minPos, minCost);
		//再把当前找到的这个点的周围的可能的点加入到候选队列

		for (int j = 0; j < G.numVertexes; ++j)
		{
			if (lowcost[j] != 0 && G.arc[minPos][j] < lowcost[j])
			{
				lowcost[j] = G.arc[minPos][j];
				adjvex[j] = minPos;
			}
		}
	}
}
#pragma endregion



int main(void)
{
	MGraph G;
	CreateMGraph(&G);
	MiniSpanTree_Prim(G);
	MiniSpanTree_Prim1(G);

	return 0;

}