#include "policy_factory.hpp"
#include "fifo.hpp"
#include "lru.hpp"
#include "optimal.hpp"

std::unique_ptr<ReplacementPolicy> makePolicy(PolicyType type, std::size_t frames,
                                              const ReferenceString& refs) {
    switch (type) {
        case PolicyType::FIFO:    return std::make_unique<FIFOPolicy>(frames);
        case PolicyType::LRU:     return std::make_unique<LRUPolicy>(frames);
        case PolicyType::Optimal: return std::make_unique<OptimalPolicy>(frames, refs);
    }
    return nullptr;
}

const std::vector<PolicyType>& allPolicies() {
    static const std::vector<PolicyType> v = {PolicyType::FIFO, PolicyType::LRU, PolicyType::Optimal};
    return v;
}