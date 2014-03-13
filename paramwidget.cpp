#include "paramwidget.h"
#include "common.h"
#include <cmath>

ParamWidget::ParamWidget(StockParameters& sp) : QGroupBox("Parameters"), sp(&sp) {
    layout = new QGridLayout;
    this -> setLayout(layout);
    
    lengthlabel = new QLabel("<b>Length</b>:");
    noiselabel = new QLabel("<b>Noise &sigma;</b>:");
    angnslabel = new QLabel("<b>Trend angle &sigma;</b>:");
    trendlabel = new QLabel("<b>Trend &mu;</b>:");
    inprlabel = new QLabel("<b>Initial price</b>:");
    inbaglabel = new QLabel("<b>Initial bag</b>:");

    lengthbox = new QSpinBox;
    lengthbox -> setRange(1, 1000);
    noisebox = new QDoubleSpinBox;
    noisebox -> setRange(0, 20);
    noisebox -> setSingleStep(0.1);
    angnsbox = new QDoubleSpinBox;
    angnsbox -> setRange(0, 20);
    angnsbox -> setSingleStep(0.1);
    trendbox = new QDoubleSpinBox;
    trendbox -> setRange(1.1, 100);
    trendbox -> setSingleStep(0.2);
    inprbox = new QDoubleSpinBox;
    inprbox -> setRange(0, 10000);
    inprbox -> setSingleStep(10);
    inbagbox = new QDoubleSpinBox;
    inbagbox -> setRange(0, 10000);
    inbagbox -> setSingleStep(10);

    layout -> addWidget(lengthlabel, 0, 0);
    layout -> addWidget(noiselabel, 1, 0);
    layout -> addWidget(angnslabel, 2, 0);
    layout -> addWidget(trendlabel, 3, 0);
    layout -> addWidget(inprlabel, 4, 0);
    layout -> addWidget(inbaglabel, 5, 0);

    layout -> addWidget(lengthbox, 0, 1);
    layout -> addWidget(noisebox, 1, 1);
    layout -> addWidget(angnsbox, 2, 1);
    layout -> addWidget(trendbox, 3, 1);
    layout -> addWidget(inprbox, 4, 1);
    layout -> addWidget(inbagbox, 5, 1);

    scan_pars();

}

ParamWidget::~ParamWidget() {
    //oh my gawd
    delete inbagbox;
    delete inbaglabel;
    delete inprbox;
    delete inprlabel;
    delete trendbox;
    delete trendlabel;
    delete angnsbox;
    delete angnslabel;
    delete noisebox;
    delete noiselabel;
    delete lengthbox;
    delete lengthlabel;
    
    delete layout;
}

void ParamWidget::scan_pars() {
    lengthbox -> setValue(sp -> length);
    noisebox -> setValue(sp -> noise_sd);
    angnsbox -> setValue(sp -> angle_sd);
    trendbox -> setValue(1 / (sp -> trend_prob));
    inprbox -> setValue(sp -> initial_price);
    inbagbox -> setValue(sp -> initial_bag);
}

void ParamWidget::write_pars() {
    sp -> length = lengthbox -> value();
    sp -> noise_sd = noisebox -> value();
    sp -> angle_sd = angnsbox -> value();
    sp -> trend_prob = 1 / (trendbox -> value());
    sp -> initial_price = inprbox -> value();
    sp -> initial_bag = inbagbox -> value();
}
