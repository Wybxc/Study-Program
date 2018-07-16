#ifndef getin_header
#define getin_header

#include <iostream>

namespace wy {

int get_ints(int output[]);

#define clear_cin cin.ignore(INT_MAX, '\n')

#define pause_cin      \
    do {           \
        clear_cin; \
        cin.get(); \
    } while (0)
    
}  // namespace wy

#endif