#include "working_set.hpp"
#include <algorithm>
#include <unordered_map>

WorkingSetStats analyzeWorkingSet(const ReferenceString& refs, std::size_t window) {
    WorkingSetStats s;
    s.window = window;
    s.sizes.reserve(refs.size());

    std::unordered_map<int, std::size_t> count;  // page -> occurrences in window
    double total = 0.0;

    for (std::size_t i = 0; i < refs.size(); ++i) {
        ++count[refs[i]];                                     // slide in
        if (i >= window) {                                    // slide out
            auto it = count.find(refs[i - window]);
            if (--(it->second) == 0) count.erase(it);
        }
        std::size_t wss = count.size();
        s.sizes.push_back(wss);
        s.maximum = std::max(s.maximum, wss);
        total += static_cast<double>(wss);
    }
    s.average = refs.empty() ? 0.0 : total / refs.size();
    return s;
}