#include "pseudo-collector.h"
#include "allocator.h"
#include "cell.h"
#include <vector>
#include <stack>
#include <memory>

namespace PGC {

PseudoCollector::PseudoCollector(std::shared_ptr<Allocator> allocator, std::shared_ptr<std::vector<Cell*>> roots)
    : m_allocator(allocator), m_roots(roots) {}

void PseudoCollector::mark()
{
    std::stack<Cell*> stack;

    for (Cell* root : *m_roots) {
        stack.push(root);
    }

    while (!stack.empty()) {
        Cell* top = stack.top();
        stack.pop();

        top->m_cellStatus = CellStatus::Black;

        if (top->m_ptr1 != nullptr)
            stack.push(top->m_ptr1);
        if (top->m_ptr2 != nullptr)
            stack.push(top->m_ptr2);
        if (top->m_ptr3 != nullptr)
            stack.push(top->m_ptr3);
    }
}

void PseudoCollector::sweep()
{}

void PseudoCollector::collect()
{
    mark();
    sweep();
}

} /* PGC */
