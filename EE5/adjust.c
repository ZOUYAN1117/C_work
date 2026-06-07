#include <stdio.h>
#include <stdlib.h>

// 定义树分叉节点结构体
struct Node
{
    int id;           // 节点编号
    int children[3];  // 存储子节点编号，由于树的度为3，所以最多3个
    int num_children; // 实际的子节点个数
};

struct Node nodes[205]; // 存储所有的分叉节点
int num_nodes = 0;

// 查找分叉节点在数组中的索引，如果不存在则新建并返回新索引
int get_node_index(int id)
{
    for (int i = 0; i < num_nodes; ++i)
    {
        if (nodes[i].id == id)
        {
            return i;
        }
    }
    nodes[num_nodes].id = id;
    nodes[num_nodes].num_children = 0;
    return num_nodes++;
}

// 定义登机口结构体
struct Gate
{
    int id;      // 登机口编号
    int traffic; // 流量
};

// qsort 的比较函数：按流量降序排序，若流量相同则按编号升序排序
int cmp_gates(const void *a, const void *b)
{
    struct Gate *ga = (struct Gate *)a;
    struct Gate *gb = (struct Gate *)b;
    if (ga->traffic != gb->traffic)
    {
        return gb->traffic - ga->traffic; // 流量从大到小
    }
    return ga->id - gb->id; // 编号从小到大
}

int main()
{
    int r;

    // 1. 读取树形结构关系
    while (scanf("%d", &r) == 1 && r != -1)
    {
        int r_idx = get_node_index(r);
        int child_id;
        // 依次读取当前分叉节点的所有子节点，遇到 -1 停止
        while (scanf("%d", &child_id) == 1 && child_id != -1)
        {
            nodes[r_idx].children[nodes[r_idx].num_children++] = child_id;
        }
    }

    // 2. 读取所有的登机口及其流量数据
    struct Gate gates[205];
    int num_gates = 0;
    while (scanf("%d %d", &gates[num_gates].id, &gates[num_gates].traffic) == 2)
    {
        num_gates++;
    }

    // 3. 对将要调整的登机口进行排序
    qsort(gates, num_gates, sizeof(struct Gate), cmp_gates);

    // 4. 使用层序遍历 (BFS) 获得调整目标的坑位顺序
    int target_gates[205];
    int num_targets = 0;

    int queue[1005];
    int head = 0, tail = 0;

    queue[tail++] = 100; // 树根是安检口，编号为100，入队

    while (head < tail)
    {
        int curr_id = queue[head++];

        // 如果编号小于 100，说明是叶节点（即登机口），将其加入目标序列
        if (curr_id < 100)
        {
            target_gates[num_targets++] = curr_id;
        }
        else
        {
            // 如果是分叉节点，将其所有从左到右的子节点加入队列
            int idx = get_node_index(curr_id);
            for (int i = 0; i < nodes[idx].num_children; ++i)
            {
                queue[tail++] = nodes[idx].children[i];
            }
        }
    }

    // 5. 将排好序的登机口依次分配到找出的目标坑位上并输出
    for (int i = 0; i < num_gates && i < num_targets; ++i)
    {
        printf("%d->%d\n", gates[i].id, target_gates[i]);
    }

    return 0;
}
