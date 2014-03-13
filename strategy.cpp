#include "strategy.h"

Strategy::Strategy(StockParameters& sp) : sp(&sp), buysell_state(0),
                                         share_amount(0), bag(sp.initial_bag) { }

TransactData Strategy::insert_series(const dvector& series) {
    for (uint i = 0; i < series.size(); ++i) buysell_insert(series[i]);
	return finish_trade();
}

int Strategy::get_L() const{
    return UINT_UNDEF;
}

double Strategy::get_p() const {
    return NAN;
}

Strategy::~Strategy() { }
