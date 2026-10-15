#pragma once
#include <unordered_map>
#include <vector>
#include "replacement_policy.hpp"
#include "types.hpp"

class OptimalPolicy : public ReplacementPolicy {
public:
    OptimalPolicy(std::size_t frames, const ReferenceString& refs);
    std::string name() const override { return "Optimal"; }
    bool access(int page, std::size_t time) override;

private:
    std::vector<std::size_t> nextUse_;
    std::unordered_map<int, std::size_t> resident_;
};