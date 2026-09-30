#include "lru.hpp"

bool LRUPolicy::access(int page, std::size_t) {
    auto it = where_.find(page);
    if (it != where_.end()) {                        // hit: move to front
        order_.splice(order_.begin(), order_, it->second);
        return true;
    }

    if (where_.size() == capacity_) {                // full: evict LRU
        where_.erase(order_.back());
        order_.pop_back();
    }
    order_.push_front(page);
    where_[page] = order_.begin();
    return false;
}