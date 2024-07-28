#include <memory>
#include <vector>
#include "allocator.h"
#include "cell.h"

namespace PGC {

class PseudoCollector {
public:
    PseudoCollector(std::shared_ptr<Allocator> allocator, std::shared_ptr<std::vector<Cell*>> roots);
    void collect();

private:
    std::shared_ptr<Allocator> m_allocator;
    std::shared_ptr<std::vector<Cell*>> m_roots;
    void mark();
    void sweep();
};

} /* PGC */
