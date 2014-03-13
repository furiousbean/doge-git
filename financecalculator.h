#ifndef FINANCECALCULATOR_H
#define FINANCECALCULATOR_H

#include "common.h"
#include "stockparameters.h"
#include "strategy.h"
#include <QString>

class FinanceCalculator {
public:
	static double eval_risk(const dvector& income);
    static QString html_summary(const Strategy& strat, const TransactData& td,
		                        QString name);
    static QString html_summary(const TransactData& td, QString name);

};

#endif  //FINANCECALCULATOR_H
