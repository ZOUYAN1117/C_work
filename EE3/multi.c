#include <stdio.h>
#include <stdlib.h>

// 定义多项式链表节点结构体
struct node
{
    int base, power;   // base表示系数(coefficient)，power表示指数(exponent)
    struct node *link; // 指向下一个节点的指针(单向链表)
};

int main()
{
    int base, power;
    // list, tail 用于存放第一个输入的多项式
    // list1, tail1 用于存放第二个输入的多项式
    // list2 用于存放最终相乘结果的多项式（降序排列）
    struct node *list = NULL, *tail = NULL, *p, *list1 = NULL, *tail1 = NULL, *list2 = NULL;
    char c;

    // ---------------- 1. 读取第一条链（第一个多项式） ----------------
    // 采用尾插法构建单链表。以回车符('\n')作为输入结束的标志
    while (1)
    {
        scanf("%d%d%c", &base, &power, &c);
        p = (struct node *)malloc(sizeof(struct node)); // 动态分配新节点内存
        p->power = power;
        p->base = base;
        p->link = NULL;

        if (list == NULL) // 若链表为空，首尾指针均指向该新节点
            list = tail = p;
        else
        {
            tail->link = p; // 将新节点接入链表尾部
            tail = p;       // 尾指针后移
        }
        if (c == '\n') // 检测到换行符则跳出循环，结束第一个多项式的读取
            break;
    }

    // ---------------- 2. 读取第二条链（第二个多项式） ----------------
    // 同样使用尾插法，但结束条件变为遇到EOF（或无法再成功读取两个整数）
    while (scanf("%d%d", &base, &power) == 2)
    {
        p = (struct node *)malloc(sizeof(struct node));
        p->power = power;
        p->base = base;
        p->link = NULL;

        if (list1 == NULL)
            list1 = tail1 = p;
        else
        {
            tail1->link = p;
            tail1 = p;
        }
    }

    // ---------------- 3. 两多项式相乘之后插入结果链表 ----------------
    struct node *pa, *pb;
    // 两层for循环：遍历第一个多项式的每一项 与 第二个多项式的每一项进行相乘
    for (pa = list; pa != NULL; pa = pa->link)
    {
        for (pb = list1; pb != NULL; pb = pb->link)
        {
            int nb = pa->base * pb->base;   // 系数相乘 (new base)
            int np = pa->power + pb->power; // 指数相加 (new power)

            // 为本次乘积准备一个新的链表节点
            // 目标：将该节点按指数从大到小插入到 list2 链表中
            p = (struct node *)malloc(sizeof(struct node));
            p->power = np;
            p->base = nb;
            p->link = NULL;

            if (list2 == NULL) // 如果结果链表目前还是空的，直接把新节点当作头部
            {
                list2 = p;
                continue;
            }

            // t 作为遍历指针，用于在 list2 中寻找合适的插入位置
            struct node *t = list2;
            while (t != NULL)
            {
                // 情况 A：要插入的项指数比当前 t (比如头节点) 的指数还要大，应插在 t 的前面
                // 【潜藏Bug提示】：这里 p->link = t 后，如果 t 是等于 list2，并没有执行 list2 = p。
                // 这会导致插入的新节点虽然接上了，但链表的总头指针未能变更，丢失了更高的指数项。
                if (t->power < p->power)
                {
                    p->link = t;
                    break;
                }

                // 情况 B：遍历到了链表的最后一个节点，依然没有找到比自己指数小的项
                // 说明新节点的指数是目前最小的，直接接在链表末尾
                if (t->link == NULL)
                {
                    p->link = t->link; // 等同于 p->link = NULL;
                    t->link = p;
                    break;
                }

                // 情况 C：找到了合适的中间位置（前一个节点的指数 > 新指数 > 后一个节点的指数）
                // 执行标准链表中间插入：将新节点 p 插入到 t 和 t->link 之间
                if (t->link->power < p->power)
                {
                    p->link = t->link;
                    t->link = p;
                    break;
                }

                // 情况 D：发现已有相同指数的项，属于“同类项”
                // 把系数累加到已有的项上即可（即合并同类项）
                // 【潜藏Bug提示】：此时前面 malloc 出来的新节点 p 就成了没用的“孤儿”，且缺少 free(p)，会造成内存泄漏。
                if (t->link->power == p->power)
                {
                    t->link->base += p->base;
                    break;
                }

                t = t->link; // 找不到合适位置，继续向后判断下一个
            }
        }
    }

    // ---------------- 4. 遍历输出相加合并后的结果链表 ----------------
    p = list2;
    while (p != NULL)
    {
        printf("%d %d ", p->base, p->power); // 格式要求：系数 指数
        p = p->link;
    }
    // 【建议】：程序结束前通常应该写一个循环把之前malloc出的链表全部free掉
    return 0;
}
