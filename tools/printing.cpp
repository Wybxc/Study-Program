#include "printing.hpp"
#include <iostream>

using namespace std;

namespace wy {

void print_arr(int arr[], int a, int b) {
    cout << '[';
    for (int i = a; i < b - 1; i++) {
        cout << arr[i] << ',';
    }
    cout <<arr[b - 1] << ']' << endl;
}

}  // namespace wy