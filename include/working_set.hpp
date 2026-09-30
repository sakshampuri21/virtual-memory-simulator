#pragma once
#include <vector>
#include "types.hpp"

struct WorkingSetStats {
    std::size_t window = 0;
    std::vector<std::size_t> sizes;  // |W(t, window)| for every t
    double average = 0.0;
    std::size_t maximum = 0;
};

// Sliding-window working-set model: W(t, w) = distinct pages referenced in
// the last w references. Measures temporal locality of the reference string.
WorkingSetStats analyzeWorkingSet(const ReferenceString& refs, std::size_t window);