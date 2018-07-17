#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

// 其实这个程序是用 C 写的
// 但是因为从 2 号开始换了 C++
// tasks.json 只能设成 C++
// 这个就把拓展名改成 C++ 了
// 反正 C++ 向下兼容（逃

void q(int arr[], int left, int right) {
    // 对前闭后开区间 [left, right) 排序
    int n, pivot;
    int i, j;
    int mid;
    int lb, rb;
    if (left >= right - 1) {  // 只有一个数或者没有数
        return;
    } else if (left == right - 2) {  // 有两个数
        i = left;
        j = left + 1;
        if (arr[i] > arr[j]) {
            n = arr[i];
            arr[i] = arr[j];
            arr[j] = n;
        }
        return;
    }
    // 调整基准数到 arr[0]
    mid = (left + right) >> 1;
    i = arr[left] <= arr[right - 1] ? left : right - 1;
    j = left ^ (right - 1) ^ i;
    i = arr[i] > arr[mid] ? i : mid;
    n = arr[j] <= arr[i] ? j : i;  // 诡异的三数取中
    pivot = arr[n];
    arr[n] = arr[left];
    // arr[0] = pivot; // 没有必要，因为 arr[0] 迟早会被覆盖
    // 循环遍历
    lb = left + 1;
    rb = right;  // [lb, rb) 是未处理区间
    i = left;
    while (lb < rb - 1) {
        // 右扫描
        for (i = rb - 1; i >= lb; i--)
            if (arr[i] < pivot) {
                arr[lb - 1] = arr[i];
                rb = i + 1;
                break;
            }
        if (i < lb) break;
        //左扫描
        for (i = lb; i < rb; i++)
            if (arr[i] > pivot) {
                arr[rb - 1] = arr[i];
                lb = i + 1;
                break;
            }
        if (i >= rb) break;
    }
    if (i >= rb)
        n = rb - 1;
    else
        n = lb - 1;
    arr[n] = pivot;
    // 递归处理
    q(arr, left, n);
    q(arr, n + 1, right);
}

#define FUNC quicksort
int quicksort(int arr[], int n) {
    q(arr, 0, n);
    return n;
}

#define bool int
#define true 1
#define false 0

#define LEN 1024
int main(int argc, char *argv[]) {
    // 通用的数组数据输入、输出
    // 输入示例：[1,2,3,4,5]
    char input[LEN];
    char c;
    int i, j;
    int st;
    int output[LEN >> 2];
    int k = 0;
    printf("Quick Sort\n");
    printf("Please input an array:\n");
    fgets(input, LEN, stdin);
    // 开始分析输入数据
    bool finished = false;
    do {
        if (input[0] != '[') break;
        i = 1;
        j = 1;
        st = 0;
        while (input[i]) {  // 遍历字符串
            c = input[i];
            if ((c != ']') && (c != ',') && ((c < '0') || ('9' < c))) {
                break;
            }
            if (st == 0) {                       // 接受数字
                if (('0' <= c) && ('9' >= c)) {  // 如果是数字
                    st = 0;
                    i++;
                } else if (c == ',') {  // 逗号
                    st = 1;
                } else if (isspace(c)) {  // 空白符
                    st = 1;
                    i++;
                }
            } else if (st == 1) {  // 接受分隔符中
                if (c == ',') {
                    // 数字储存在前开后闭区间[j,i)中
                    output[k++] = atoi(&(input[j]));  // 获取数字
                    do {
                        i++;
                    } while (isspace(input[i]));  // 前进到下一个非空白字符
                    j = i;
                    st = 0;
                }
            }
            if (c == ']') {  // 处理完成
                finished = true;
                if (j == i) break;
                output[k++] = atoi(&(input[j]));  // 获取数字
                break;
            }
        }
    } while (false);
    if (!finished) {
        printf("Bad input!\n");
        return -1;
    }
    // 输出结果
    k = FUNC(output, k);
    if (k) {
        for (i = 0; i < k - 1; i++) {
            printf("%d,", output[i]);
        }
        printf("%d\n", output[k - 1]);
    }
    system("pause");
    return 0;
}