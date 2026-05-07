struct node
{
    int m;
    struct node *link;
};

// 将数字按从小到大的顺序插入链表，并返回新的链表头指针
struct node* insert_sorted(struct node *list, int a)
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