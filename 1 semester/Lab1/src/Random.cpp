//
// Created by Win10Pro on 10.09.2020.
//

#include "Random.h"

int Random::rand(int lo, int hi) {

    static std::random_device rd;
    static std::seed_seq seq{rd(), static_cast<unsigned>(time(nullptr))};
    static std::mt19937 mt(seq);

    std::uniform_int_distribution range(lo, hi);

    return range(mt);
}