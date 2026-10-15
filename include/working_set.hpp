#pragma once
#include <vector>
#include "types.hpp"

struct WorkingSetStats {
    std::size_t window = 0;
    std::vector<std::size_t> sizes;
    double average = 0.0;
    std::size_t maximum = 0;
};

WorkingSetStats analyzeWorkingSet(const ReferenceString& refs, std::size_t window);