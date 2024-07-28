#include "allocator.h"
#include "cell.h"
#include "pseudo-collector.h"
#include "pseudo-mutator.h"
#include <iostream>
#include <memory>
#include <random>
#include <vector>

int main()
{
    auto allocator = std::make_shared<PGC::Allocator>();
    auto roots = std::make_shared<std::vector<PGC::Cell*>>();
    auto gen = std::make_shared<std::mt19937>(std::random_device {}());

    PGC::PseudoMutator mutator(allocator, roots, gen);
    mutator.mutate();

    PGC::PseudoCollector collector(allocator, roots);
    collector.collect();

    std::cout << 1 << std::endl;

    return 0;
}
