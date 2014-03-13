#ifndef SERIESGEN_H
#define SERIESGEN_H

#include "common.h"
#include "randomgenerator.h"
#include "stockparameters.h"

struct SeriesData {
	dvector series;
	dvector trend;
};

class SeriesGenerator {
private:
	StockParameters* sp;
public:
	SeriesGenerator(StockParameters& sp);
	SeriesData generate();
};

#endif  //SERIESGEN_H
