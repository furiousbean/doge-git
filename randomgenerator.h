#ifndef RUNIF_H
#define RUNIF_H

#include <random>

//! Random value generator
class RandomGenerator{
    static std::random_device rd;
    static std::mt19937 * gen_eng;

public:
    //! Randomizes from ctime()
    static void randomize();
    //! Randomizes from given seed
    static void randomize(int seed);
    //! Returns U[0,1]-distributed value
    static double get_unif();
    //! Returns N(0,1)-distributed value
    static double get_norm();
    //! Returns Geom(p)-distributed value
    static int get_geom(double p);
    //! Destroys C++-11 objects
    static void destroy();
};

#endif //RUNIF_H
