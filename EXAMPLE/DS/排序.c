/**
 * 文件: 排序.c
 * 描述: 包含各种常见排序算法模板，包括选择排序、冒泡排序、直接插入排序、折半插入排序、堆排序、归并排序和快速排序。
 *       排序函数统一返回元素间的比较次数。
 */

#include <stdio.h>
#include <stdlib.h>

/**
 * 交换两个整型指针指向的数值
 * 参数：
 * - a: 第一个整数的指针地址
 * - b: 第二个整数的指针地址
 * 返回值：无
 */
void sortSwap(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

/**
 * 选择排序 (升序)
 * 参数：
 * - k: 待排序的一维整型数组
 * - n: 数组大小
 * 返回值：执行排序过程中的关键字比较总次数
 */
int sortSelect(int k[], int n)
{
    int i, j, d, temp, t = 0;

    for (i = 0; i < n - 1; i++)
    {
        d = i;
        for (j = i + 1; j < n; j++)
        {
            if (k[j] < k[d])
                d = j;
            t++;
        }
        if (d != i)
        {
            temp = k[d];
            k[d] = k[i];
            k[i] = temp;
        }
    }
    return t;
}

/**
 * 冒泡排序 (升序，从后向前扫描，若某趟无交换提前结束)
 * 参数：
 * - k: 待排序的一维整型数组
 * - n: 数组大小
 * 返回值：排序过程中的相邻元素比较总次数
 */
int sortBubble(int k[], int n)
{
    int i, j, flag = 1, temp, t = 0;

    for (i = n - 1; i > 0 && flag == 1; i--)
    {
        flag = 0;
        for (j = 0; j < i; j++)
        {
            if (k[j] > k[j + 1])
            {
                temp = k[j];
                k[j] = k[j + 1];
                k[j + 1] = temp;
                flag = 1;
            }
            t++;
        }
    }
    return t;
}

/**
 * 直接插入排序 (升序)
 * 参数：
 * - k: 待排序的一维整型数组
 * - n: 数组大小
 * 返回值：排序过程中的元素比较总次数
 */
int sortInsert(int k[], int n)
{
    int i, j, temp, t = 0;

    for (i = 1; i < n; i++)
    {
        temp = k[i];
        j = i - 1;
        while (j >= 0)
        {
            t++;
            if (k[j] <= temp)
                break;
            k[j + 1] = k[j];
            j--;
        }
        k[j + 1] = temp;
    }
    return t;
}

/**
 * 折半插入排序 (升序，利用折半查找确定新元素的插入位置)
 * 参数：
 * - k: 待排序的一维整型数组
 * - n: 数组大小
 * 返回值：排序过程中的折半插入关键字比较总次数
 */
int sortBinInsert(int k[], int n)
{
    int i, low, high, mid, temp, t = 0;

    for (i = 1; i < n; i++)
    {
        temp = k[i];
        low = 0;
        high = i - 1;
        while (low <= high)
        {
            mid = (low + high) / 2;
            t++;
            if (k[mid] <= temp)
                low = mid + 1;
            else
                high = mid - 1;
        }
        for (mid = i - 1; mid >= low; mid--)
            k[mid + 1] = k[mid];
        k[low] = temp;
    }
    return t;
}

/**
 * 堆调整核心函数 (下沉调整根节点以维持大顶堆属性)
 * 参数：
 * - k: 待排序数组
 * - i: 待调整下沉的根节点下标
 * - n: 当前调整涉及的最大堆边界元素个数
 * 返回值：根与左右孩子的大小关系比较次数
 */
int sortHeapAdjust(int k[], int i, int n)
{
    int j, temp, t = 0;

    temp = k[i];
    j = 2 * i + 1;
    while (j < n)
    {
        t++;
        if (j < n - 1 && k[j] < k[j + 1])
            j++;
        if (temp >= k[j])
            break;
        k[(j - 1) / 2] = k[j];
        j = 2 * j + 1;
    }
    k[(j - 1) / 2] = temp;
    return t;
}

/**
 * 堆排序 (升序，先建大顶堆，然后依次交换并向下调整)
 * 参数：
 * - k: 待排序数组
 * - n: 数组大小
 * 返回值：排序总比较次数
 */
int sortHeap(int k[], int n)
{
    int i, temp, t = 0;

    // 1. 从第一个非叶子节点向上依次建大顶堆
    for (i = n / 2 - 1; i >= 0; i--)
        t += sortHeapAdjust(k, i, n);
    
    // 2. 依次交换堆顶与堆尾，并重新向下调整
    for (i = n - 2; i >= 0; i--)
    {
        temp = k[i + 1];
        k[i + 1] = k[0];
        k[0] = temp;
        t += sortHeapAdjust(k, 0, i + 1);
    }
    return t;
}

/**
 * 归并排序中合并两段有序区间的核心函数
 * 参数：
 * - x: 原数组
 * - tmp: 存放归并中间结果的辅助数组首地址
 * - left: 左半区区间起点下标
 * - leftend: 左半区区间终点下标
 * - rightend: 右半区区间终点下标
 * 返回值：归并数据排序时的两两比较次数
 */
int sortMerge(int x[], int tmp[], int left, int leftend, int rightend)
{
    int i = left, j = leftend + 1, q = left, t = 0;

    // 双指针移动比较归并
    while (i <= leftend && j <= rightend)
    {
        t++;
        if (x[i] <= x[j])
            tmp[q++] = x[i++];
        else
            tmp[q++] = x[j++];
    }
    while (i <= leftend)
        tmp[q++] = x[i++];
    while (j <= rightend)
        tmp[q++] = x[j++];
    
    // 将归并结果复制回原数组
    for (i = left; i <= rightend; i++)
        x[i] = tmp[i];
    return t;
}

/**
 * 归并排序分治递归体
 * 参数：
 * - k: 待排数组
 * - tmp: 辅助缓存数组
 * - left: 当前处理区间的下界
 * - right: 当前处理区间的上界
 * 返回值：该区间归并的总比较次数
 */
int sortMergeRec(int k[], int tmp[], int left, int right)
{
    int center, t = 0;

    if (left < right)
    {
        center = (left + right) / 2;
        t += sortMergeRec(k, tmp, left, center);
        t += sortMergeRec(k, tmp, center + 1, right);
        t += sortMerge(k, tmp, left, center, right);
    }
    return t;
}

/**
 * 二路归并排序 (升序)
 * 参数：
 * - k: 待排一维整型数组
 * - tmp: 由外部调用方分配提供的等长临时缓存空间数组首地址
 * - n: 数组大小
 * 返回值：归并排序的总比较次数
 */
int sortMergeSort(int k[], int tmp[], int n)
{
    if (n <= 0)
        return 0;
    return sortMergeRec(k, tmp, 0, n - 1);
}

/**
 * 快速排序 (以首元素 left 作为基准的划分交换排序)
 * 参数：
 * - k: 待排数组
 * - left: 当前划分范围的左边界
 * - right: 当前划分范围的右边界
 * 返回值：快速排序递归过程中的总元素比较次数
 */
int sortQuick(int k[], int left, int right)
{
    int i, last, t = 0;

    if (left < right)
    {
        last = left;
        // 移位重构划分
        for (i = left + 1; i <= right; i++)
        {
            if (k[i] < k[left])
                sortSwap(&k[++last], &k[i]);
            t++;
        }
        sortSwap(&k[left], &k[last]);
        t += sortQuick(k, left, last - 1);
        t += sortQuick(k, last + 1, right);
    }
    return t;
}
