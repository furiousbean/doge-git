#include "strategy.h"
#include "twostepstrategy.h"
//#include <iostream>

TwoStepStrategy::TwoStepStrategy(StockParameters& sp) : Strategy(sp),
    have_prev(0), prev(0), current_pos(0) { }

int TwoStepStrategy::buysell_insert(double value) {
    //known_series.push_back(value);
	int ans = 0;
	if (!buysell_state) {
        if (have_prev && value > prev && bag >= DEFAULT_TAKE) {
            td.buy_points.push_back(current_pos);
			bag -= DEFAULT_TAKE;
            if (value > 0) share_amount = DEFAULT_TAKE / value;
			buysell_state = 1;
			ans = 1;
		}
	} else {
        if (have_prev && value < prev) {
            td.sell_points.push_back(current_pos);
			bag += value * share_amount;
			share_amount = 0;
			buysell_state = 0;
			ans = -1;
		}
	}
    have_prev = 1;
    prev = value;
    td.income.push_back(bag - sp->initial_bag + value * share_amount);
    current_pos++;
	return ans;
}

TransactData TwoStepStrategy::finish_trade() {
    if (buysell_state) td.sell_points.push_back(current_pos);
	TransactData rettd(td);
	buysell_state = 0;
	share_amount = 0;
    bag = sp->initial_bag;
    td.buy_points.clear();
    td.sell_points.clear();
    td.income.clear();
    prev = 0;
    have_prev = 0;
    current_pos = 0;
	return rettd;
}

int TwoStepStrategy::get_L() const{
    return 2;
}

TwoStepStrategy::~TwoStepStrategy() { }
