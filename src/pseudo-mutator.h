#pragma once

#include "allocator.h"
#include <memory>
#include <random>
#include <vector>

namespace PGC {

class PseudoMutator {
public:
    PseudoMutator(std::shared_ptr<Allocator> allocator, std::shared_ptr<std::vector<Cell*>> roots, std::shared_ptr<std::mt19937> gen);
    void mutate();

private:
    std::shared_ptr<Allocator> m_allocator;
    std::shared_ptr<std::vector<Cell*>> m_roots;
    std::shared_ptr<std::mt19937> m_gen;

    void allocate();
    void removeReferences();
};

} /* PGC */
