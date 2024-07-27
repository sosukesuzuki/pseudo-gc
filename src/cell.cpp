#include "cell.h"

namespace PGC {

Cell::Cell()
    : m_cellStatus(PGC::CellStatus::White)
    , m_refs(0)
    , m_ptr1(nullptr)
    , m_ptr2(nullptr)
    , m_ptr3(nullptr)
{
}

} /* PGC */
