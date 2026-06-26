/*
 * 图操作（第六次作业：图）
 *
 * 【功能清单】
 *   Part A 邻接矩阵图 AMGraph
 *     amInit · amAddEdge · amAddDirEdge · amRemoveEdge · amRemoveDirEdge
 *     amDFS · amBFS
 *     amPrint
 *   Part B 邻接表图 ALGraph
 *     alInit · alAddEdge · alAddDirEdge · alRemoveEdge · alRemoveDirEdge
 *     alDFS · alBFS
 *     alDestroy
 *   Part C 最小生成树 Prim
 *     primMST · sortArray
 *   Part D 最短路径 Dijkstra
 *     dijkstraAllPaths
 *   Part E 最小生成树 Kruskal
 *     ufInit · ufFind · ufUnion
 *     kruskalMST · sortKruskalEdges
 *
 * 用法：把需要的结构体和函数复制到你的 .c 文件里。
 * 约定：返回 1 表示"是/成功"，返回 0 表示"否/失败"（与之前的库相同）。
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ==================== 容量宏（可按题目修改） ==================== */
#define MAX_V 100 /* 最大顶点数 */
#define INF 0x7fffffff

/* ==================== Part A：邻接矩阵图 ==================== */

typedef struct AMGraph
{
    int n;                 /* 顶点数 */
    int e;                 /* 边数（有向图只计入有向边数） */
    int adj[MAX_V][MAX_V]; /* 邻接矩阵，0=无边，非0=有边（或权值） */
} AMGraph;

/* ─── 初始化 ────────────────────────────────────────── */

/*
 * 功能：初始化邻接矩阵图，n 个顶点，无边
 * 返回：无
 *
 * 使用示例：
 *   AMGraph g;
 *   amInit(&g, 5);
 */
void amInit(AMGraph *g, int n)
{
    int i, j;
    g->n = n; /* 设置顶点数 */
    g->e = 0; /* 初始无边 */
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            g->adj[i][j] = 0; /* 邻接矩阵全部清零 */
}

/* ─── 无向边 ────────────────────────────────────────── */

/*
 * 功能：添加无向边 (u, v)，权值为 w（默认为 1）
 *       同时设置 g->adj[u][v] 和 g->adj[v][u]
 * 返回：1 成功，0 顶点越界
 *
 * 使用示例：
 *   amAddEdge(&g, 0, 1, 1);
 *   amAddEdge(&g, 1, 2, 1);
 */
int amAddEdge(AMGraph *g, int u, int v, int w)
{
    if (u < 0 || u >= g->n || v < 0 || v >= g->n)
        return 0; /* 顶点下标越界，操作失败 */
    if (g->adj[u][v] == 0)
        g->e++;       /* 原先无边，边数加 1 */
    g->adj[u][v] = w; /* 设置 u→v */
    g->adj[v][u] = w; /* 对称设置 v→u */
    return 1;
}

/*
 * 功能：删除无向边 (u, v)
 *       同时清零 g->adj[u][v] 和 g->adj[v][u]
 * 返回：1 成功，0 顶点越界或无此边
 *
 * 使用示例：
 *   amRemoveEdge(&g, 0, 1);
 */
int amRemoveEdge(AMGraph *g, int u, int v)
{
    if (u < 0 || u >= g->n || v < 0 || v >= g->n)
        return 0; /* 顶点下标越界 */
    if (g->adj[u][v] == 0)
        return 0;     /* 边不存在，删除失败 */
    g->adj[u][v] = 0; /* 清除 u→v */
    g->adj[v][u] = 0; /* 对称清除 v→u */
    g->e--;           /* 边数减 1 */
    return 1;
}

/* ─── 有向边 ────────────────────────────────────────── */

/*
 * 功能：添加有向边 u→v，权值为 w
 *       只设置 g->adj[u][v]，不设置 g->adj[v][u]
 * 返回：1 成功，0 顶点越界
 *
 * 使用示例：
 *   amAddDirEdge(&g, 0, 2, 5);  // 添加 0→2 的边，权值 5
 */
int amAddDirEdge(AMGraph *g, int u, int v, int w)
{
    if (u < 0 || u >= g->n || v < 0 || v >= g->n)
        return 0; /* 顶点下标越界，操作失败 */
    if (g->adj[u][v] == 0)
        g->e++;       /* 原先无此有向边，边数加 1 */
    g->adj[u][v] = w; /* 仅设置 u→v 方向 */
    return 1;
}

/*
 * 功能：删除有向边 u→v
 *       只清零 g->adj[u][v]，不触及 g->adj[v][u]
 * 返回：1 成功，0 顶点越界或无此边
 *
 * 使用示例：
 *   amRemoveDirEdge(&g, 0, 2);
 */
int amRemoveDirEdge(AMGraph *g, int u, int v)
{
    if (u < 0 || u >= g->n || v < 0 || v >= g->n)
        return 0; /* 顶点下标越界 */
    if (g->adj[u][v] == 0)
        return 0;     /* 边不存在，删除失败 */
    g->adj[u][v] = 0; /* 仅清除 u→v 方向 */
    g->e--;           /* 边数减 1 */
    return 1;
}

/* ─── 遍历 ──────────────────────────────────────────── */

/*
 * 功能：深度优先遍历，从顶点 sv 开始
 *       visited 已标记为 1 的顶点会被跳过（也适用于有向图）
 *       first 为 1 表示第一个输出（不含前导空格），适合多行输出衔接
 * 返回：无
 *
 * 使用示例：
 *   int visited[MAX_V] = {0};
 *   visited[3] = 1;  // 提前标记，视为"已访问"（等效于删除顶点 3）
 *   amDFS(&g, 0, visited, 1);
 */
void amDFS(AMGraph *g, int sv, int visited[], int first)
{
    int i;
    if (first)
        printf("%d", sv); /* 第一个顶点不加前导空格 */
    else
        printf(" %d", sv); /* 后续顶点前加空格分隔 */
    visited[sv] = 1;       /* 标记当前顶点已访问 */
    for (i = 0; i < g->n; i++)
    {
        if (g->adj[sv][i] != 0 && !visited[i])
            amDFS(g, i, visited, 0); /* 递归访问未访问的邻接顶点 */
    }
}

/*
 * 功能：广度优先遍历，从顶点 sv 开始
 *       visited 已标记为 1 的顶点会被跳过（也适用于有向图）
 * 返回：无
 *
 * 使用示例：
 *   int visited[MAX_V] = {0};
 *   amBFS(&g, 0, visited);
 */
void amBFS(AMGraph *g, int sv, int visited[])
{
    int queue[MAX_V], front = 0, rear = 0; /* 用数组模拟队列 */
    int i, v;
    printf("%d", sv);   /* 输出起点 */
    visited[sv] = 1;    /* 标记起点已访问 */
    queue[rear++] = sv; /* 起点入队 */
    while (front < rear)
    {                       /* 队列非空时循环 */
        v = queue[front++]; /* 出队一个顶点 */
        for (i = 0; i < g->n; i++)
        { /* 检查所有邻接顶点 */
            if (g->adj[v][i] != 0 && !visited[i])
            {
                printf(" %d", i);  /* 输出该顶点 */
                visited[i] = 1;    /* 标记已访问 */
                queue[rear++] = i; /* 入队 */
            }
        }
    }
}

/*
 * 功能：打印邻接矩阵（调试用）
 * 返回：无
 */
void amPrint(AMGraph *g)
{
    int i, j;
    for (i = 0; i < g->n; i++)
    {
        for (j = 0; j < g->n; j++)
            printf("%d ", g->adj[i][j]); /* 逐格输出矩阵值 */
        printf("\n");                    /* 换行 */
    }
}

/* ==================== Part B：邻接表图 ==================== */

typedef struct EdgeNode
{
    int adjvex;            /* 邻接顶点编号 */
    int weight;            /* 边权值 */
    int eno;               /* 边编号（部分题目需要，不需要时可填 0） */
    struct EdgeNode *next; /* 指向下一条边 */
} EdgeNode;

typedef struct VertexNode
{
    EdgeNode *first; /* 指向第一条出边（链表头指针） */
} VertexNode;

typedef struct ALGraph
{
    int n;                 /* 顶点数 */
    int e;                 /* 边数 */
    VertexNode adj[MAX_V]; /* 邻接表，adj[i] 为顶点 i 的边链表 */
} ALGraph;

/* ─── 初始化 ────────────────────────────────────────── */

/*
 * 功能：初始化邻接表图，n 个顶点
 * 返回：无
 *
 * 使用示例：
 *   ALGraph g;
 *   alInit(&g, 6);
 */
void alInit(ALGraph *g, int n)
{
    int i;
    g->n = n; /* 设置顶点数 */
    g->e = 0; /* 初始无边 */
    for (i = 0; i < n; i++)
        g->adj[i].first = NULL; /* 所有顶点的边链表置空 */
}

/* ─── 无向边 ────────────────────────────────────────── */

/*
 * 功能：在邻接表中添加无向边 (u, v)，权值 w，边编号 eno
 *       分别在 u 和 v 的链表中各插入一个边结点（尾插，保持输入顺序）
 * 返回：1 成功，0 顶点越界或内存不足
 *
 * 使用示例：
 *   alAddEdge(&g, 0, 1, 1, 5);  // 权值 1，边编号 5
 */
int alAddEdge(ALGraph *g, int u, int v, int w, int eno)
{
    EdgeNode *e, *p;

    if (u < 0 || u >= g->n || v < 0 || v >= g->n)
        return 0; /* 顶点下标越界 */

    /* ── 插入 u→v ── */
    e = (EdgeNode *)malloc(sizeof(EdgeNode));
    if (e == NULL)
        return 0;   /* 内存分配失败 */
    e->adjvex = v;  /* 邻接顶点为 v */
    e->weight = w;  /* 设置权值 */
    e->eno = eno;   /* 设置边编号 */
    e->next = NULL; /* 新结点作为尾结点 */
    if (g->adj[u].first == NULL)
    {
        g->adj[u].first = e; /* 当前链表为空，新结点成为头结点 */
    }
    else
    {
        for (p = g->adj[u].first; p->next != NULL; p = p->next)
            ;        /* 找到链表末尾 */
        p->next = e; /* 尾插 */
    }

    /* ── 插入 v→u（对称） ── */
    e = (EdgeNode *)malloc(sizeof(EdgeNode));
    if (e == NULL)
        return 0;  /* 内存分配失败 */
    e->adjvex = u; /* 邻接顶点为 u */
    e->weight = w; /* 权值相同 */
    e->eno = eno;  /* 边编号相同 */
    e->next = NULL;
    if (g->adj[v].first == NULL)
    {
        g->adj[v].first = e;
    }
    else
    {
        for (p = g->adj[v].first; p->next != NULL; p = p->next)
            ;
        p->next = e;
    }

    g->e++; /* 边数加 1 */
    return 1;
}

/*
 * 功能：删除无向边 (u, v)
 *       分别在 u 和 v 的链表中查找并删除对应的边结点
 * 返回：1 成功，0 顶点越界或不存在此边
 *
 * 使用示例：
 *   alRemoveEdge(&g, 0, 1);
 */
int alRemoveEdge(ALGraph *g, int u, int v)
{
    EdgeNode *p, *prev;

    if (u < 0 || u >= g->n || v < 0 || v >= g->n)
        return 0; /* 顶点下标越界 */

    /* ── 从 u 的链表中删除 v ── */
    prev = NULL;
    for (p = g->adj[u].first; p != NULL; prev = p, p = p->next)
    {
        if (p->adjvex == v)
        { /* 找到指向 v 的边 */
            if (prev == NULL)
                g->adj[u].first = p->next; /* 删除的是头结点 */
            else
                prev->next = p->next; /* 删除的是中间/尾结点 */
            free(p);                  /* 释放内存 */
            break;
        }
    }

    /* ── 从 v 的链表中删除 u（对称） ── */
    prev = NULL;
    for (p = g->adj[v].first; p != NULL; prev = p, p = p->next)
    {
        if (p->adjvex == u)
        { /* 找到指向 u 的边 */
            if (prev == NULL)
                g->adj[v].first = p->next;
            else
                prev->next = p->next;
            free(p);
            break;
        }
    }

    g->e--; /* 边数减 1 */
    return 1;
}

/* ─── 有向边 ────────────────────────────────────────── */

/*
 * 功能：添加有向边 u→v，权值 w，边编号 eno
 *       只在 u 的链表中插入边结点，不插入 v 的链表
 * 返回：1 成功，0 顶点越界或内存不足
 *
 * 使用示例：
 *   alAddDirEdge(&g, 2, 5, 3, 0);  // 添加 2→5 的有向边，权值 3
 */
int alAddDirEdge(ALGraph *g, int u, int v, int w, int eno)
{
    EdgeNode *e, *p;

    if (u < 0 || u >= g->n || v < 0 || v >= g->n)
        return 0; /* 顶点下标越界 */

    e = (EdgeNode *)malloc(sizeof(EdgeNode));
    if (e == NULL)
        return 0;  /* 内存分配失败 */
    e->adjvex = v; /* 邻接顶点为 v */
    e->weight = w; /* 设置权值 */
    e->eno = eno;  /* 设置边编号 */
    e->next = NULL;
    if (g->adj[u].first == NULL)
    {
        g->adj[u].first = e; /* 头插（链表为空） */
    }
    else
    {
        for (p = g->adj[u].first; p->next != NULL; p = p->next)
            ;        /* 找到链表末尾 */
        p->next = e; /* 尾插 */
    }

    g->e++; /* 有向边数加 1 */
    return 1;
}

/*
 * 功能：删除有向边 u→v
 *       只在 u 的链表中查找并删除指向 v 的第一个边结点
 * 返回：1 成功，0 越界或不存在此边
 *
 * 使用示例：
 *   alRemoveDirEdge(&g, 2, 5);
 */
int alRemoveDirEdge(ALGraph *g, int u, int v)
{
    EdgeNode *p, *prev;

    if (u < 0 || u >= g->n || v < 0 || v >= g->n)
        return 0; /* 顶点下标越界 */

    prev = NULL;
    for (p = g->adj[u].first; p != NULL; prev = p, p = p->next)
    {
        if (p->adjvex == v)
        { /* 找到指向 v 的边结点 */
            if (prev == NULL)
                g->adj[u].first = p->next; /* 删除头结点 */
            else
                prev->next = p->next; /* 删除非头结点 */
            free(p);                  /* 释放内存 */
            g->e--;                   /* 边数减 1 */
            return 1;
        }
    }
    return 0; /* 未找到该边 */
}

/* ─── 遍历 ──────────────────────────────────────────── */

/*
 * 功能：邻接表深度优先遍历（递归），从顶点 v 开始
 *       visited 数组需由调用方维护并初始化为 0
 * 返回：无
 */
void alDFS(ALGraph *g, int v, int visited[])
{
    EdgeNode *p;
    printf("%d ", v); /* 输出当前顶点 */
    visited[v] = 1;   /* 标记已访问 */
    for (p = g->adj[v].first; p != NULL; p = p->next)
    {
        if (!visited[p->adjvex])          /* 邻接顶点未访问 */
            alDFS(g, p->adjvex, visited); /* 递归访问 */
    }
}

/*
 * 功能：邻接表广度优先遍历，从顶点 sv 开始
 *       visited 数组需由调用方维护并初始化为 0
 * 返回：无
 */
void alBFS(ALGraph *g, int sv, int visited[])
{
    int queue[MAX_V], front = 0, rear = 0; /* 辅助队列 */
    EdgeNode *p;
    printf("%d ", sv);  /* 输出起点 */
    visited[sv] = 1;    /* 标记已访问 */
    queue[rear++] = sv; /* 起点入队 */
    while (front < rear)
    {                           /* 队列非空 */
        int v = queue[front++]; /* 出队 */
        for (p = g->adj[v].first; p != NULL; p = p->next)
        {
            if (!visited[p->adjvex])
            {                              /* 未访问的邻接顶点 */
                printf("%d ", p->adjvex);  /* 输出 */
                visited[p->adjvex] = 1;    /* 标记 */
                queue[rear++] = p->adjvex; /* 入队 */
            }
        }
    }
}

/*
 * 功能：释放邻接表所有边结点占用的内存
 * 返回：无
 *
 * 使用示例：
 *   alDestroy(&g);
 */
void alDestroy(ALGraph *g)
{
    int i;
    EdgeNode *p, *q;
    for (i = 0; i < g->n; i++)
    { /* 遍历每个顶点 */
        p = g->adj[i].first;
        while (p != NULL)
        {                /* 遍历该顶点的边链表 */
            q = p;       /* 暂存当前结点 */
            p = p->next; /* 移动到下一个 */
            free(q);     /* 释放当前结点 */
        }
        g->adj[i].first = NULL; /* 链表指针置空 */
    }
}

/* ==================== Part C：最小生成树 Prim ==================== */

/*
 * 功能：Prim 算法求最小生成树
 *       输入带权邻接矩阵 adj[n][n]（无边的位置填 INF），n 为顶点数
 *       输出最小生成树的总权值，选中的边编号存入 result[]，数量写入 *cnt
 *       edgeId[i][j] 为边 (i,j) 的编号（不需要时填 -1 或 0）
 * 返回：最小生成树总权值，选中边数通过 *cnt 传出
 *
 * 使用示例：
 *   int adjMat[MAX_V][MAX_V], edgeId[MAX_V][MAX_V];
 *   // ... 初始化（无边处填 INF，edgeId 无编号处填 -1）...
 *   int resultEdges[MAX_V], cnt;
 *   int total = primMST(adjMat, edgeId, n, resultEdges, &cnt);
 */
int primMST(int adj[MAX_V][MAX_V], int edgeId[MAX_V][MAX_V],
            int n, int result[], int *cnt)
{
    int visited[MAX_V] = {0}; /* 访问标记数组 */
    int minCost[MAX_V];       /* minCost[i]：顶点 i 到生成树的最小边权 */
    int parent[MAX_V];        /* parent[i]：i 在生成树中的父顶点 */
    int i, j, sum = 0;        /* sum 累计生成树总权值 */

    *cnt = 0; /* 选中的边数初值为 0 */
    for (i = 0; i < n; i++)
    {
        minCost[i] = INF; /* 初始化为无穷大 */
        parent[i] = -1;   /* 父顶点初始化为 -1 */
    }

    minCost[0] = 0; /* 选择顶点 0 作为起点，代价为 0 */
    visited[0] = 1; /* 标记顶点 0 已加入生成树 */

    for (i = 1; i < n; i++)
    { /* 用顶点 0 更新邻居的 minCost */
        if (adj[0][i] != INF && adj[0][i] < minCost[i])
        {
            minCost[i] = adj[0][i]; /* 更新最小代价 */
            parent[i] = 0;          /* 记录父顶点 */
        }
    }

    for (i = 0; i < n - 1; i++)
    {                            /* 需要选择 n-1 条边 */
        int min = INF, idx = -1; /* min：当前最小代价；idx：对应顶点 */
        for (j = 0; j < n; j++)
        { /* 在所有未加入的顶点中找最小者 */
            if (!visited[j] && minCost[j] < min)
            {
                min = minCost[j];
                idx = j;
            }
        }
        if (idx == -1)
            break;        /* 找不到可连的顶点（图不连通），退出 */
        visited[idx] = 1; /* 将 idx 加入生成树 */
        sum += min;       /* 累加边权值 */

        if (edgeId[parent[idx]][idx] != -1)
            result[(*cnt)++] = edgeId[parent[idx]][idx]; /* 记录选中边的编号 */

        for (j = 0; j < n; j++)
        { /* 用新加入的顶点 idx 更新邻居 */
            if (!visited[j] && adj[idx][j] != INF && adj[idx][j] < minCost[j])
            {
                minCost[j] = adj[idx][j]; /* 找到更小的代价 */
                parent[j] = idx;          /* 更新父顶点 */
            }
        }
    }
    return sum; /* 返回最小生成树总权值 */
}

/*
 * 功能：对整数数组升序排序（插入排序，用于 Prim 结果输出）
 * 返回：无
 */
void sortArray(int arr[], int n)
{
    int i, j, tmp;
    for (i = 1; i < n; i++)
    {                 /* 从第二个元素开始 */
        tmp = arr[i]; /* 暂存当前元素 */
        for (j = i - 1; j >= 0 && arr[j] > tmp; j--)
            arr[j + 1] = arr[j]; /* 比 tmp 大的元素后移 */
        arr[j + 1] = tmp;        /* 插入到正确位置 */
    }
}

/* ==================== Part D：最短路径 Dijkstra ==================== */

/*
 * 功能：Dijkstra 算法（含等长多前驱），求单源最短路径
 *       adj[n][n] 为邻接矩阵（无边处填 INF），n 为顶点数
 *       从起点 sv 到所有顶点的最短距离存入 dist[]
 *       前驱列表存入 spath[][]，spath[i][0..ls[i]-1] 为顶点 i 的所有前驱
 *       调用后可通过前驱列表回溯枚举所有最短路径
 * 返回：无
 *
 * 使用示例：
 *   int dist[MAX_V], spath[MAX_V][MAX_V], ls[MAX_V];
 *   dijkstraAllPaths(adjMat, n, 0, dist, spath, ls);
 *   // dist[i] 存储最短距离，通过 spath 和 ls 回溯所有最短路径
 */
void dijkstraAllPaths(int adj[MAX_V][MAX_V], int n, int sv,
                      int dist[], int spath[][MAX_V], int ls[])
{
    int visited[MAX_V] = {0}; /* 访问标记：1=已确定最短路径 */
    int i, j, v, min;

    /* ── 初始化 ── */
    for (i = 0; i < n; i++)
    {
        dist[i] = adj[sv][i]; /* 初始距离 = 起点到 i 的直接边权 */
        spath[i][0] = sv;     /* 初始前驱为起点 */
        ls[i] = 1;            /* 初始前驱个数为 1 */
    }
    dist[sv] = 0;    /* 起点到自身的距离为 0 */
    visited[sv] = 1; /* 起点已确定 */

    /* ── 主循环：每次确定一个距起点最近的未访问顶点 ── */
    for (i = 0; i < n - 1; i++)
    {
        min = INF;
        v = -1;
        for (j = 0; j < n; j++)
        { /* 在未访问顶点中找距离最小者 */
            if (!visited[j] && dist[j] < min)
            {
                min = dist[j];
                v = j;
            }
        }
        if (v == -1)
            break;      /* 剩余顶点不可达，退出 */
        visited[v] = 1; /* 确定顶点 v 的最短路径 */

        for (j = 0; j < n; j++)
        { /* 用 v 松弛其所有邻居 */
            if (!visited[j] && adj[v][j] != INF)
            {
                if (min + adj[v][j] < dist[j])
                {
                    /* 找到更短路径，更新距离并重置前驱列表 */
                    dist[j] = min + adj[v][j];
                    spath[j][0] = v;
                    ls[j] = 1; /* 清空前驱列表，只有 v */
                }
                else if (min + adj[v][j] == dist[j])
                {
                    /* 找到等长路径，追加前驱 */
                    spath[j][ls[j]] = v;
                    ls[j]++; /* 前驱个数加 1 */
                }
            }
        }
    }
}

/* ==================== Part E：最小生成树 Kruskal ==================== */

/*
 * Kruskal 算法核心思想：
 *   1. 将所有边按权值从小到大排序
 *   2. 从小到大依次选边，若边的两端不在同一连通分量（并查集判断），
 *      则选中这条边并合并两端所在的连通分量
 *   3. 重复直到选出 n-1 条边（n 为顶点数）
 *
 * 时间复杂度 O(e log e)，e 为边数，瓶颈在边排序。
 */

/* ─── Kruskal 边结构 ───────────────────────────────── */

/*
 * KruskalEdge：封装一条边，供 Kruskal 排序和选边使用
 *   u, v   — 边的两个端点
 *   w      — 边权值
 *   id     — 边编号（不需要时填 0）
 */
typedef struct KruskalEdge
{
    int u, v; /* 边两端顶点 */
    int w;    /* 边权值 */
    int id;   /* 边编号 */
} KruskalEdge;

/* ─── 并查集（Union-Find / Disjoint Set） ──────────── */

int ufParent[MAX_V]; /* parent[i]：i 的父结点，根结点的 parent 为 -1 */
int ufSize[MAX_V];   /* size[i]：以 i 为根的集合大小（仅根有效） */

/*
 * 功能：初始化并查集，n 个顶点各自独立
 * 返回：无
 *
 * 使用示例：
 *   ufInit(6);
 */
void ufInit(int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        ufParent[i] = -1; /* -1 表示自身为根 */
        ufSize[i] = 1;    /* 初始每个集合大小为 1 */
    }
}

/*
 * 功能：查找顶点 x 所在集合的根（带路径压缩）
 *       路径压缩：查找过程中将途径结点直接挂在根下，加速后续查询
 * 返回：根顶点编号
 *
 * 使用示例：
 *   int root = ufFind(5);
 */
int ufFind(int x)
{
    if (ufParent[x] == -1)
        return x;                      /* 当前结点就是根 */
    ufParent[x] = ufFind(ufParent[x]); /* 递归查找根并做路径压缩 */
    return ufParent[x];
}

/*
 * 功能：合并顶点 a 和 b 所在的两个集合（按大小归并）
 *       较小集合的根挂到较大集合的根下，保持树的高度较低
 * 返回：无
 *
 * 使用示例：
 *   ufUnion(1, 3);
 */
void ufUnion(int a, int b)
{
    int ra = ufFind(a); /* a 所在集合的根 */
    int rb = ufFind(b); /* b 所在集合的根 */
    if (ra == rb)
        return; /* 已在同一集合中，无需合并 */

    /* ── 按大小归并：小集合挂到大集合下 ── */
    if (ufSize[ra] < ufSize[rb])
    {
        ufParent[ra] = rb;        /* ra 的父结点设为 rb */
        ufSize[rb] += ufSize[ra]; /* 更新 rb 的集合大小 */
    }
    else
    {
        ufParent[rb] = ra;        /* rb 的父结点设为 ra */
        ufSize[ra] += ufSize[rb]; /* 更新 ra 的集合大小 */
    }
}

/* ─── Kruskal 排序 ─────────────────────────────────── */

/*
 * 功能：对 Kruskal 边数组按权值升序排序（选择排序，稳定）
 *       权值相等时按边编号升序（题目常见稳定排序要求）
 *       输入边数较小时（≤ 200）选择排序足够
 * 返回：无
 */
void sortKruskalEdges(KruskalEdge edges[], int e)
{
    int i, j, min;
    KruskalEdge tmp;
    for (i = 0; i < e - 1; i++)
    {
        min = i;
        for (j = i + 1; j < e; j++)
        {
            if (edges[j].w < edges[min].w || (edges[j].w == edges[min].w && edges[j].id < edges[min].id))
            {
                min = j; /* 找到更小的边 */
            }
        }
        if (min != i)
        { /* 交换到第 i 位 */
            tmp = edges[i];
            edges[i] = edges[min];
            edges[min] = tmp;
        }
    }
}

/*
 * 功能：Kruskal 算法求最小生成树
 *       输入边数组 edges[] 和边数 e（有向图请只传入一个方向的边），
 *       顶点数 n
 *       输出最小生成树的总权值（return），选中的边编号存入 result[]，
 *       选中边数写入 *cnt
 * 返回：最小生成树总权值，边数通过 *cnt 传出
 *
 * 使用示例：
 *   KruskalEdge edges[MAX_E];
 *   // ... 逐条填入 edges，设边数为 e ...
 *   int result[MAX_V], cnt;
 *   int total = kruskalMST(edges, e, n, result, &cnt);
 *   // 对 result 排序后输出
 */
int kruskalMST(KruskalEdge edges[], int e, int n,
               int result[], int *cnt)
{
    int i, sum = 0;

    *cnt = 0;  /* 选中边数初值为 0 */
    ufInit(n); /* 并查集初始化：n 个顶点各自独立 */

    sortKruskalEdges(edges, e); /* 边按权值从小到大排序 */

    for (i = 0; i < e && *cnt < n - 1; i++)
    {
        /* 若边两端不在同一集合（不会形成环），则选中 */
        if (ufFind(edges[i].u) != ufFind(edges[i].v))
        {
            ufUnion(edges[i].u, edges[i].v); /* 合并两个连通分量 */
            sum += edges[i].w;               /* 累加边权值 */
            if (edges[i].id != 0)
                result[(*cnt)++] = edges[i].id; /* 记录选中边的编号 */
        }
    }
    return sum; /* 返回最小生成树总权值 */
}
