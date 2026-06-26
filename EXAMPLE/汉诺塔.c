/**
 * 文件: 汉诺塔.c
 * 描述: 经典汉诺塔问题的递归求解模板，提供字符式柱子名称与数字式柱子编号两种求解版本。
 */

#include <stdio.h>

/**
 * 打印单次盘子移动的轨迹 (字符名称版)
 * 参数：
 * - i: 盘子编号 (1 为最上方盘子)
 * - from: 起始柱子字符名 (如 'A')
 * - to: 目标柱子字符名 (如 'C')
 * 返回值：无
 */
void move_char(int i, char from, char to) {
    printf("Disk %d, %c --> %c\n", i, from, to);
}

/**
 * 递归模拟汉诺塔盘子移动过程 (字符名称版)
 * 参数：
 * - n: 当前操作的盘子总数
 * - from: 起始柱子名称
 * - via: 辅助过渡柱子名称
 * - to: 目标柱子名称
 * 返回值：无
 */
void hanoi_char(int n, char from, char via, char to) {
    if (n == 1) {
        move_char(n, from, to);
        return;
    }
    // 递归：将上方 n-1 个盘子从 from 搬移到 via
    hanoi_char(n - 1, from, to, via);
    // 将第 n 个盘子直接从 from 搬移到 to
    move_char(n, from, to);
    // 递归：将刚才的 n-1 个盘子从 via 搬移到 to
    hanoi_char(n - 1, via, from, to);
}

/**
 * 打印单次盘子移动的轨迹 (数字编号版)
 * 参数：
 * - disk: 盘子编号 (1 为最上方盘子)
 * - source: 起始柱子数字编号
 * - destination: 目标柱子数字编号
 * 返回值：无
 */
void moveDisk_int(int disk, int source, int destination) {
    printf("Electromagnet move disk %d from %d to %d\n", disk, source, destination);
}

/**
 * 递归模拟汉诺塔盘子移动过程 (数字编号版)
 * 参数：
 * - diskCount: 当前操作的盘子总数
 * - source: 起始柱子数字编号
 * - destination: 目标柱子数字编号
 * - spare: 辅助过渡柱子数字编号
 * 返回值：无
 */
void hanoi_int(int diskCount, int source, int destination, int spare) {
    if (diskCount == 1) {
        moveDisk_int(diskCount, source, destination);
        return;
    }
    // 递归：将上方 diskCount-1 个盘子从 source 搬移到 spare
    hanoi_int(diskCount - 1, source, spare, destination);
    // 将第 diskCount 个盘子从 source 搬移到 destination
    moveDisk_int(diskCount, source, destination);
    // 递归：将上方 diskCount-1 个盘子从 spare 搬移到 destination
    hanoi_int(diskCount - 1, spare, destination, source);
}

/*
// 演示如何调用字符版汉诺塔的示例函数
int run_hanoi_char_demo() {
    int num;
    char a = 'A', b = 'B', c = 'C';
    if (scanf("%d", &num) == 1) {
        hanoi_char(num, a, b, c);
    }
    return 0;
}

// 演示如何调用数字版汉诺塔的示例函数
int run_hanoi_int_demo() {
    int diskCount, source, destination, spare;
    if (scanf("%d%d%d%d", &diskCount, &source, &destination, &spare) == 4) {
        hanoi_int(diskCount, source, destination, spare);
    }
    return 0;
}
*/