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

typedef int Status;	/* Status�Ǻ���������,��ֵ�Ǻ������״̬���룬��OK�� */

typedef struct
{
	int arc[MAXVEX][MAXVEX];
	int numVertexes, numEdges;
}MGraph;

void CreateMGraph(MGraph *G)/* ����ͼ */
{
	int i, j;

	/* printf("����������Ͷ�����:"); */
	G->numEdges = 15;
	G->numVertexes = 9;

	for (i = 0; i < G->numVertexes; i++)/* ��ʼ��ͼ */
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

	for (i = 0; i < G->numVertexes; i++) //����ͼ
	{
		for (j = i; j < G->numVertexes; j++)
		{
			G->arc[j][i] = G->arc[i][j];
		}
	}

}

/* Prim�㷨������С������  */

//����prim�㷨̰��ԭ����:ÿ���ҵ����ܼ�����֪�㼯�����ܹ��γ�������СȨֵ�߼��뵽������
//��������ܵ���˵:
//����㷨�Ļ��������ȴ�V0��ʼ���ҵ�һ����С�ģ�����㼯��
//Ȼ����ҵ�������㣬�ٿ�����Χ����СȨֵ��֮ǰ��һ������СȨֵ�������뵽��С������
void MiniSpanTree_Prim(MGraph G)
{
	int min, i, j, k;
	int adjvex[MAXVEX];		/* ������ض����±� */
	int lowcost[MAXVEX];	/* ������ض����ߵ�Ȩֵ */
	//adjvex����װ����һ���ߵĳ�������
	//lowcost����װ�������л�δ������С����������ǰ������С�������Ͻ���Ȩֵ
	lowcost[0] = 0;/* ��ʼ����һ��ȨֵΪ0����v0���������� */
			/* lowcost��ֵΪ0����������Ǵ��±�Ķ����Ѿ����������� */
	adjvex[0] = 0;			/* ��ʼ����һ�������±�Ϊ0 */
	for (i = 1; i < G.numVertexes; i++)	/* ѭ�����±�Ϊ0���ȫ������ */
	{
		lowcost[i] = G.arc[0][i];	/* ��v0������֮�бߵ�Ȩֵ�������� */
		adjvex[i] = 0;					/* ��ʼ����Ϊv0���±� */
	}
	for (i = 1; i < G.numVertexes; i++)
	{
		min = INFINITY;	/* ��ʼ����СȨֵΪ�ޣ� */
						/* ͨ������Ϊ�����ܵĴ�������32767��65535�� */
		j = 1; k = 0;
		while (j < G.numVertexes)	/* ѭ��ȫ������ */
		{
			if (lowcost[j] != 0 && lowcost[j] < min)/* ���Ȩֵ��Ϊ0��ȨֵС��min */
			{
				min = lowcost[j];	/* ���õ�ǰȨֵ��Ϊ��Сֵ */
				k = j;			/* ����ǰ��Сֵ���±����k */
			}
			j++;
		}
		printf("(%d, %d),Ȩֵ:%d\n", adjvex[k], k,min);/* ��ӡ��ǰ�������Ȩֵ��С�ı� */
		lowcost[k] = 0;/* ����ǰ�����Ȩֵ����Ϊ0,��ʾ�˶����Ѿ�������� */
		for (j = 1; j < G.numVertexes; j++)	/* ѭ�����ж��� */
		{
			if (lowcost[j] != 0 && G.arc[k][j] < lowcost[j])
			{/* ����±�Ϊk�������ȨֵС�ڴ�ǰ��Щ����δ������������Ȩֵ */
				lowcost[j] = G.arc[k][j];/* ����С��Ȩֵ����lowcost��Ӧλ�� */
				adjvex[j] = k;				/* ���±�Ϊk�Ķ������adjvex *///����������ܵ�Ȩֵ�Ǵ�k������������
			}
		}
	}
}

#pragma region �Լ���д��һ��
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
		adjvex[i] = 0; //�����ҵ��Ǵ�0����㿪ʼ�������СȨֵ
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
		printf("%d->%d,Ȩֵ:%d\n", adjvex[minPos], minPos, minCost);
		//�ٰѵ�ǰ�ҵ�����������Χ�Ŀ��ܵĵ���뵽��ѡ����

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