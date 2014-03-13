#include "basestrategy.h"
#include "strategyfactory.h"
#include "cmath"

StrategyFactory::StrategyFactory(StockParameters& sp) : sp(&sp) {

}

Strategy* StrategyFactory::optimize(const dvector& series) {
	int optimal_L = 3;
	double optimal_p = 0;
	double bestincome = -1e-100;
    for (int L = 3; L <= std::min(MAX_L, (int)series.size()); L++)
        for (double p = 0.05; p <= 0.95; p += 0.05) { //bad place
            BaseStrategy trystrat(*sp, L, p);
            TransactData result(trystrat.insert_series(series));
			if (result.income.back() > bestincome) {
				optimal_L = L;
				optimal_p = p;
				bestincome = result.income.back();
			}
		}
    Strategy* result = new BaseStrategy(*sp, optimal_L, optimal_p);
	return result;
}
