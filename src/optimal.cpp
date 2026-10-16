#include "optimal.hpp"

OptimalPolicy::OptimalPolicy(std::size_t frames, const ReferenceString& refs)
    : ReplacementPolicy(frames), refs_(refs) {}

std::size_t OptimalPolicy::nextUse(int page, std::size_t time) const {
    for (std::size_t i = time + 1; i < refs_.size(); ++i)
        if (refs_[i] == page) return i;
    return refs_.size();
}

bool OptimalPolicy::access(int page, std::size_t time) {
    for (int p : memory_)
        if (p == page) return true;

    if (memory_.size() < capacity_) {
        memory_.push_back(page);
        return false;
    }

    std::size_t victim = 0;
    std::size_t farthest = 0;
    for (std::size_t i = 0; i < memory_.size(); ++i) {
        std::size_t next = nextUse(memory_[i], time);
        if (next > farthest) {
            farthest = next;
            victim = i;
        }
    }
    memory_[victim] = page;
    return false;
}