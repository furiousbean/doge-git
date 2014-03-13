#ifndef BASESTRATEGY_H
#define BASESTRATEGY_H

#include "strategy.h"

class BaseStrategy : public Strategy {
private:
	int L;
	double p;
	dvector known_series;
	int test_hyphot();
    int have_prefix_means;
    double sample_mean;
    double sample_var;
public:
	BaseStrategy(StockParameters& sp, int L, double p);
	virtual int buysell_insert(double value);
	virtual TransactData finish_trade();
    int get_L() const;
    double get_p() const;
    virtual ~BaseStrategy();
};

#endif  //STRATEGY_H
