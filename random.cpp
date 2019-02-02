
#include "random.h"
#include "random_generator.h"

#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>
#include <vector>

using namespace std;

double PRNG::function1() {

    util::random::xoshiro256_plus gen;

    gen.init_seed(chrono::steady_clock::now().time_since_epoch().count());

    gen.get_core().long_jump();
    unsigned long long int x;
    x = gen.random();
    return (x >> 11) * (1. / (UINT64_C(1) << 53));
}

int PRNG::function2(int n) {

    util::random::xoshiro256_starstar gen;

    gen.init_seed(chrono::steady_clock::now().time_since_epoch().count());


    gen.get_core().long_jump();

    return abs((int) gen.random() % n);
}
