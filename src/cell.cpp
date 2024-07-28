#include "cell.h"

namespace PGC {

void Cell::writeBarrier(Cell* parent, Cell* oldChild, Cell* newChild)
{
    oldChild->m_refs--;
    newChild->m_refs++;
}

void Cell::writeToPtr1(Cell* parent, Cell* newChild)
{
    auto oldChild = parent->m_ptr1;
    writeBarrier(parent, oldChild, newChild);
    parent->m_ptr1 = newChild;
}

void Cell::writeToPtr2(Cell* parent, Cell* newChild)
{
    auto oldChild = parent->m_ptr2;
    writeBarrier(parent, oldChild, newChild);
    parent->m_ptr2 = newChild;
}

void Cell::writeToPtr3(Cell* parent, Cell* newChild)
{
    auto oldChild = parent->m_ptr3;
    writeBarrier(parent, oldChild, newChild);
    parent->m_ptr3 = newChild;
}

} /* PGC */
