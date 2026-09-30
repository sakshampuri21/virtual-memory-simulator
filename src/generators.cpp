#include "generators.hpp"
#include <random>
#include <vector>

ReferenceString generateRandom(std::size_t length, int pages, unsigned seed) {
    std::mt19937 rng(seed);
    std::uniform_int_distribution<int> pick(0, pages - 1);
    ReferenceString refs(length);
    for (auto& p : refs) p = pick(rng);
    return refs;
}

ReferenceString generateSequential(std::size_t length, int pages) {
    ReferenceString refs(length);
    for (std::size_t i = 0; i < length; ++i) refs[i] = static_cast<int>(i % pages);
    return refs;
}

ReferenceString generateLocality(std::size_t length, int pages, unsigned seed,
                                 int localitySize, std::size_t phaseLength, double hotProb) {
    std::mt19937 rng(seed);
    std::uniform_int_distribution<int> anyPage(0, pages - 1);
    std::uniform_real_distribution<double> coin(0.0, 1.0);

    ReferenceString refs;
    refs.reserve(length);
    std::vector<int> hot;

    for (std::size_t i = 0; i < length; ++i) {
        if (i % phaseLength == 0) {                       // new phase, new hot set
            hot.clear();
            for (int k = 0; k < localitySize; ++k) hot.push_back(anyPage(rng));
        }
        if (coin(rng) < hotProb) {
            std::uniform_int_distribution<std::size_t> h(0, hot.size() - 1);
            refs.push_back(hot[h(rng)]);
        } else {
            refs.push_back(anyPage(rng));
        }
    }
    return refs;
}