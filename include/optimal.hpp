#pragma once
#include <unordered_map>
#include <vector>
#include "replacement_policy.hpp"
#include "types.hpp"

// Belady's OPT: evicts the page whose next use is farthest in the future.
// Needs the whole reference string up front, so it is only a theoretical
// baseline (not implementable in a real OS).
class OptimalPolicy : public ReplacementPolicy {
public:
    OptimalPolicy(std::size_t frames, const ReferenceString& refs);
    std::string name() const override { return "Optimal"; }
    bool access(int page, std::size_t time) override;

private:
    std::vector<std::size_t> nextUse_;                    // nextUse_[i] = next index of refs[i]
    std::unordered_map<int, std::size_t> resident_;       // page -> its next use
};