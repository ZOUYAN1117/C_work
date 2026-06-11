#include <stdio.h>
#include <stdlib.h>

#define MaxV 100  // 最大顶点数
#define INF 99999 // 无穷大
int Visited[MaxV] = {0};
// ========== 邻接矩阵 ==========
typedef struct
{
    int weight; // 权值
} Edge;

void visit(int v)
{
    printf("%d ", v);
}

void DFS_Matrix(Edge G[][MaxV], int n, int v)
{
    Visited[v] = 1;
    visit(v);
    for (int j = 0; j < n; j++)                 // 扫描整行
        if (G[v][j].weight != 0 && !Visited[j]) // 有边且未访问
            DFS_Matrix(G, n, j);
}

void BFS_Matrix(Edge G[][MaxV], int n, int v)
{
    int Q[MaxV], front = 0, rear = 0;
    Visited[v] = 1;
    Q[rear++] = v;
    while (front < rear)
    {
        v = Q[front++];
        visit(v);
        for (int j = 0; j < n; j++) // 扫描整行
            if (G[v][j].weight != 0 && !Visited[j])
            {
                Visited[j] = 1;
                Q[rear++] = j;
            }
    }
}

int main()
{
    Edge G[MaxV][MaxV];
    int n, e; // 顶点数、边数
    scanf("%d %d", &n, &e);
    for (int i = 0; i < e; i++)
    {
        int u, v;
        scanf("%d %d", &u, &v);
        G[u][v].weight = 1; // 无权图，权值设为1
        G[v][u].weight = 1; // 无向图
    }
    DFS_Matrix(G, n, 0); // 从顶点0开始DFS
    printf("\n");
    for (int i = 0; i < n; i++)
        Visited[i] = 0;  // 重置访问标记
    BFS_Matrix(G, n, 0); // 从顶点0开始BFS
    printf("\n");
    for (int i = 0; i < n; i++)
        Visited[i] = 0; // 重置访问标记
    int k;
    scanf("%d", &k); // 防止程序立即退出
    for (int i = 0; i < n; i++)
    {
        if (G[i][k].weight)
        {
            G[i][k].weight = 0;
            G[k][i].weight = 0;
        }
    }
    DFS_Matrix(G, n, 0); // 从顶点0开始DFS
    printf("\n");
    for (int i = 0; i < n; i++)
        Visited[i] = 0;  // 重置访问标记
    BFS_Matrix(G, n, 0); // 从顶点0开始BFS
    printf("\n");
    return 0;
}
