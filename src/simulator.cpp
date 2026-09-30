#include "simulator.hpp"

SimResult simulate(ReplacementPolicy& policy, const ReferenceString& refs) {
    SimResult r;
    r.frames = policy.capacity();
    r.accesses = refs.size();
    for (std::size_t t = 0; t < refs.size(); ++t) {
        if (policy.access(refs[t], t)) ++r.hits;
        else ++r.faults;
    }
    return r;
}