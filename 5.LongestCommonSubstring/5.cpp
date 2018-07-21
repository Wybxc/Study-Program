#include <string>
#include "../tools/getin.hpp"

using namespace std;

void LCS(const char a[], int an, const char b[], int bn, int &start, int &count) {
    if ((an <= 0) || (bn <= 0)) {
        start = 0;
        count = 0;
        return;
    }
    int len = 0;
    for (int i = 0; i < an; i++)
        for (int j = 0; j < bn; j++)
            if (a[i] == b[j]) {
                if(i && j)
                    if (a[i - 1] == b[j - 1]) continue;
                int l = 1;
                for (int m = i + 1, n = j + 1;
                     (m < an) && (n < bn) && (a[m] == b[n]);m++,n++)
                    l++;
                if (l > len) {
                    len = l;
                    start = i;
                }
            }
    count = len;
}

int main() {
    cout << "Longest Common Substring" << endl;
    string a, b;
    cout << "a = ";
    cin >> a;
    cout << "b = ";
    cin >> b;
    int start, n;
    LCS(a.c_str(), a.length(), b.c_str(), b.length(), start, n);
    cout << a.substr(start, n);
    pause_cin;
}