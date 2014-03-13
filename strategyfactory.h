#ifndef STRATEGYFACTORY_H
#define STRATEGYFACTORY_H
#include "strategy.h"
#include "basestrategy.h"

class StrategyFactory {
protected:
	StockParameters* sp;
public:
	StrategyFactory(StockParameters& sp);
    Strategy* optimize(const dvector& series);
};

#endif //STRATEGYFACTORY_H
