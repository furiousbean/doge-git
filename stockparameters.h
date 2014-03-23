#ifndef STOCKPARAMETERS_H
#define STOCKPARAMETERS_H

//!Stock Parameters struct
struct StockParameters {
	int length;
	double noise_sd;
	double angle_sd;
	double trend_prob;
	double initial_price;
	double initial_bag;
    int optim_crit;
    StockParameters();
};

#endif //STOCKPARAMETERS_H
