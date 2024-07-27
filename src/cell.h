#include <stdint.h>
#include <stdlib.h>

namespace PGC {

enum class CellStatus : uint8_t {
    White,
    Gray,
    Black
};

class Cell {
public:
    Cell();
    ~Cell() = default;
    CellStatus m_cellStatus;
    size_t m_refs;
    Cell* m_ptr1;
    Cell* m_ptr2;
    Cell* m_ptr3;
};

} /* PGC */
