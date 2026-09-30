#include "optimal.hpp"
#include <limits>

OptimalPolicy::OptimalPolicy(std::size_t frames, const ReferenceString& refs)
    : ReplacementPolicy(frames), nextUse_(refs.size()) {
    const std::size_t NEVER = std::numeric_limits<std::size_t>::max();
    std::unordered_map<int, std::size_t> seen;
    for (std::size_t i = refs.size(); i-- > 0;) {        // backward pass
        auto it = seen.find(refs[i]);
        nextUse_[i] = (it == seen.end()) ? NEVER : it->second;
        seen[refs[i]] = i;
    }
}

bool OptimalPolicy::access(int page, std::size_t time) {
    auto it = resident_.find(page);
    if (it != resident_.end()) {                          // hit
        it->second = nextUse_[time];
        return true;
    }

    if (resident_.size() == capacity_) {                  // full: evict farthest next use
        auto victim = resident_.begin();
        for (auto cur = resident_.begin(); cur != resident_.end(); ++cur)
            if (cur->second > victim->second) victim = cur;
        resident_.erase(victim);
    }
    resident_[page] = nextUse_[time];
    return false;
}