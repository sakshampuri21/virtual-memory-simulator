#pragma once
#include <vector>
#include "replacement_policy.hpp"
#include "types.hpp"

class OptimalPolicy : public ReplacementPolicy {
public:
    OptimalPolicy(std::size_t frames, const ReferenceString& refs);
    std::string name() const override { return "Optimal"; }
    bool access(int page, std::size_t time) override;

private:
    ReferenceString refs_;
    std::vector<int> memory_;
    std::size_t nextUse(int page, std::size_t time) const;
};