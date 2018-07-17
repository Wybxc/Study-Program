#include <iostream>
#include "../tools/getin.hpp"
#include "../tools/printing.hpp"

using namespace std;
using namespace wy;

void po(int first[], int f_left, int f_right, int mid[], int m_left,
        int m_right, int post[], int *k) {
    // 原理：first[f_left] 就是当前二叉树的根节点
    // 假设输入的 first 和 mid 中没有重复元素
    if (f_left >= f_right) return; 
    // In fact, 由于 f_right - f_left == m_right - m_right
    // (可以用归纳法证明)
    // 所以不需要检查 m_right 和 m_left 的关系
    int root = first[f_left];
    int r = 0;
    for (int i = m_left; i < f_right; i++) 
        if(mid[i] == root){ // 找到中序遍历中等于 root 的值
            r = i;          // 左边就是左子树
            break;          // 右边就是右子树
        }
    // 左子树：first{[f_left + 1, f_left + (r - m_left) + 1)}
    //        mid{[m_left, r)}
    po(first, f_left + 1, f_left + r - m_left + 1, mid, m_left, r, post, k);
    // 右子树：first{[f_left + (r - m_left) + 1, f_right)}
    //        mid{[r + 1, m_right)}
    po(first, f_left + (r - m_left) + 1, f_right, mid, r + 1, m_right, post, k);
    post[*k] = root;
    *k += 1;
}

void get_postorder(int first[], int mid[], int post[], int count) {
    int k = 0;
    po(first, 0, count, mid, 0, count, post, &k);
}

int main() {
    cout << "Get Postoder" << endl;
    int first[256], mid[256];
    cout << "First:" << endl;
    int count = get_ints(first);
    cout << "Middle:" << endl;
    get_ints(mid);
    int post[256];
    get_postorder(first, mid, post, count);
    cout << "Post:" << endl;
    print_arr(post, 0, count);
    pause_cin;
    return 0;
}