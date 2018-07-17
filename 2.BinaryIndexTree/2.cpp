#include "../tools/getin.hpp"

using namespace std;
using namespace wy;

#define lowbit(x) ((x) & (-(x)))
// lowbit 返回一个二进制数字的最低位1
// 例如88的二进制是01011000
// lowbit(88)就是00001000
// 这个位运算计算方法的原理是 x 的最低位1是 ~x 的最低位0
// ~x + 1 就是把结尾的一系列1变成0，最低位0变成1
// 那么 x & (~x + 1) 就是 x 的最低位1
// 根据补码的计算，~x + 1 = -x
// 所以得出 x & (-x)

// 树状数组结构图:
//                                                  +------+
//                         +----------------------->|      |
//                         |              +-------->| C[8] |
//                         |              |     +-->|      |
//                      +--+---+          |     |   +---+--+
//                      |      |          |     |       ^
//           +--------->| C[4] |          |     |       |
//           |       +->|      |          |     |       |
//        +--+---+   |  +---+--+      +---+--+  |       |
//        |      |   |      ^         |      |  |       |
//   +--->| C[2] |   |      |    +--->| C[6] |  |       |
//   |    |      |   |      |    |    |      |  |       |
//   |    +---+--+   |      |    |    +---+--+  |       |
//   |        ^      |      |    |        ^     |       |
// +-+----+   |  +---+--+   |  +-+----+   |  +--+---+   |
// |      |   |  |      |   |  |      |   |  |      |   |
// | C[1] |   |  | C[3] |   |  | C[5] |   |  | C[7] |   |
// |      |   |  |      |   |  |      |   |  |      |   |
// +------+---+--+------+---+--+------+---+--+------+---+--+--
// |      |      |      |      |      |      |      |      |
// | a[1] | a[2] | a[3] | a[4] | a[5] | a[6] | a[7] | a[8] |
// |      |      |      |      |      |      |      |      |
// +------+------+------+------+------+------+------+------+--

// 树状数组中，第 n 个节点的父节点在 arr[n + lowbit(n)]
// 更新树状数组时，只需要更新节点的每一个父节点
// 时间复杂度 O(log n)
void update(int arr[], int count, int i, int value) {
    for (; i < count + 1; i += lowbit(i)) arr[i] += value;
}

// 利用树状数组求前缀和
int sum(int arr[], int n) {
    int ans = 0;
    for (; n; n -= lowbit(n)) ans += arr[n];
    return ans;
}

// 利用树状数组求 [a, b) 的区间和
int sum(int arr[], int a, int b) { return sum(arr, b - 1) - sum(arr, a - 1); }

// 获取原始数组的元素
int get(int arr[], int n) {
    if (n % 2 == 1) return n;
    else return arr[n] - sum(arr, n-1);
}

int main(int argc, char* argv[]) {
    cout << "Binary Index Tree" << endl;
    int output[256];
    // 获取数组
    int count = get_ints(output);
    // 生成树状数组
    int tree[256];
    for (int i = 1; i <= count; i++) tree[i] = 0;  // 初始化
    for (int i = 1; i <= count; i++) update(tree, count, i, output[i - 1]);
    cout << "BIT build finished:" << endl;
    cout << '[';
    for (int i = 1; i <= count - 1; i++) {
        cout << tree[i] << ',';
    }
    cout << tree[count] << ']' << endl;
    // 查询前缀和
    int k = INT_MAX;
    while (true) {
        cout << " The sum of first k numbers:" << endl;
        cout << "k = ";
        cin >> k;
        if (k <= count) break;
        else
            cout << "Wrong Input!" << endl;
    }
    cout << "The sum of first " << k << " numbers = " << sum(tree, k) << endl;
    // 查询区间和
    int a = INT_MAX, b = INT_MAX;
    while (true) {
        cout << " The sum of [a, b) numbers:" << endl;
        cout << "a = ";
        cin >> a;
        cout << "b = ";
        cin >> b;
        if (a <= b && b <= count) break;
        else
            cout << "Wrong Input!" << endl;
    }
    cout << "The sum of [" << a << ", " << b << ") = " << sum(tree, a, b) << endl;
    pause_cin;
    return 0;
}