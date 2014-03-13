#ifndef STRATEGY_H
#define STRATEGY_H

#include "common.h"
#include "randomgenerator.h"
#include "stockparameters.h"

struct TransactData {
	dvector buy_points;
	dvector sell_points;
	dvector income;
};

class Strategy {
protected:
	StockParameters* sp;
	int buysell_state; //0 - ready to buy, 1 - ready to sell
	double share_amount;
	double bag;
	TransactData td;
public:
	Strategy(StockParameters& sp);
    virtual int buysell_insert(double value) = 0;
    virtual TransactData finish_trade() = 0;
    TransactData insert_series(const dvector& series);
    virtual int get_L() const;
    virtual double get_p() const;
    virtual ~Strategy();
};

#endif  //STRATEGY_H
