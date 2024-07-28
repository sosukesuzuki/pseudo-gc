#include "pseudo-mutator.h"
#include "cell.h"
#include <random>
#include <stack>
#include <vector>

namespace PGC {

PseudoMutator::PseudoMutator(std::shared_ptr<Allocator> allocator, std::shared_ptr<std::vector<Cell*>> roots, std::shared_ptr<std::mt19937> gen)
    : m_allocator(allocator)
    , m_roots(roots)
    , m_gen(gen)
{
}

void PseudoMutator::mutate()
{
    allocate();
    removeReferences();
}

void PseudoMutator::allocate()
{
    constexpr auto numOfRoots = 3;
    constexpr auto numOfCells = 1024;

    std::uniform_int_distribution<> rootDist(0, numOfRoots - 1);
    std::uniform_int_distribution<> fieldDist(0, 2);

    for (size_t i = 0; i < numOfRoots; ++i) {
        Cell* root = m_allocator->allocate();
        root->m_refs++;
        m_roots->push_back(root);
    }

    std::vector<Cell*> cells;
    for (Cell* root : *m_roots) {
        cells.push_back(root);
    }

    for (size_t i = numOfRoots; i < numOfCells; ++i) {
        Cell* cell = m_allocator->allocate();
        Cell* parent = cells[rootDist(*m_gen)];
        switch (fieldDist(*m_gen)) {
        case 0:
            Cell::writeToPtr1(parent, cell);
            break;
        case 1:
            Cell::writeToPtr2(parent, cell);
            break;
        case 2:
            Cell::writeToPtr3(parent, cell);
            break;
        }
        cells.push_back(cell);
    }
}

void PseudoMutator::removeReferences()
{
    constexpr auto removeProbability = 0.8;

    std::uniform_int_distribution<> probDist(0.0, 1.0);
    std::stack<Cell*> stack;

    for (Cell* root : *m_roots) {
        stack.push(root);
    }

    while (!stack.empty()) {
        Cell* cell = stack.top();
        stack.pop();

        if (cell->m_ptr1 != nullptr && probDist(*m_gen) < removeProbability) {
            stack.push(cell->m_ptr1);
            Cell::writeToPtr1(cell, nullptr);
        } else if (cell->m_ptr1 != nullptr) {
            stack.push(cell->m_ptr1);
        }

        if (cell->m_ptr2 != nullptr && probDist(*m_gen) < removeProbability) {
            stack.push(cell->m_ptr2);
            Cell::writeToPtr2(cell, nullptr);
        } else if (cell->m_ptr2 != nullptr) {
            stack.push(cell->m_ptr2);
        }

        if (cell->m_ptr3 != nullptr && probDist(*m_gen) < removeProbability) {
            stack.push(cell->m_ptr3);
            Cell::writeToPtr3(cell, nullptr);
        } else if (cell->m_ptr3 != nullptr) {
            stack.push(cell->m_ptr3);
        }
    }
}

} /* PGC */
