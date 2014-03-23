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

    //connect(buttonbox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonbox, SIGNAL(accepted()), this, SLOT(apply_pars()));
    connect(buttonbox, SIGNAL(rejected()), this, SLOT(reject()));
    samplabel = new QLabel("<b>Sample size</b>:");
    sampbox = new QSpinBox();
    sampbox -> setRange(10, 1000);
    sampbox -> setValue(100);

    vlayout -> addWidget(samplabel);
    vlayout -> addWidget(sampbox);
    vlayout -> addWidget(buttonbox);

    //vlayout -> addWidget(refreshbutton);

    //connect(refreshbutton, SIGNAL(clicked()), this, SLOT(remake()));
    this -> setLayout(vlayout);
    //leftpanel -> setLayout(plotslayout);
    //setWidget(center);
    //setMinimumSize(dimx, dimy);
    //sizeHint() = QSize(dimx, dimy);
    //resize(QSize(dimx, dimy));
    //setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    //init_plot(upperplot, "Base period");
    //init_plot(bottomplot, "Test period");
    //bottomplot->legend->setVisible(true);
    //bottomplot->plotLayout()->addElement(2, 0, bottomplot->legend);
    //QSize restrictor;
    //restrictor.setHeight(20);
    //restrictor.setWidth(10000);

    //bottomplot->legend->setMaximumSize(restrictor);
    //bottomplot->legend->setBorderPen(QPen(Qt::white));
    //make_work();
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
