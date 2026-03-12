#include <stdio.h>
#include <string.h>
int compare(long long a, long long b) { return a - b; }
void swap(long long *a, long long *b) {
  long long temp;
  temp = *a;
  *a = *b;
  *b = temp;
}
void stoogeSort(long long array[], int arraySize) {
  if (compare(array[0], array[arraySize - 1]) > 0) {
    swap(&array[0], &array[arraySize - 1]); // TODO
  }
  if (arraySize >= 3) {
    int third = arraySize / 3;
    stoogeSort(array, arraySize - third);
    stoogeSort(array + third, arraySize - third);
    stoogeSort(array, arraySize - third);
  }
}
long long a[1003];
int main() {
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    scanf("%lld", &a[i]);
  }
  stoogeSort(a, n);
  for (int i = 0; i < n; i++) {
    printf("%lld ", a[i]);
  }
}