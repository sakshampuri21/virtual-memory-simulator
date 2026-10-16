#include "generators.hpp"
#include <random>
#include <vector>

const unsigned SEED = 42;

ReferenceString generateRandom(std::size_t length, int pages) {
    std::mt19937 rng(SEED);
    std::uniform_int_distribution<int> pick(0, pages - 1);

    ReferenceString refs(length);
    for (std::size_t i = 0; i < length; ++i)
        refs[i] = pick(rng);
    return refs;
}

ReferenceString generateSequential(std::size_t length, int pages) {
    ReferenceString refs(length);
    for (std::size_t i = 0; i < length; ++i)
        refs[i] = i % pages;
    return refs;
}

ReferenceString generateLocality(std::size_t length, int pages) {
    const int HOT_SIZE = 4;
    const std::size_t PHASE_LENGTH = 50;
    const double HOT_PROB = 0.9;

    std::mt19937 rng(SEED);
    std::uniform_int_distribution<int> anyPage(0, pages - 1);
    std::uniform_real_distribution<double> coin(0.0, 1.0);

    ReferenceString refs;
    std::vector<int> hot;

    for (std::size_t i = 0; i < length; ++i) {
        if (i % PHASE_LENGTH == 0) {
            hot.clear();
            for (int k = 0; k < HOT_SIZE; ++k)
                hot.push_back(anyPage(rng));
        }
        if (coin(rng) < HOT_PROB) {
            std::uniform_int_distribution<std::size_t> pickHot(0, hot.size() - 1);
            refs.push_back(hot[pickHot(rng)]);
        } else {
            refs.push_back(anyPage(rng));
        }
    }
    return refs;
}