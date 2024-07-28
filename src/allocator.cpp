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

    auto cell = m_free++;
    cell->m_cellStatus = CellStatus::White;
    cell->m_refs = 0;
    cell->m_ptr1 = nullptr;
    cell->m_ptr2 = nullptr;
    cell->m_ptr3 = nullptr;

    return cell;
}

} /* PGC */
