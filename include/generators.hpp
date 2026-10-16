#pragma once
#include "types.hpp"

ReferenceString generateRandom(std::size_t length, int pages);
ReferenceString generateSequential(std::size_t length, int pages);
ReferenceString generateLocality(std::size_t length, int pages);