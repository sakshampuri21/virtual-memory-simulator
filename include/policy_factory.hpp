#pragma once
#include <memory>
#include <string>
#include "replacement_policy.hpp"
#include "types.hpp"

std::unique_ptr<ReplacementPolicy> makePolicy(const std::string& name,
                                              std::size_t frames,
                                              const ReferenceString& refs);