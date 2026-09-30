#include "fifo.hpp"

bool FIFOPolicy::access(int page, std::size_t) {
    if (resident_.count(page)) return true;  // hit: FIFO order unchanged

    if (resident_.size() == capacity_) {     // full: evict oldest
        resident_.erase(order_.front());
        order_.pop();
    }
    order_.push(page);
    resident_.insert(page);
    return false;
}