#include "basestrategy.h"
#include "twostepstrategy.h"

#include "strategyfactory.h"
#include "financecalculator.h"
#include "cmath"

StrategyFactory::StrategyFactory(StockParameters& sp) : sp(&sp) {

}

double StrategyFactory::eval_score(const dvector &series) const {
    if (sp -> optim_crit) {
        double risk = FinanceCalculator::eval_risk(series);
        if (risk > 0) return series.back() / risk; else return 0;
    } else return series.back();
}

Strategy* StrategyFactory::optimize(const dvector& series) const {
	int optimal_L = 3;
	double optimal_p = MIN_OPT_PROB;
    double bestscore = -std::numeric_limits<double>::infinity();
    for (int L = 3; L <= std::min(MAX_L, (int)series.size()); L++)
        for (double p = MIN_OPT_PROB; p <= MAX_OPT_PROB; p += OPT_PROB_STEP) { //bad place
            BaseStrategy trystrat(*sp, L, p);
            TransactData result(trystrat.insert_series(series));
            double score = eval_score(result.income);
            if (score > bestscore) {
				optimal_L = L;
				optimal_p = p;
                bestscore = score;
			}
		}
	{ 
        TwoStepStrategy trystrat(*sp);
        TransactData result(trystrat.insert_series(series));
        double score = eval_score(result.income);
        if (score > bestscore) {
			optimal_L = 2;
            bestscore = result.income.back();
		}
    }
    Strategy* result;
    if (optimal_L > 2) result = new BaseStrategy(*sp, optimal_L, optimal_p); else
      result = new TwoStepStrategy(*sp);
	return result;
}
