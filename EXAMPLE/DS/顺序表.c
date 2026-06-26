/**
 * 文件: 顺序表.c
 * 描述: 顺序存储结构（静态数组）实现的线性表基本操作，包括插入、删除、查找、遍历等。
 */

#include <stdio.h>

/**
 * 结构体: SeqList - 顺序表结构定义
 * 成员：
 * - data: 静态数组，存储整型数据元素
 * - length: 顺序表当前长度（即已存储的元素个数）
 */
#define SEQ_MAX 1000   /* 最大元素个数 */

typedef struct {
    int data[SEQ_MAX];
    int length;        /* 当前元素个数，合法下标为 0 .. length-1 */
} SeqList;

/**
 * 初始化顺序表（长度清 0）
 * 参数：
 * - list: 顺序表指针
 * 返回值：无
 */
void initSeqList(SeqList *list)
{
    // 将顺序表长度置为0
    list->length = 0;
}

/**
 * 判断顺序表是否为空
 * 参数：
 * - list: 顺序表指针
 * 返回值：1 表示为空，0 表示非空
 */
int seqIsEmpty(const SeqList *list)
{
    return list->length == 0;
}

/**
 * 判断顺序表是否已满
 * 参数：
 * - list: 顺序表指针
 * 返回值：1 表示已满，0 表示未满
 */
int seqIsFull(const SeqList *list)
{
    return list->length >= SEQ_MAX;
}

/**
 * 获取顺序表的当前元素个数
 * 参数：
 * - list: 顺序表指针
 * 返回值：顺序表当前元素个数
 */
int seqLength(const SeqList *list)
{
    return list->length;
}

/**
 * 清空顺序表 (效果同初始化)
 * 参数：
 * - list: 顺序表指针
 * 返回值：无
 */
void seqClear(SeqList *list)
{
    // 长度归零实现快速清空
    list->length = 0;
}

/**
 * 获取顺序表中指定下标位置的值
 * 参数：
 * - list: 顺序表指针
 * - index: 待读取元素的下标位置 (0-indexed)
 * - out: 指针，用于输出读取到的元素值
 * 返回值：1 表示读取成功，0 表示失败 (下标越界)
 */
int seqGet(const SeqList *list, int index, int *out)
{
    // 检查越界
    if (index < 0 || index >= list->length)
        return 0;
    
    // 写入输出值
    *out = list->data[index];
    return 1;
}

/**
 * 修改顺序表中指定下标位置的值
 * 参数：
 * - list: 顺序表指针
 * - index: 待修改元素的下标位置 (0-indexed)
 * - value: 新的值
 * 返回值：1 表示修改成功，0 表示失败 (下标越界)
 */
int seqSet(SeqList *list, int index, int value)
{
    // 检查越界
    if (index < 0 || index >= list->length)
        return 0;
    
    // 赋新值
    list->data[index] = value;
    return 1;
}

/**
 * 在顺序表尾部追加新元素
 * 参数：
 * - list: 顺序表指针
 * - value: 待追加的新元素值
 * 返回值：1 表示追加成功，0 表示失败 (表已满)
 */
int seqAppend(SeqList *list, int value)
{
    // 判断表是否已满
    if (list->length >= SEQ_MAX)
        return 0;
    
    // 在尾部下一位置填入值，并增加长度
    list->data[list->length] = value;
    list->length++;
    return 1;
}

/**
 * 删除顺序表尾部元素
 * 参数：
 * - list: 顺序表指针
 * - out: 指针，用于输出被删除的元素值
 * 返回值：1 表示删除成功，0 表示失败 (表为空)
 */
int seqRemoveLast(SeqList *list, int *out)
{
    // 判断表是否为空
    if (list->length == 0)
        return 0;
    
    // 缩减长度，并在需要时传回被删除元素的值
    list->length--;
    if (out != NULL)
        *out = list->data[list->length];
    return 1;
}

/**
 * 在顺序表头部插入新元素 (原元素整体后移)
 * 参数：
 * - list: 顺序表指针
 * - value: 待插入的新元素值
 * 返回值：1 表示插入成功，0 表示失败 (表已满)
 */
int seqInsertFirst(SeqList *list, int value)
{
    int i;

    // 判断表是否已满
    if (list->length >= SEQ_MAX)
        return 0;
    
    // 元素依次向后移一位
    for (i = list->length; i > 0; i--)
        list->data[i] = list->data[i - 1];
    
    // 头部填入新值，长度增加
    list->data[0] = value;
    list->length++;
    return 1;
}

/**
 * 删除顺序表头部元素 (原元素整体前移)
 * 参数：
 * - list: 顺序表指针
 * - out: 指针，用于输出被删除的元素值
 * 返回值：1 表示删除成功，0 表示失败 (表为空)
 */
int seqRemoveFirst(SeqList *list, int *out)
{
    int i;

    // 判断表是否为空
    if (list->length == 0)
        return 0;
    
    // 传回头部原有的值
    if (out != NULL)
        *out = list->data[0];
    
    // 元素依次前移一位
    for (i = 0; i < list->length - 1; i++)
        list->data[i] = list->data[i + 1];
    
    // 缩减长度
    list->length--;
    return 1;
}

/**
 * 在顺序表指定位置 pos 插入新元素 (原 pos 及其后元素整体后移)
 * 参数：
 * - list: 顺序表指针
 * - pos: 插入目标下标位置 (pos 范围应为 0 .. length)
 * - value: 待插入的新元素值
 * 返回值：1 表示插入成功，0 表示失败 (pos越界或表满)
 */
int seqInsertAt(SeqList *list, int pos, int value)
{
    int i;

    // 检查插入位置越界
    if (pos < 0 || pos > list->length)
        return 0;
    
    // 检查表满
    if (list->length >= SEQ_MAX)
        return 0;
    
    // 从表尾到 pos 的元素全部向后移动一位
    for (i = list->length; i > pos; i--)
        list->data[i] = list->data[i - 1];
    
    // 在指定位置填入新元素值，并增加长度
    list->data[pos] = value;
    list->length++;
    return 1;
}

/**
 * 删除顺序表指定位置 pos 的元素 (其后元素整体前移)
 * 参数：
 * - list: 顺序表指针
 * - pos: 待删除元素的下标位置 (pos 范围应为 0 .. length-1)
 * - out: 指针，用于输出被删除的元素值
 * 返回值：1 表示删除成功，0 表示失败 (下标越界)
 */
int seqDeleteAt(SeqList *list, int pos, int *out)
{
    int i;

    // 检查删除下标越界
    if (pos < 0 || pos >= list->length)
        return 0;
    
    // 传回被删除元素的值
    if (out != NULL)
        *out = list->data[pos];
    
    // pos 之后的元素全部向前移动一位
    for (i = pos; i < list->length - 1; i++)
        list->data[i] = list->data[i + 1];
    
    // 长度缩减一位
    list->length--;
    return 1;
}

/**
 * 在顺序表中查找指定元素值 value 第一次出现的下标位置
 * 参数：
 * - list: 顺序表指针
 * - value: 待查找的元素值
 * - index: 指针，用于输出查找到的下标
 * 返回值：1 表示查找成功，0 表示未找到
 */
int seqFind(const SeqList *list, int value, int *index)
{
    int i;

    // 顺序遍历查找
    for (i = 0; i < list->length; i++) {
        if (list->data[i] == value) {
            if (index != NULL)
                *index = i;
            return 1;
        }
    }
    return 0;
}

/**
 * 统计指定元素值 value 在顺序表中出现的次数
 * 参数：
 * - list: 顺序表指针
 * - value: 待统计的元素值
 * 返回值：出现次数
 */
int seqCount(const SeqList *list, int value)
{
    int i, cnt = 0;

    // 顺序统计出现次数
    for (i = 0; i < list->length; i++) {
        if (list->data[i] == value)
            cnt++;
    }
    return cnt;
}

/**
 * 按顺序打印顺序表中的所有元素 (以空格分隔，末尾换行)
 * 参数：
 * - list: 顺序表指针
 * 返回值：无
 */
void seqPrint(const SeqList *list)
{
    int i;

    // 依次打印元素，中间以空格分隔
    for (i = 0; i < list->length; i++) {
        printf("%d", list->data[i]);
        if (i < list->length - 1)
            printf(" ");
    }
    printf("\n");
}
