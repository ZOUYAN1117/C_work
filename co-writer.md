# 📚 图（Graph）· 期末总结

---

# 第一部分：知识点总汇

---

## 一、图的基本概念（6.1）

### 1. 图的定义
> G = (V, E)，V 是顶点非空有穷集合，E 是边/弧的集合。

### 2. 无向图 vs 有向图

|        | 无向图              | 有向图                  |
| :----: | ------------------- | ----------------------- |
| 边表示 | **(vᵢ, vⱼ)** 圆括号 | **`<vᵢ, vⱼ>`** 尖括号   |
|  方向  | (vᵢ, vⱼ) = (vⱼ, vᵢ) | `<vᵢ, vⱼ>` ≠ `<vⱼ, vᵢ>` |
|  边称  | 边 (Edge)           | 弧 (Arc)                |

### 3. 度的概念

|      概念      |  记法  | 含义                 |
| :------------: | :----: | -------------------- |
|  度（无向图）  | TD(vᵢ) | 依附于 vᵢ 的边的数目 |
| 出度（有向图） | OD(vᵢ) | 以 vᵢ 为起点的弧数目 |
| 入度（有向图） | ID(vᵢ) | 以 vᵢ 为终点的弧数目 |
| 总度（有向图） | TD(vᵢ) | TD = OD + ID         |

### 4. 完全图

|       图类型       |   最大边数   |
| :----------------: | :----------: |
| n 个顶点无向完全图 | **n(n−1)/2** |
| n 个顶点有向完全图 |  **n(n−1)**  |

### 5. 稀疏图 vs 稠密图
- 边数接近 n(n−1)/2 → 稠密图
- 边数远小于 n(n−1)/2 → 稀疏图（通常 e < n·log n）

### 6. 连通性

| 术语                   | 含义                                           |
| ---------------------- | ---------------------------------------------- |
| **连通图（无向）**     | 任意两顶点间有路径                             |
| **连通分量（无向）**   | 极大连通子图                                   |
| **强连通图（有向）**   | 任意两顶点互相可达                             |
| **强连通分量（有向）** | 极大强连通子图                                 |
| **生成树**             | 包含全部 n 个顶点、恰好 n−1 条边的无环连通子图 |
| **生成森林**           | 非连通图每个连通分量一棵生成树                 |

---

## 二、图的存储方法（6.2）

|   存储方式   | 核心结构             |  空间  |     适用     |
| :----------: | -------------------- | :----: | :----------: |
| **邻接矩阵** | n×n 二维数组 G[i][j] | O(n²)  |    稠密图    |
|  **邻接表**  | 顶点数组 + 边链表    | O(n+e) |    稀疏图    |
| **逆邻接表** | 存指向自己的顶点     | O(n+e) | 需频繁查入度 |
| **边集数组** | 一维数组存所有边     |  O(e)  |   Kruskal    |

### 邻接矩阵
- 判邻接：**O(1)**
- 找所有邻接点：**O(n)**
- 无向图对称，有向图不对称
- 对于有向图，第 i 行的非无穷大元素个数等于顶点 i 的**出度**，第 i 列的非无穷大元素个数等于顶点 i 的**入度**

### 邻接表
- 判邻接：**O(n)** 最坏
- 找所有邻接点：**O(度)**
- 有向图：只存出边；需入度 → 建逆邻接表（或同时维护两者）

---

## 三、图的遍历（6.3）

### DFS（深度优先搜索）
- 核心数据结构：**递归（系统栈）**
- 走法：一条路走到底，走不通再回溯
- 标记时机：访问时标记 `Visited[v]=1`
- 时间复杂度：**O(n+e)**
- 类比树：前/中/后序遍历
- 适用：目标明确，找路径

### BFS（广度优先搜索）
- 核心数据结构：**队列**
- 走法：层层扩散，涟漪式
- 标记时机：**入队时标记**（防止重复入队！）
- 时间复杂度：**O(n+e)**
- 类比树：层次遍历
- 适用：找最短路径、最优解

### 非连通图处理
- 两个算法都通过外层 `travel` 函数的 for 循环保证每个连通分量都被遍历

---

## 四、最小生成树 MST（6.4）

### 生成树定义
> 包含 n 个顶点、n−1 条边、无环的连通子图

### MST 定义
> 所有生成树中边权总和**最小**的那棵

### MST 性质（判断题高频）

| 命题                                  | 正误  | 理由                     |
| ------------------------------------- | :---: | ------------------------ |
| 最小边一定在 MST 中（无权值相同）     |   ✅   | 不选它换成更大边总权增大 |
| 最大边一定不在 MST 中（无权值相同）   |   ❌   | 若是割边，必须选         |
| 与同一顶点相连的最小边一定在 MST 中   |   ❌   | 局部未必全局最优         |
| Kruskal 判环只需看两端点是否都在 U 中 |   ❌   | 必须用**并查集**判同根   |

### Prim 算法
- 策略：认准集合 U，每次挑 U↔V−U 的最小边往外扩
- 复杂度：**O(n²)**
- 适合：**稠密图**
- 数据结构：邻接矩阵

### Kruskal 算法
- 策略：边排序 → 从小到大依次拿 → 不成环就收
- 复杂度：**O(e·log e)**
- 适合：**稀疏图**
- 数据结构：边集数组 + **并查集**

### 并查集（Union-Find）
|     操作     | 作用                    |    复杂度    |
| :----------: | ----------------------- | :----------: |
|   Find(x)    | 找 x 所在集合的根       | O(α(n))≈O(1) |
|  Union(a,b)  | 合并两个集合            | O(α(n))≈O(1) |
| **路径压缩** | Find 时把沿途节点直挂根 |      —       |
| **按秩合并** | Union 时矮的挂到高的下  |      —       |

---

## 五、最短路径（6.5）

### Dijkstra（单源）
- 策略：贪心选 dist 最小顶点 → 松弛邻居
- 复杂度：O(n²) 或堆优化 O((n+e)·log n)
- **不能处理负权边**（为什么？已确定顶点可能被负权边改小）
- 数据结构：邻接矩阵 + dist 数组 + path 数组

### Floyd（所有顶点对）
- 策略：动态规划，逐次插入中转点 k
- 核心转移：`D[i][j] = min(D[i][j], D[i][k] + D[k][j])`
- 复杂度：**O(n³)**
- **可以处理负权边**，但不能有负权回路
- 负权回路检测：Floyd 后若 `D[i][i] < 0` 则存在

### Dijkstra vs Floyd

|        | Dijkstra |   Floyd    |
| :----: | :------: | :--------: |
|  范围  |   单源   | 所有顶点对 |
|  思想  |   贪心   |  动态规划  |
| 复杂度 |  O(n²)   |   O(n³)    |
| 负权边 |    ❌     |     ✅      |
| 代码量 |   中等   |    极简    |

### 最短路径 vs 最小生成树

|                               |        MST         |    最短路径    |
| :---------------------------: | :----------------: | :------------: |
|             目标              | 全连通，总代价最小 | 两点间代价最小 |
| MST 中的路径 ≠ 两点间最短路径 |

---

## 六、拓展内容（6.6–6.8，非重点，了解即可）

| 内容         | 一句话                                     |
| ------------ | ------------------------------------------ |
| **AOV 网**   | 顶点表示活动，弧表示先后关系               |
| **拓扑排序** | 把 AOV 网排成线性序列，满足所有先后关系    |
| **AOE 网**   | 边表示活动，顶点表示事件，有权值（时间）   |
| **关键路径** | AOE 网中从源点到汇点的最长路径，决定总工期 |
| **网络流**   | 求从源点到汇点的最大流量                   |

---

---

# 第二部分：核心代码汇总

---

## 一、存储结构定义

```c
#define MaxV 100      // 最大顶点数
#define INF 99999     // 无穷大

// ========== 邻接矩阵 ==========
typedef struct {
    int weight;       // 权值
} Edge;

typedef char Vertype;  // 顶点信息类型

Vertype Vertex[MaxV];
Edge    G[MaxV][MaxV];
int     n, e;          // 顶点数、边数

// ========== 邻接表 ==========
typedef struct edge {
    int  adjvex;               // 邻接点在数组中的下标
    int  weight;               // 权值
    struct edge *next;         // 下一条边
} ELink;

typedef struct ver {
    Vertype vertex;            // 顶点信息
    ELink  *link;              // 指向第一条边
} VLink;

VLink G[MaxV];                 // 顶点数组

// ========== 边集数组（Kruskal 用）==========
typedef struct {
    int u, v;      // 起点、终点
    int weight;    // 权值
} EdgeSet;
```

---

## 二、深度优先搜索 DFS

```c
//邻接表
int Visited[MaxV] = {0};

// 递归核心
void DFS(VLink G[], int v) {
    ELink *p;
    Visited[v] = 1;                    // 标记已访问
    visit(G, v);                       // 访问顶点
    for(p = G[v].link; p != NULL; p = p->next)
        if(!Visited[p->adjvex])
            DFS(G, p->adjvex);         // 递归深入
}

// 外层：处理非连通图
void travelDFS(VLink G[], int n) {
    int i;
    for(i = 0; i < n; i++) Visited[i] = 0;
    for(i = 0; i < n; i++)
        if(!Visited[i]) DFS(G, i);
}

//邻接矩阵
int Visited[MaxV] = {0};

void DFS_Matrix(Edge G[][MaxV], int n, int v) {
    Visited[v] = 1;
    visit(v);
    for(int j = 0; j < n; j++)          // 扫描整行
        if(G[v][j].weight != 0 && !Visited[j]) // 有边且未访问
            DFS_Matrix(G, n, j);
}
```
---

## 三、广度优先搜索 BFS

```c
//邻接表
int Visited[MaxV] = {0};

void BFS(VLink G[], int v) {
    ELink *p;
    int Q[MaxV], front = 0, rear = 0;  // 简易队列

    Visited[v] = 1;                    // ⚠️ 入队前标记
    Q[rear++] = v;                     // 起点入队

    while(front < rear) {
        v = Q[front++];                // 出队
        visit(G, v);                   // 访问
        for(p = G[v].link; p != NULL; p = p->next)
            if(!Visited[p->adjvex]) {
                Visited[p->adjvex] = 1;// ⚠️ 入队前标记
                Q[rear++] = p->adjvex;
            }
    }
}

void travelBFS(VLink G[], int n) {
    int i;
    for(i = 0; i < n; i++) Visited[i] = 0;
    for(i = 0; i < n; i++)
        if(!Visited[i]) BFS(G, i);
}

//邻接矩阵上的 BFS
void BFS_Matrix(Edge G[][MaxV], int n, int v) {
    int Q[MaxV], front = 0, rear = 0;
    Visited[v] = 1;
    Q[rear++] = v;

    while(front < rear) {
        v = Q[front++];
        visit(v);
        for(int j = 0; j < n; j++)          // 扫描整行
            if(G[v][j].weight != 0 && !Visited[j]) {
                Visited[j] = 1;
                Q[rear++] = j;
            }
    }
}
```

---

## 四、Prim 算法

```c
void Prim(int G[][MaxV], int n) {
    int dist[MaxV];      // dist[i] = 顶点 i 到 U 集合的最小边权
    int adjvex[MaxV];    // adjvex[i] = 使 dist[i] 取最小值的 U 中顶点
    int S[MaxV] = {0};   // 已选集合
    int i, j, k;
    int totalWeight = 0;

    // 初始化：从顶点 0 出发
    S[0] = 1;
    for(i = 1; i < n; i++) {
        dist[i]   = G[0][i];      // 到 U={0} 的距离
        adjvex[i] = 0;
    }

    // 选 n-1 条边
    for(i = 0; i < n - 1; i++) {
        // ① 选：在 V-S 中找 dist 最小的顶点 k
        int min = INF;
        for(j = 0; j < n; j++)
            if(!S[j] && dist[j] < min) {
                min = dist[j];
                k = j;
            }

        if(min == INF) break;     // 图不连通
        S[k] = 1;
        totalWeight += min;
        printf("边 (%d,%d) 权=%d\n", adjvex[k], k, min);

        // ② 更新：用 k 去更新 V-S 中顶点的 dist 和 adjvex
        for(j = 0; j < n; j++)
            if(!S[j] && G[k][j] < dist[j]) {
                dist[j]   = G[k][j];
                adjvex[j] = k;
            }
    }
    printf("MST 总权值 = %d\n", totalWeight);
}
```

---

## 五、Kruskal 算法 + 并查集

```c
// ========== 并查集 ==========
int parent[MaxV];
int rank[MaxV];

void initUF(int n) {
    for(int i = 0; i < n; i++) {
        parent[i] = i;
        rank[i] = 0;
    }
}

int Find(int x) {
    if(parent[x] != x)
        parent[x] = Find(parent[x]);   // 路径压缩
    return parent[x];
}

void Union(int a, int b) {
    int rootA = Find(a), rootB = Find(b);
    if(rootA == rootB) return;
    // 按秩合并
    if(rank[rootA] < rank[rootB])
        parent[rootA] = rootB;
    else if(rank[rootA] > rank[rootB])
        parent[rootB] = rootA;
    else {
        parent[rootA] = rootB;
        rank[rootB]++;
    }
}

// ========== Kruskal 主算法 ==========
// 比较函数（供 qsort 使用）
int cmpEdge(const void *a, const void *b) {
    return ((EdgeSet*)a)->weight - ((EdgeSet*)b)->weight;
}

void Kruskal(EdgeSet edges[], int n, int e) {
    qsort(edges, e, sizeof(EdgeSet), cmpEdge);  // 边按权排序
    initUF(n);

    int cnt = 0, totalWeight = 0;
    for(int i = 0; i < e && cnt < n - 1; i++) {
        int u = edges[i].u, v = edges[i].v;
        if(Find(u) != Find(v)) {          // 不连通 → 安全
            Union(u, v);
            totalWeight += edges[i].weight;
            cnt++;
            printf("边 (%d,%d) 权=%d\n", u, v, edges[i].weight);
        }
    }
    if(cnt == n - 1)
        printf("MST 总权值 = %d\n", totalWeight);
    else
        printf("图不连通！\n");
}
```

---

## 六、Dijkstra 算法

```c
void Dijkstra(int G[][MaxV], int n, int start) {
    int dist[MaxV];    // dist[i] = start 到 i 的最短距离
    int path[MaxV];    // path[i] = i 在最短路径上的前驱
    int S[MaxV] = {0}; // 已确定集合
    int i, j, u, min;

    // 初始化
    for(i = 0; i < n; i++) {
        dist[i] = G[start][i];
        path[i] = (dist[i] < INF) ? start : -1;
    }
    dist[start] = 0;
    S[start] = 1;

    // 主循环
    for(i = 0; i < n - 1; i++) {
        // ① 选：在 V-S 中找 dist 最小的顶点 u
        min = INF; u = -1;
        for(j = 0; j < n; j++)
            if(!S[j] && dist[j] < min) {
                min = dist[j];
                u = j;
            }
        if(u == -1) break;         // 剩余顶点不可达
        S[u] = 1;

        // ② 松：用 u 更新邻居
        for(j = 0; j < n; j++)
            if(!S[j] && G[u][j] < INF
               && dist[u] + G[u][j] < dist[j]) {
                dist[j] = dist[u] + G[u][j];
                path[j] = u;
            }
    }

    // 输出结果
    for(i = 0; i < n; i++) {
        if(dist[i] == INF)
            printf("%d -> %d : 不可达\n", start, i);
        else
            printf("%d -> %d : 距离=%d\n", start, i, dist[i]);
    }
}
```

---

## 七、Floyd 算法

```c
void Floyd(int G[][MaxV], int n) {
    int D[MaxV][MaxV];     // 距离矩阵
    int path[MaxV][MaxV];  // path[i][j] = i→j 路径上 j 的前驱
    int i, j, k;

    // 初始化
    for(i = 0; i < n; i++)
        for(j = 0; j < n; j++) {
            D[i][j] = G[i][j];
            path[i][j] = (G[i][j] < INF && i != j) ? i : -1;
        }

    // 三重循环：依次插入中转点 k
    for(k = 0; k < n; k++)
        for(i = 0; i < n; i++)
            for(j = 0; j < n; j++)
                if(D[i][k] < INF && D[k][j] < INF
                   && D[i][k] + D[k][j] < D[i][j]) {
                    D[i][j] = D[i][k] + D[k][j];
                    path[i][j] = path[k][j];
                }

    // 检查负权回路
    for(i = 0; i < n; i++)
        if(D[i][i] < 0) {
            printf("存在负权回路！\n");
            return;
        }

    // 输出结果
    for(i = 0; i < n; i++)
        for(j = 0; j < n; j++)
            if(i != j && D[i][j] < INF)
                printf("%d -> %d : %d\n", i, j, D[i][j]);
}
```


> 🎯 以上是图这一章的完整知识体系。第一部分吃透概念和性质（尤其是 MST 判断题和算法对比选择题），第二部分每个算法都能默写核心结构。两相结合，期末考试足以应对。

需要我把这份总结保存到你的笔记本吗？或者你对其中某块还想再展开？
