#ifndef CACHESTDTR_H
#define CACHESTDTR_H
#include "stdtr.h"
#include "common.h"
#include <unordered_map>

//! Cache for Student Distribution Quantiles
class CacheStdtr {
public:
    static double cache[BIG_DF + 1][BIG_M + 1];
    static double eval(int df, double x);
    static void make_cache();
};

#endif //CACHESTDTR_H
