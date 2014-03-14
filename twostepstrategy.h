#ifndef TWOSTEPSTRATEGY_H
#define TWOSTEPSTRATEGY_H

#include "strategy.h"

class TwoStepStrategy : public Strategy {
private:
    int have_prev;
    double prev;
    int current_pos;
public:
	TwoStepStrategy(StockParameters& sp);
	virtual int buysell_insert(double value);
 	virtual TransactData finish_trade();
    //TransactData insert_series(const dvector& series);
    int get_L() const;
    //double get_p() const;
    virtual ~TwoStepStrategy();
};

#endif  //STRATEGY_H
