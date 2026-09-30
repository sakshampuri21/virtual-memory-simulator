#pragma once
#include <list>
#include <unordered_map>
#include "replacement_policy.hpp"

class LRUPolicy : public ReplacementPolicy {
public:
    using ReplacementPolicy::ReplacementPolicy;
    std::string name() const override { return "LRU"; }
    bool access(int page, std::size_t time) override;

private:
    std::list<int> order_;  // front = most recently used, back = least
    std::unordered_map<int, std::list<int>::iterator> where_;
};