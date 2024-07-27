#include "allocator.h"
#include <cstdlib>
#include <new>

namespace PGC {

Allocator::Allocator()
{
    constexpr auto numOfCells = 1024;
    constexpr auto sizeOfCell = sizeof(Cell);
    m_start = (Cell*)std::calloc(numOfCells, sizeOfCell);
    if (m_start == nullptr)
        throw std::bad_alloc();
    m_free = m_start;
    m_limit = m_start + numOfCells;
}

Allocator::~Allocator()
{
    std::free(m_start);
}

Cell* Allocator::allocate()
{
    if (m_free >= m_limit)
        return nullptr;
    return m_free++;
}

} /* PGC */
