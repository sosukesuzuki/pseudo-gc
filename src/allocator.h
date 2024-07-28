#pragma once

#include "cell.h"

namespace PGC {

class Allocator {

private:
    Cell* m_start;
    Cell* m_free;
    Cell* m_limit;

public:
    Allocator();
    ~Allocator();
    Cell* allocate();
};

} /* PGC */
