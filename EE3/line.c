#include <stdio.h>

// 只记录每条连续路径的 头、尾 和 包含的线段数
struct Path
{
    int sx, sy; // 起点 (start x, start y)
    int ex, ey; // 终点 (end x, end y)
    int len;    // 这条路径包含几个线段
};

int main()
{
    int n;
    if (scanf("%d", &n) != 1)
        return 0;

    struct Path paths[100];
    int path_count = 0;

    for (int i = 0; i < n; i++)
    {
        int x1, y1, x2, y2;
        scanf("%d %d %d %d", &x1, &y1, &x2, &y2);

        int append_idx = -1;  // 记录可以向后追加的路径索引
        int prepend_idx = -1; // 记录可以向前前置插入的路径索引

        // 查找当前的线段能和现有的哪条路径相接
        for (int j = 0; j < path_count; j++)
        {
            if (paths[j].ex == x1 && paths[j].ey == y1)
                append_idx = j;
            if (paths[j].sx == x2 && paths[j].sy == y2)
                prepend_idx = j;
        }

        if (append_idx != -1 && prepend_idx != -1)
        {
            // [情况 C]: 这个线段正好把两段路径桥接在了一起，合并它们
            paths[append_idx].ex = paths[prepend_idx].ex;
            paths[append_idx].ey = paths[prepend_idx].ey;
            paths[append_idx].len += 1 + paths[prepend_idx].len;

            // 删除被合并的第二条路径 (将其与最后一个元素交换后数组缩容)
            paths[prepend_idx] = paths[path_count - 1];
            path_count--;
        }
        else if (append_idx != -1)
        {
            // [情况 A]: 只能接到旧路径的后面
            paths[append_idx].ex = x2;
            paths[append_idx].ey = y2;
            paths[append_idx].len++;
        }
        else if (prepend_idx != -1)
        {
            // [情况 B]: 只能接到旧路径的前面
            paths[prepend_idx].sx = x1;
            paths[prepend_idx].sy = y1;
            paths[prepend_idx].len++;
        }
        else
        {
            // [情况 D]: 和谁都接不上，自己独立成为一条新路径
            paths[path_count].sx = x1;
            paths[path_count].sy = y1;
            paths[path_count].ex = x2;
            paths[path_count].ey = y2;
            paths[path_count].len = 1;
            path_count++;
        }
    }

    // 找出包含了最多线段的路径
    int max_len = -1, max_idx = 0;
    for (int i = 0; i < path_count; i++)
    {
        if (paths[i].len > max_len)
        {
            max_len = paths[i].len;
            max_idx = i;
        }
    }

    // 打印最长路径的长度及起点
    printf("%d %d %d\n", paths[max_idx].len, paths[max_idx].sx, paths[max_idx].sy);

    return 0;
}
