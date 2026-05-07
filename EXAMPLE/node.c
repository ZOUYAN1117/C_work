struct node
{
    int m;
    struct node *link;
};

// 将数字按从小到大的顺序插入链表，并返回新的链表头指针
struct node *insert_sorted(struct node *list, int a)
{
    // 1. 创建并初始化新节点
    struct node *p = (struct node *)malloc(sizeof(struct node));
    p->m = a;
    p->link = NULL;

    // 2. 如果链表为空，或者新数字比头节点还小（或相等）
    // 那么新节点就应该作为新的头节点
    if (list == NULL || list->m >= a)
    {
        p->link = list;
        return p;
    }

    // 3. 寻找中间或末尾的插入位置
    struct node *q = list;
    // 当下一个节点不为空，且下一个节点的值小于要插入的值时，指针后移
    while (q->link != NULL && q->link->m < a)
    {
        q = q->link;
    }

    // 4. 将新节点插入到找到的节点 q 的后面
    p->link = q->link;
    q->link = p;

    // 头指针没变，返回原来的头
    return list;
}

// 1. 在链表尾部追加节点（普通单链表构建）
void append_node(struct node **list, struct node **tail, char data)
{
    struct node *p = (struct node *)malloc(sizeof(struct node));
    p->c = data;
    p->link = NULL;

    if (*list == NULL)
    {
        *list = p;
        *tail = p;
    }
    else
    {
        (*tail)->link = p;
        *tail = p;
    }
}

// 3. 约瑟夫环节点删除 (在循环链表中向后走 n 步并移除对应节点)
// 参数：
// list: 当前节点的指针的首地址
// tail: 当前节点的前驱指针的首地址（在循环链表中，即前一个节点）
// step: 需要走几步。比如当前节点走1步就删除，传 1。
// 返回值：被移除节点的内部数据 char
char pop_josephus_node(struct node **list, struct node **tail, int step)
{
    char result_data;

    // 只有一个节点了
    if (*list == *list->link)
    {
        result_data = (*list)->c;
        free(*list);
        *list = NULL;
        *tail = NULL;
        return result_data;
    }

    // 走 step - 1 次跨越
    while (--step > 0)
    {
        *list = (*list)->link;
        *tail = (*tail)->link;
    }

    // 摘除当前节点 (*list)
    struct node *temp = *list;
    result_data = temp->c;

    // 前驱节点指向后继节点，修复断链
    (*tail)->link = temp->link;

    // 移动当前节点指针到下一个节点
    *list = temp->link;

    free(temp); // 原代码未释放内存，这里加上

    return result_data;
}

// 4. 判断循环链表是否只剩最后一个节点
int is_last_node(struct node *list)
{
    return (list != NULL && list == list->link);
}

// 1. 构建初始链表
for (int i = 0; key[i] != '\0'; i++)
{
    append_node(&list, &tail, key[i]);
}
