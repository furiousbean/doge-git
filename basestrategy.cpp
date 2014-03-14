#include "strategy.h"
#include "basestrategy.h"
#include "cachestdtr.h"
#include <cmath>
//#include <iostream>

BaseStrategy::BaseStrategy(StockParameters& sp, int L, double p) : Strategy(sp),
    L(L), p(p), have_prefix_means(0), sample_mean(0), sample_var(0){ }

int BaseStrategy::buysell_insert(double value) {
    known_series.push_back(value);
	int ans = 0;
	if (!buysell_state) {
        if (known_series.size() >= (uint)L && test_hyphot() && bag >= DEFAULT_TAKE) {
            td.buy_points.push_back(known_series.size() - 1);
			bag -= DEFAULT_TAKE;
            if (value > 0) share_amount = DEFAULT_TAKE / value;
			buysell_state = 1;
			ans = 1;
		}
	} else {
        if (known_series.size() >= (uint)L && test_hyphot()) {
            td.sell_points.push_back(known_series.size() - 1);
			bag += value * share_amount;
			share_amount = 0;
			buysell_state = 0;
			ans = -1;
		}
	}
    td.income.push_back(bag - sp->initial_bag + value * share_amount);
	return ans;
}

TransactData BaseStrategy::finish_trade() {
    if (buysell_state) td.sell_points.push_back(known_series.size() - 1);
	TransactData rettd(td);
	buysell_state = 0;
	share_amount = 0;
    bag = sp->initial_bag;
    td.buy_points.clear();
    td.sell_points.clear();
    td.income.clear();
    known_series.clear();
    have_prefix_means = 0;
    sample_mean = 0;
    sample_var = 0;
	return rettd;
}

int BaseStrategy::test_hyphot() {
    uint size = known_series.size();
    if (!have_prefix_means) {
        for (uint i = size - L + 1; i < size; ++i) {
            double sample_elem = known_series.at(i) - known_series.at(i - 1);
            sample_mean += sample_elem;
            sample_var += sample_elem * sample_elem;
        }
        have_prefix_means = 1;
    } else {
        double pred = known_series.at(size - L)
                - known_series.at(size - L - 1);
        sample_mean -= pred;
        sample_var -= pred * pred;
        double sample_elem = known_series.back()
                - known_series.at(size - 2);
        sample_mean += sample_elem;
        sample_var += sample_elem * sample_elem;
    }

    double sample_mean_t = sample_mean /(L - 1);
    double sample_var_t = sample_var / (L - 1);
    sample_var_t -= sample_mean_t * sample_mean_t;
    if (sample_var_t <= 0) return 0;
    double rstat = (L - 2) / sample_var_t * xabsx(sample_mean_t);
    return ((buysell_state && rstat < xabsx(CacheStdtr::eval(L - 2, p))) ||
        (!buysell_state && rstat > xabsx(CacheStdtr::eval(L - 2, 1 - p))));

}

int BaseStrategy::get_L() const{
    return L;
}

double BaseStrategy::get_p() const {
    return p;
}

BaseStrategy::~BaseStrategy() { }

TransactData BaseStrategy::insert_series(const dvector& series) {
	known_series.reserve(series.size());
    return Strategy::insert_series(series);
}
