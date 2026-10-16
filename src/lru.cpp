#include "lru.hpp"

bool LRUPolicy::access(int page, std::size_t) {
    auto it = where_.find(page);
    if (it != where_.end()) {
        order_.splice(order_.begin(), order_, it->second); 
        /*
        order_.begin() is where to put it: the front (top).
        order_ is the list it comes from.
        it->second is the card to move. The map stores page → card position, and second is the position.
        */
        return true;
    }

    if (where_.size() == capacity_) {
        where_.erase(order_.back());
        order_.pop_back();
    }
    order_.push_front(page);
    where_[page] = order_.begin();
    return false;
}