#include "financecalculator.h"

double FinanceCalculator::eval_risk (const dvector& income) {
	if (income.size() <= 1) return 0;
	double sum = 0;
    for (uint i = 1; i < income.size() - 1; ++i) {
		double val = income[i] - ((income.back() - income.front()) 
			/ (income.size() - 1) * i);
		sum += val * val;
	}
    return std::sqrt(sum / income.size());
}

QString FinanceCalculator::html_summary(const Strategy &strat,
    const TransactData& td, QString name) {
    QString result = "<b>L</b>: " + int_to_QString(strat.get_L()) + "<br>";
    result += "<b>p</b>: " + double_to_QString(strat.get_p()) + "<br>";
	result += html_summary(td, name);
	return result;
}

QString FinanceCalculator::html_summary(const TransactData& td, QString name) {
	QString result = "<b>" + name + " income</b>: " + 
	    double_to_QString(td.income.back())  + "<br>";
	result += "<b>" + name + " risk</b>: " + 
        double_to_QString(FinanceCalculator::eval_risk(td.income)) + "<br>";
    result += "<b>" + name + " No. of transactions</b>: " +
        int_to_QString(td.buy_points.size() + td.sell_points.size());
	return result;
}

QString FinanceCalculator::parameter_summary(const StockParameters& sp) {
    QString result = "Length: " + int_to_QString(sp.length);
    result += ", noise sd: " + double_to_QString(sp.noise_sd);
    result += ", angle sd: " + double_to_QString(sp.angle_sd);
    result += ", trend mu: " + double_to_QString(1 / sp.trend_prob);
    return result;
}
