#ifndef STRATEGYFACTORY_H
#define STRATEGYFACTORY_H
#include "strategy.h"
#include "basestrategy.h"

//! Strategy optimizer
class StrategyFactory {
protected:
	StockParameters* sp;
    double eval_score(const dvector& series) const;
public:
	StrategyFactory(StockParameters& sp);
    Strategy* optimize(const dvector& series) const;
};

#endif //STRATEGYFACTORY_H
