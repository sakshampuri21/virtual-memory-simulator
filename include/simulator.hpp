#pragma once
#include "replacement_policy.hpp"
#include "types.hpp"

// Runs one policy over a reference string and tracks page faults and hits.
SimResult simulate(ReplacementPolicy& policy, const ReferenceString& refs);