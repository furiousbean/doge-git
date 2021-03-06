#ifndef COMMON_H
#define COMMON_H
#include <vector>
#include <list>
#include <QString>
#include <sstream>

typedef std::vector<double> dvector;

typedef unsigned int uint;

const int SP_LENGTH = 150;
const double SP_NOISE_SD = 1;
const double SP_ANGLE_SD = 0.5;
const double SP_TREND_PROB = 0.1;
const double SP_INITIAL_PRICE = 100;
const double SP_INITIAL_BAG = 1000;

const double DEFAULT_TAKE = 100;
const int UINT_UNDEF = -1;
const int BORDER_DIV = 20;
const int MAX_L = 50;

const int BIG_DF = 30;
const int BIG_M = 1000;

const double MIN_OPT_PROB = 0.025;
const double MAX_OPT_PROB = 0.51;
const double OPT_PROB_STEP = 0.025;

const double HISTOGRAM_BW_SZ = 1.0;

QString int_to_QString(int val);

QString double_to_QString(double val, int fixed = 1);
QString double_to_QString(double val, int fixed, int length);


double xabsx(double x);

#endif //COMMON_H
