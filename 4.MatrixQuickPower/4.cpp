#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include "../tools/getin.hpp"

using namespace std;

template <int M_SIZE>
class Matrix {
   public:
    int m[M_SIZE][M_SIZE];
    // 初始化为空矩阵
    Matrix() { memset(m, 0, sizeof(m)); }
    // 用数组初始化
    Matrix(int vec[M_SIZE]) {
        for (int i = 0; i < M_SIZE; i++)
            for (int j = 0; j < M_SIZE; j++) {
                m[i][j] = vec[i * M_SIZE + j];
            }
    }
    // 用二重数组初始化
    Matrix(int vec[M_SIZE][M_SIZE]) {
        for (int i = 0; i < M_SIZE; i++)
            for (int j = 0; j < M_SIZE; j++) {
                m[i][j] = vec[i][j];
            }
    }
    // 用另一个矩阵初始化
    Matrix(Matrix<M_SIZE>* M) { memcpy(m, M->m, sizeof(m)); }
    // 返回一个新的单位阵
    static Matrix<M_SIZE> Identity() {
        Matrix<M_SIZE> ans;
        for (int i = 0; i < M_SIZE; i++)
            for (int j = 0; j < M_SIZE; j++)
                if (i == j)
                    ans.m[i][j] = 1;
                else
                    ans.m[i][j] = 0;
        return ans;
    }
    // 向量左乘矩阵
    void mul(int vec[M_SIZE]) {
        int ans[M_SIZE];
        memset(ans, 0, sizeof(ans));
        for (int i = 0; i < M_SIZE; i++)
            for (int j = 0; j < M_SIZE; j++) ans[i] += vec[j] * m[i][j];
        memcpy(vec, ans, sizeof(ans));
    }
    // 输出矩阵内容
    void print() {
        int width[M_SIZE];
        memset(width, 0, sizeof(width));
        for (int i = 0; i < M_SIZE; i++)
            for (int j = 0; j < M_SIZE; j++) {
                int w = 0;
                if (m[i][j]) w = (int)floor(log10(m[i][j]));
                if (w > width[j]) width[j] = w;
            }
        // width[j] + 2 就是第 j 列的宽度（包括空格）
        for (int i = 0; i < M_SIZE; i++) {
            for (int j = 0; j < M_SIZE; j++) {
                printf("%-*d", width[j] + 2, m[i][j]);
            }
            printf("\n");
        }
    }
    int* operator[](int n) { return m[n]; }
    Matrix<M_SIZE>& operator=(const Matrix<M_SIZE>& M) {
        memcpy(m, M.m, sizeof(m));
        return *this;
    }
    Matrix<M_SIZE> operator*(const Matrix<M_SIZE>& M) {
        Matrix<M_SIZE> ans;
        for (int i = 0; i < M_SIZE; i++)
            for (int j = 0; j < M_SIZE; j++)
                for (int k = 0; k < M_SIZE; k++)
                    ans.m[i][j] += this->m[i][k] * M.m[k][j];
        return ans;
    }
    Matrix<M_SIZE>& operator*=(const Matrix<M_SIZE>& M) {
        *this = (*this) * M;
        return *this;
    }
    Matrix<M_SIZE> operator^(int n) {
        Matrix<M_SIZE> ans = Identity();
        Matrix<M_SIZE> res = *this;
        while (n) {
            if (n & 1) ans *= res;
            res *= res;
            n >>= 1;
        }
        return ans;
    }
    Matrix<M_SIZE>& operator^=(int n) {
        *this = *this ^ n;
        return *this;
    }
};

int main() {
    cout << "Matrix Quick Pow" << endl;
    int m[4][4] = {{1, 1, 1, 1}, {1, 1, 1, 0}, {1, 1, 0, 1}, {1, 0, 1, 1}};
    Matrix<4> E(m);
    E.m[0][1] = 1;
    cout << "E:" << endl;
    E.print();
    cout << "E*E:" << endl;
    (E * E).print();
    cout << "E^5:" << endl;
    (E ^ 5).print();
    // 计算斐波那契数列
    // 递推式（矩阵）：
    // [f(n)  ] = [1 1] * [f(n-1)]
    // [f(n-1)]   [0 1]   [f(n-2)]
    int fibb_m[2][2] = {{1, 1}, {1, 0}};
    Matrix<2> fibb(fibb_m);
    int i;
    cout << endl << "The nth of Fibonacci:";
    cin >> i;
    int vec[2] = {1, 0};
    if (i > 1) fibb ^= i - 1;
    fibb.mul(vec);
    cout << "Result = " << vec[0];
    pause_cin;
}
