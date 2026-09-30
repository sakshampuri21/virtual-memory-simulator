#pragma once
#include <cstddef>
#include <vector>

using ReferenceString = std::vector<int>;

struct SimResult {
    std::size_t frames = 0;
    std::size_t accesses = 0;
    std::size_t hits = 0;
    std::size_t faults = 0;

    double hitRatio() const  { return accesses ? static_cast<double>(hits) / accesses : 0.0; }
    double faultRate() const { return accesses ? static_cast<double>(faults) / accesses : 0.0; }
};