#include "getin.hpp"
#include <iostream>
#include <string>

using namespace std;

namespace wy {

int get_ints(int output[]) {
    cout << "Please input an array:" << endl;
    string input;
    getline(cin, input);
    // 开始分析输入数据
    bool finished = false;
    int k = 0;
    do {
        if (input[0] != '[') break;
        int i = 1, j = 1;
        int st = 0;
        size_t count = input.size();
        while (i < count) {  // 遍历字符串
            char c = input[i];
            if ((c != ']') && (c != ',') && ((c < '0') || ('9' < c))) break;
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
                    output[k++] = atoi(input.substr(j).c_str());  // 获取数字
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
                output[k++] = atoi(input.substr(j).c_str());  // 获取数字
                break;
            }
        }
    } while (false);
    if (!finished) {
        cout << "Bad input!" << endl;
        return 0;
    }
    return k;
}

}  // namespace wy