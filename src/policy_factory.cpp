#include "policy_factory.hpp"
#include "fifo.hpp"
#include "lru.hpp"
#include "optimal.hpp"

std::unique_ptr<ReplacementPolicy> makePolicy(const std::string& name,
                                              std::size_t frames,
                                              const ReferenceString& refs) {
    if (name == "FIFO")    return std::make_unique<FIFOPolicy>(frames);
    if (name == "LRU")     return std::make_unique<LRUPolicy>(frames);
    if (name == "Optimal") return std::make_unique<OptimalPolicy>(frames, refs);
    return nullptr;
}