#include "../tools/getin.hpp"

using namespace std;
using namespace wy;

int main(int argc, char* argv[]) {
    int output[256];
    int count = get_ints(output);
    cout << '[';
    for (int i = 0; i < count; i++) {
        cout << output[i] << ',';
    }
    cout << output[count - 1]  << ']' << endl;
    pause;
    return 0;
}