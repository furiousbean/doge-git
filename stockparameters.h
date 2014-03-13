#ifndef STOCKPARAMETERS_H
#define STOCKPARAMETERS_H

struct StockParameters {
	int length;
	double noise_sd;
	double angle_sd;
	double trend_prob;
	double initial_price;
	double initial_bag;
    StockParameters();
};

#endif //STOCKPARAMETERS_H
