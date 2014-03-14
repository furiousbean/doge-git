#include "basestrategy.h"
#include "twostepstrategy.h"

#include "strategyfactory.h"
#include "cmath"

StrategyFactory::StrategyFactory(StockParameters& sp) : sp(&sp) {

}

Strategy* StrategyFactory::optimize(const dvector& series) {
	int optimal_L = 3;
	double optimal_p = MIN_OPT_PROB;
    double bestincome = -std::numeric_limits<double>::infinity();
    for (int L = 3; L <= std::min(MAX_L, (int)series.size()); L++)
        for (double p = MIN_OPT_PROB; p <= MAX_OPT_PROB; p += OPT_PROB_STEP) { //bad place
            BaseStrategy trystrat(*sp, L, p);
            TransactData result(trystrat.insert_series(series));
			if (result.income.back() > bestincome) {
				optimal_L = L;
				optimal_p = p;
				bestincome = result.income.back();
			}
		}
	{ 
        TwoStepStrategy trystrat(*sp);
        TransactData result(trystrat.insert_series(series));
		if (result.income.back() > bestincome) {
			optimal_L = 2;
			bestincome = result.income.back();
		}
    }
    Strategy* result;
    if (optimal_L > 2) result = new BaseStrategy(*sp, optimal_L, optimal_p); else
      result = new TwoStepStrategy(*sp);
	return result;
}
