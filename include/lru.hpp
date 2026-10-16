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
    std::list<int> order_; // front for most recently used and back for least recently used (c++ builitin doubly linked list)
    std::unordered_map<int, std::list<int>::iterator> where_; // An iterator is like a pointer to one node inside that list. So a variable of this type holds the answer to “which node?”.
};