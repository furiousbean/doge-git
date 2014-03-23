#ifndef TWOSTEPSTRATEGY_H
#define TWOSTEPSTRATEGY_H

#include "strategy.h"

//! Trivial two-step strategy
class TwoStepStrategy : public Strategy {
private:
    int have_prev;
    double prev;
    int current_pos;
public:
	TwoStepStrategy(StockParameters& sp);
	virtual int buysell_insert(double value);
 	virtual TransactData finish_trade();
    int get_L() const;
    virtual ~TwoStepStrategy();
};

#endif  //STRATEGY_H
