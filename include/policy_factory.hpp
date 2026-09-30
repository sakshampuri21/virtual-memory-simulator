#pragma once
#include <memory>
#include <vector>
#include "replacement_policy.hpp"
#include "types.hpp"

enum class PolicyType { FIFO, LRU, Optimal };

std::unique_ptr<ReplacementPolicy> makePolicy(PolicyType type, std::size_t frames,
                                              const ReferenceString& refs);

const std::vector<PolicyType>& allPolicies();