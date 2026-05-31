/*
 * 顺序表（数组实现的线性表）
 *
 * 使用方法：把本文件开头的 #include、结构体定义，以及你需要的函数
 *           一起复制到你的 .c 文件中即可。
 *
 * 约定：函数返回 1 表示成功，返回 0 表示失败（越界、表满等）。
 *       下标 pos 从 0 开始，合法范围见各函数注释。
 */

#include <stdio.h>

/* ========== 顺序表：结构体定义 ========== */

#define SEQ_MAX 1000   /* 最大元素个数，可按题目改小，如 100 */

typedef struct {
    int data[SEQ_MAX];
    int length;        /* 当前元素个数，合法下标为 0 .. length-1 */
} SeqList;

/* ========== 顺序表：初始化与状态 ========== */

/*
 * 功能：清空顺序表，长度置 0
 * 参数：list - 顺序表
 * 返回：无
 *
 * 使用示例：
 *   SeqList list;
 *   initSeqList(&list);
 */
void initSeqList(SeqList *list)
{
    list->length = 0;
}

/*
 * 功能：判断顺序表是否为空
 * 返回：1 空，0 非空
 *
 * 使用示例：
 *   if (seqIsEmpty(&list)) printf("表为空\n");
 */
int seqIsEmpty(const SeqList *list)
{
    return list->length == 0;
}

/*
 * 功能：判断顺序表是否已满
 * 返回：1 满，0 未满
 *
 * 使用示例：
 *   if (seqIsFull(&list)) printf("表已满\n");
 */
int seqIsFull(const SeqList *list)
{
    return list->length >= SEQ_MAX;
}

/*
 * 功能：获取当前元素个数
 * 返回：元素个数
 *
 * 使用示例：
 *   int n = seqLength(&list);
 */
int seqLength(const SeqList *list)
{
    return list->length;
}

/*
 * 功能：清空顺序表（与 initSeqList 相同）
 * 返回：无
 *
 * 使用示例：
 *   seqClear(&list);
 */
void seqClear(SeqList *list)
{
    list->length = 0;
}

/* ========== 顺序表：访问元素 ========== */

/*
 * 功能：读取下标 index 处的元素
 * 参数：index 范围 0 .. length-1
 * 返回：1 成功（值写入 *out），0 失败（越界）
 *
 * 使用示例：
 *   int x;
 *   if (seqGet(&list, 0, &x)) printf("%d\n", x);
 */
int seqGet(const SeqList *list, int index, int *out)
{
    if (index < 0 || index >= list->length)
        return 0;
    *out = list->data[index];
    return 1;
}

/*
 * 功能：修改下标 index 处的元素
 * 参数：index 范围 0 .. length-1
 * 返回：1 成功，0 失败（越界）
 *
 * 使用示例：
 *   seqSet(&list, 0, 99);
 */
int seqSet(SeqList *list, int index, int value)
{
    if (index < 0 || index >= list->length)
        return 0;
    list->data[index] = value;
    return 1;
}

/* ========== 顺序表：尾部操作 ========== */

/*
 * 功能：在表尾追加元素
 * 返回：1 成功，0 失败（表已满）
 *
 * 使用示例：
 *   seqAppend(&list, 10);
 *   seqAppend(&list, 20);
 */
int seqAppend(SeqList *list, int value)
{
    if (list->length >= SEQ_MAX)
        return 0;
    list->data[list->length] = value;
    list->length++;
    return 1;
}

/*
 * 功能：删除表尾元素
 * 返回：1 成功（删除的值写入 *out），0 失败（表为空）
 *
 * 使用示例：
 *   int x;
 *   if (seqRemoveLast(&list, &x)) printf("删掉 %d\n", x);
 */
int seqRemoveLast(SeqList *list, int *out)
{
    if (list->length == 0)
        return 0;
    list->length--;
    if (out != NULL)
        *out = list->data[list->length];
    return 1;
}

/* ========== 顺序表：头部操作 ========== */

/*
 * 功能：在表头插入元素（后面元素整体后移）
 * 返回：1 成功，0 失败（表已满）
 *
 * 使用示例：
 *   seqInsertFirst(&list, 5);
 */
int seqInsertFirst(SeqList *list, int value)
{
    int i;

    if (list->length >= SEQ_MAX)
        return 0;
    for (i = list->length; i > 0; i--)
        list->data[i] = list->data[i - 1];
    list->data[0] = value;
    list->length++;
    return 1;
}

/*
 * 功能：删除表头元素
 * 返回：1 成功，0 失败（表为空）
 *
 * 使用示例：
 *   int x;
 *   seqRemoveFirst(&list, &x);
 */
int seqRemoveFirst(SeqList *list, int *out)
{
    int i;

    if (list->length == 0)
        return 0;
    if (out != NULL)
        *out = list->data[0];
    for (i = 0; i < list->length - 1; i++)
        list->data[i] = list->data[i + 1];
    list->length--;
    return 1;
}

/* ========== 顺序表：指定位置插入与删除 ========== */

/*
 * 功能：在下标 pos 处插入元素（原 pos 及之后元素后移）
 * 参数：pos 范围 0 .. length（pos==length 等价于尾插）
 * 返回：1 成功，0 失败（越界或表满）
 *
 * 使用示例：
 *   seqInsertAt(&list, 1, 100);   // 插到第 2 个位置
 */
int seqInsertAt(SeqList *list, int pos, int value)
{
    int i;

    if (pos < 0 || pos > list->length)
        return 0;
    if (list->length >= SEQ_MAX)
        return 0;
    for (i = list->length; i > pos; i--)
        list->data[i] = list->data[i - 1];
    list->data[pos] = value;
    list->length++;
    return 1;
}

/*
 * 功能：删除下标 pos 处的元素
 * 参数：pos 范围 0 .. length-1
 * 返回：1 成功，0 失败（越界）
 *
 * 使用示例：
 *   int x;
 *   seqDeleteAt(&list, 0, &x);
 */
int seqDeleteAt(SeqList *list, int pos, int *out)
{
    int i;

    if (pos < 0 || pos >= list->length)
        return 0;
    if (out != NULL)
        *out = list->data[pos];
    for (i = pos; i < list->length - 1; i++)
        list->data[i] = list->data[i + 1];
    list->length--;
    return 1;
}

/* ========== 顺序表：查找 ========== */

/*
 * 功能：查找值 value 第一次出现的下标
 * 返回：1 找到（下标写入 *index），0 未找到
 *
 * 使用示例：
 *   int idx;
 *   if (seqFind(&list, 10, &idx)) printf("在下标 %d\n", idx);
 */
int seqFind(const SeqList *list, int value, int *index)
{
    int i;

    for (i = 0; i < list->length; i++) {
        if (list->data[i] == value) {
            if (index != NULL)
                *index = i;
            return 1;
        }
    }
    return 0;
}

/*
 * 功能：统计值 value 在表中出现的次数
 * 返回：出现次数
 *
 * 使用示例：
 *   int cnt = seqCount(&list, 10);
 */
int seqCount(const SeqList *list, int value)
{
    int i, cnt = 0;

    for (i = 0; i < list->length; i++) {
        if (list->data[i] == value)
            cnt++;
    }
    return cnt;
}

/* ========== 顺序表：辅助输出 ========== */

/*
 * 功能：按顺序打印所有元素（调试用）
 * 返回：无
 *
 * 使用示例：
 *   seqPrint(&list);   // 输出：10 20 30
 */
void seqPrint(const SeqList *list)
{
    int i;

    for (i = 0; i < list->length; i++) {
        printf("%d", list->data[i]);
        if (i < list->length - 1)
            printf(" ");
    }
    printf("\n");
}
