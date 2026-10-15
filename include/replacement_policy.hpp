#pragma once
#include <cstddef>
#include <string>

class ReplacementPolicy {
public:
    explicit ReplacementPolicy(std::size_t frames) : capacity_(frames) {}
    virtual ~ReplacementPolicy() = default;

    virtual std::string name() const = 0;
    virtual bool access(int page, std::size_t time) = 0;

    std::size_t capacity() const { return capacity_; }

protected:
    std::size_t capacity_;
};