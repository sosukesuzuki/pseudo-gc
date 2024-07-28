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
    if (cell->m_refs == 0) {
        cell->m_cellStatus = CellStatus::White;
        cell->m_ptr1 = nullptr;
        cell->m_ptr2 = nullptr;
        cell->m_ptr3 = nullptr;
        return cell;
    } else
        return allocate();
}

Allocator::Iterator::Iterator(Cell* ptr)
    : m_current(ptr)
{
}

Allocator::Iterator::reference Allocator::Iterator::operator*() const
{
    return *m_current;
}

Allocator::Iterator::pointer Allocator::Iterator::operator->()
{
    return m_current;
}

Allocator::Iterator& Allocator::Iterator::operator++()
{
    ++m_current;
    return *this;
}

Allocator::Iterator Allocator::Iterator::operator++(int)
{
    Iterator tmp = *this;
    ++(*this);
    return tmp;
}

bool operator==(const Allocator::Iterator& a, const Allocator::Iterator& b)
{
    return a.m_current == b.m_current;
}

bool operator!=(const Allocator::Iterator& a, const Allocator::Iterator& b)
{
    return a.m_current != b.m_current;
}

Allocator::Iterator Allocator::begin()
{
    return Iterator(m_start);
}

Allocator::Iterator Allocator::end()
{
    return Iterator(m_free);
}

} /* PGC */
