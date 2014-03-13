#include "seriesgen.h"

SeriesGenerator::SeriesGenerator(StockParameters& sp) : sp(&sp) { }

SeriesData SeriesGenerator::generate() {
	SeriesData sd;
	double angle = RandomGenerator::get_norm() * sp->angle_sd;
	int nextch = RandomGenerator::get_geom(sp->trend_prob) + 1;
	sd.trend.push_back(sp->initial_price);
    for (int i = 1; i < sp->length; i++) {
		sd.trend.push_back(sd.trend[i - 1] + angle);
		nextch--;
		if (!nextch) {
			angle = RandomGenerator::get_norm() * sp->angle_sd;
			nextch = RandomGenerator::get_geom(sp->trend_prob) + 1;
		}
	}
	int null_mode = 0; //bankrupt =(
	double noise_traject = 0;
    for (int i = 0; i < sp->length; i++) {
    	noise_traject += RandomGenerator::get_norm() * sp->noise_sd;
		sd.series.push_back(sd.trend[i] + noise_traject);
		if (sd.series[i] < 0) null_mode = 1;
		if (null_mode) {
			sd.series[i] = 0;
			sd.trend[i] = 0;
		}
	}
	return sd;
}
