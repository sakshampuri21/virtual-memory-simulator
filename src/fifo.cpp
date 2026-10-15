#include "fifo.hpp"

bool FIFOPolicy::access(int page, std::size_t) {
    if (resident_.count(page)) return true;

    if (resident_.size() == capacity_) {
        resident_.erase(order_.front());
        order_.pop();
    }
    order_.push(page);
    resident_.insert(page);
    return false;
}