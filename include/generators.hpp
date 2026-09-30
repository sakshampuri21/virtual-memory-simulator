#pragma once
#include "types.hpp"

// Random: uniform over [0, pages).
ReferenceString generateRandom(std::size_t length, int pages, unsigned seed = 42);

// Sequential: 0,1,2,...,pages-1 repeating (looping scan).
ReferenceString generateSequential(std::size_t length, int pages);

// Locality-heavy: program moves through phases; in each phase most accesses
// (`hotProb`) hit a small hot set of `localitySize` pages.
ReferenceString generateLocality(std::size_t length, int pages, unsigned seed = 42,
                                 int localitySize = 4, std::size_t phaseLength = 50,
                                 double hotProb = 0.9);