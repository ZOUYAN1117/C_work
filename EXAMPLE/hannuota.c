// 从A开始，n个盘子
#include <stdio.h>
void hanoi(int n, char a, char b, char c); // 接口清晰
void move(int i, char from, char to);
int main() {
  int num;
  char a = 'A', b = 'B', c = 'C';
  scanf("%d", &num);
  hanoi(num, a, b, c);
  return 0;
}

void hanoi(int n, char from, char via, char to) {
  if (n == 1) {
    move(n, from, to);
    return;
  }
  hanoi(n - 1, from, to, via); // 递归：挪上面的n-1个盘子
  move(n, from, to);           // 移动第n个盘子
  hanoi(n - 1, via, from, to); // 递归：挪n-1个盘子
}

void move(int i, char from, char to) {
  printf("Distk %d, %c --> %c\n", i, from, to);
}

// 规定数目，开始和结束
#include <stdio.h>
void moveDisk(int disk, int source, int destination) {
  printf("Electromagnet move disk %d from %d to %d\n", disk, source,
         destination);
}
void hanoi(int diskCount, int source, int destination, int spare) {
  if (diskCount == 1) {
    moveDisk(diskCount, source, destination);
    return;
  }
  hanoi(diskCount - 1, source, spare, destination);
  moveDisk(diskCount, source, destination);
  hanoi(diskCount - 1, spare, destination, source);
  return;
}
int main() {
  int diskCount = 0, source = 0, destination = 0, spare = 0;
  scanf("%d%d%d%d", &diskCount, &source, &destination, &spare);
  hanoi(diskCount, source, destination, spare);
  return 0;
}