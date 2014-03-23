#include "cachestdtr.h"
#include "stdtr.h"
#include <iostream>

double CacheStdtr::cache[BIG_DF + 1][BIG_M + 1];

double CacheStdtr::eval(int df, double x) {
	if (df > BIG_DF) df = BIG_DF;
    return cache[df][(int)(x * BIG_M)];
}

void CacheStdtr::make_cache() {
    for (int i = 1; i <= BIG_DF; i++)
      for (double x = MIN_OPT_PROB; x <= MAX_OPT_PROB; x += OPT_PROB_STEP)
          cache[i][(int)(x * BIG_M)] = i < BIG_DF ? stdtr(i, x) : ndtr(x);
}
