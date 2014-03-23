#include "stockparameters.h"
#include "common.h"
#include "histoconf.h"

HistoConf::HistoConf(StockParameters& sp): sp(&sp) {
    setWindowTitle("Histogram parameters");
    parwidget = new ParamWidget(sp);
    vlayout = new QVBoxLayout;
    vlayout -> addWidget(parwidget);
    buttonbox = new QDialogButtonBox(QDialogButtonBox::Ok
                                     | QDialogButtonBox::Cancel);

    connect(buttonbox, SIGNAL(accepted()), this, SLOT(apply_pars()));
    connect(buttonbox, SIGNAL(rejected()), this, SLOT(reject()));
    samplabel = new QLabel("<b>Sample size</b>:");
    sampbox = new QSpinBox();
    sampbox -> setRange(10, 1000);
    sampbox -> setValue(100);

    vlayout -> addWidget(samplabel);
    vlayout -> addWidget(sampbox);
    vlayout -> addWidget(buttonbox);

    this -> setLayout(vlayout);
    setWindowIcon (QIcon(":/images/histogram.png"));

}

int HistoConf::get_sample_size() const {
    return sampbox -> value();
}

void HistoConf::apply_pars() {
    parwidget -> write_pars();
    accept();
}

HistoConf::~HistoConf() {
    delete sampbox;
    delete samplabel;
    delete buttonbox;
    delete parwidget;
    delete vlayout;
}
