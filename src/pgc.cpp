#include "allocator.h"
#include <iostream>

int main()
{

    PGC::Allocator allocator;

    int i = 0;

    while (true) {
        auto cell = allocator.allocate();
        i++;
        if (cell == nullptr)
            break;
    }

    std::cout << i << std::endl;

    return 0;
}
