#pragma once
#include "types.hpp"

ReferenceString generateRandom(std::size_t length, int pages, unsigned seed = 42);

ReferenceString generateSequential(std::size_t length, int pages);

ReferenceString generateLocality(std::size_t length, int pages, unsigned seed = 42,
                                 int localitySize = 4, std::size_t phaseLength = 50,
                                 double hotProb = 0.9);