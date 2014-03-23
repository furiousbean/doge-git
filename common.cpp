#include "common.h"
#include <cmath>

QString int_to_QString(int val) {
    std::ostringstream stm;
    stm << val;
    return QString::fromStdString(stm.str());
}

QString double_to_QString(double val, int fixed) {
    if (std::isnan(val)) return QString("N/A");
    std::ostringstream stm;
    if (fixed) stm << std::fixed << val; else stm << val;
    return QString::fromStdString(stm.str());
}

QString double_to_QString(double val, int fixed, int length) {
    if (std::isnan(val)) return QString("N/A");
    std::ostringstream stm;
    stm.precision(length);
    if (fixed) stm << std::fixed << val; else stm << val;
    return QString::fromStdString(stm.str());
}

double xabsx(double x) {
    return (x * std::fabs(x));
}
