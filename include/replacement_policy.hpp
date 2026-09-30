#pragma once
#include <cstddef>
#include <string>

// Common interface for every page-replacement algorithm.
class ReplacementPolicy {
public:
    explicit ReplacementPolicy(std::size_t frames) : capacity_(frames) {}
    virtual ~ReplacementPolicy() = default;

    virtual std::string name() const = 0;

    // Access `page` at position `time` in the reference string.
    // Returns true on a hit, false on a page fault.
    virtual bool access(int page, std::size_t time) = 0;

    std::size_t capacity() const { return capacity_; }

protected:
    std::size_t capacity_;
};