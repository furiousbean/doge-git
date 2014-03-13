#include "stockparameters.h"
#include "common.h"

StockParameters::StockParameters() : length(SP_LENGTH), noise_sd(SP_NOISE_SD),
                         angle_sd(SP_ANGLE_SD), trend_prob(SP_TREND_PROB),
                         initial_price(SP_INITIAL_PRICE),
                         initial_bag(SP_INITIAL_BAG) { }
