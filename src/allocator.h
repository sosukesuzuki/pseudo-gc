#pragma once

#include "cell.h"
#include <iterator>

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

    class Iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = Cell;
        using difference_type = std::ptrdiff_t;
        using pointer = Cell*;
        using reference = Cell&;

        Iterator(Cell* ptr);
        reference operator*() const;
        pointer operator->();
        Iterator& operator++();
        Iterator operator++(int);
        friend bool operator==(const Iterator& a, const Iterator& b);
        friend bool operator!=(const Iterator& a, const Iterator& b);

    private:
        Cell* m_current;
    };

    Iterator begin();
    Iterator end();
};

} /* PGC */
