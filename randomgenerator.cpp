#include "randomgenerator.h"
#include <cstdlib>
#include <ctime>

std::random_device RandomGenerator::rd;
std::mt19937 * RandomGenerator::gen_eng = 0;

void RandomGenerator::randomize() {
    if (gen_eng != 0) delete gen_eng;
    gen_eng = new std::mt19937(rd.entropy() ? rd() :
                               (unsigned long)(std::time(nullptr)));
    //srand(std::time(nullptr));
}

void RandomGenerator::randomize(int seed) {
    if (gen_eng != 0) delete gen_eng;
    gen_eng = new std::mt19937(seed);
    //srand(seed);
}

double RandomGenerator::get_unif() {
    std::uniform_real_distribution<double> unif_real_01(0.0, 1.0);
    return unif_real_01(*gen_eng);
}

double RandomGenerator::get_norm() {
    std::normal_distribution<double> norm_real_01(0.0, 1.0);
    return norm_real_01(*gen_eng);
}

int RandomGenerator::get_geom(double p) {
    std::geometric_distribution<int> geom_real(p);
    return geom_real(*gen_eng);
}

void RandomGenerator::destroy() {
    if (gen_eng != 0) delete gen_eng;
    //srand(seed);
}
