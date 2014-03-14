#include "strategy.h"

Strategy::Strategy(StockParameters& sp) : sp(&sp), buysell_state(0),
                                         share_amount(0), bag(sp.initial_bag) { }

TransactData Strategy::insert_series(const dvector& series) {
	td.income.reserve(series.size());
    //for (uint i = 0; i < series.size(); ++i) buysell_insert(series[i]);
    for (auto it = series.begin(); it != series.end(); ++it) buysell_insert(*it);
	return finish_trade();
}

int Strategy::get_L() const{
    return UINT_UNDEF;
}

double Strategy::get_p() const {
    return NAN;
}

Strategy::~Strategy() { }
