#pragma once
#include <queue>
#include <unordered_set>
#include "replacement_policy.hpp"

class FIFOPolicy : public ReplacementPolicy {
public:
    using ReplacementPolicy::ReplacementPolicy;
    std::string name() const override { return "FIFO"; }
    bool access(int page, std::size_t time) override;

private:
    std::queue<int> order_;               // arrival order
    std::unordered_set<int> resident_;    // pages currently in frames
};