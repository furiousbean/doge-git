#include "basestrategy.h"
#include "strategy.h"
#include "seriesgen.h"
#include "stockparameters.h"
#include "randomgenerator.h"
#include "strategyfactory.h"
#include "common.h"
#include "plotswindow.h"
#include "financecalculator.h"

const int dimx = 780;
const int dimy = 400;

PlotsWindow::PlotsWindow() {
    setAttribute(Qt::WA_DeleteOnClose);
    upperplot = new QCustomPlot;
    bottomplot = new QCustomPlot;
    center = new QWidget;
    leftpanel = new QWidget;
    rightpanel = new QWidget;
    hlayout = new QHBoxLayout;
    refreshbutton = new QPushButton("Refresh");
    hlayout -> addWidget(leftpanel);
    hlayout -> addWidget(rightpanel);
    center -> setLayout(hlayout);
    rightpanel -> setMaximumWidth(200);
    rightpanel -> setMinimumWidth(200);
    rightpanel -> setMaximumHeight(400);
    summary = new QLabel;
    plotslayout = new QVBoxLayout;
    plotslayout -> addWidget(upperplot);
    plotslayout -> addWidget(bottomplot);

    parwidget = new ParamWidget(sp);
    vlayout = new QVBoxLayout;
    vlayout -> addWidget(summary);
    vlayout -> addWidget(parwidget);
    vlayout -> addWidget(refreshbutton);

    connect(refreshbutton, SIGNAL(clicked()), this, SLOT(remake()));
    rightpanel -> setLayout(vlayout);
    leftpanel -> setLayout(plotslayout);
    setWidget(center);
    setMinimumSize(dimx, dimy);
    sizeHint() = QSize(dimx, dimy);
    resize(QSize(dimx, dimy));
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    init_plot(upperplot, "Base period");
    init_plot(bottomplot, "Test period");
    bottomplot->legend->setVisible(true);
    bottomplot->plotLayout()->addElement(2, 0, bottomplot->legend);
    QSize restrictor;
    restrictor.setHeight(20);
    restrictor.setWidth(10000);

    bottomplot->legend->setMaximumSize(restrictor);
    bottomplot->legend->setBorderPen(QPen(Qt::white));
    make_work();
}

PlotsWindow::~PlotsWindow() {
    delete parwidget;
    delete upperplot;
    delete bottomplot;
    delete vlayout;
    delete plotslayout;
    delete summary;
    delete refreshbutton;
    delete hlayout;
    delete leftpanel;
    delete rightpanel;
    delete center;
}

void PlotsWindow::init_plot(QCustomPlot* plot, QString title) {
    for (int i = 0; i < 5; i++)
      plot->addGraph();

    plot->graph(0)->setPen(QPen(Qt::blue));
    plot->graph(1)->setPen(QPen(Qt::red));
    plot->graph(2)->setPen(QPen(Qt::green));
    plot->graph(3)->setPen(QPen(Qt::darkMagenta));
    plot->graph(4)->setPen(QPen(Qt::darkCyan));
    plot->graph(3)->setLineStyle(QCPGraph::lsNone);
    plot->graph(3)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 5));
    plot->graph(4)->setLineStyle(QCPGraph::lsNone);
    plot->graph(4)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssSquare, 5));
    plot->plotLayout()->insertRow(0);
    plot->plotLayout()->addElement(0, 0, new QCPPlotTitle(plot, title));
    plot->xAxis->setLabel("Time");
    plot->yAxis->setLabel("Price");

    plot->graph(0)->setName("Trend data");
    plot->graph(1)->setName("Stock data");
    plot->graph(2)->setName("Income");
    plot->graph(3)->setName("Buy points");
    plot->graph(4)->setName("Sell points");
}

void PlotsWindow::set_lines(QCustomPlot* plot, dvector& trend, dvector& series,
                            dvector& income, dvector& buy, dvector& sell) {
    for (int i = 0; i < 5; i++)
        plot->graph(i)->clearData();
    double umin = 1e100, umax = -1e100;

    for (uint i = 0; i < series.size(); i++) {
        umin = std::min(trend[i], umin);
        umax = std::max(trend[i], umax);
        plot->graph(0)->addData(i, trend[i]);
    }
    for (uint i = 0; i < series.size(); i++) {
        umin = std::min(series[i], umin);
        umax = std::max(series[i], umax);
        plot->graph(1)->addData(i, series[i]);
    }
    for (uint i = 0; i < series.size(); i++) {
        umin = std::min(income[i], umin);
        umax = std::max(income[i], umax);
        plot->graph(2)->addData(i, income[i]);
    }

    for (uint i = 0; i < buy.size(); i++)
        plot->graph(3)->addData(buy[i], series[buy[i]]);
    for (uint i = 0; i < sell.size(); i++)
        plot->graph(4)->addData(sell[i], series[sell[i]]);


    plot->xAxis->setRange(0, series.size());
    plot->yAxis->setRange(umin - (umax - umin) / BORDER_DIV,
                          umax + (umax - umin) / BORDER_DIV);
    plot->replot();
}

void PlotsWindow::make_work() {
    SeriesGenerator sergen(sp);
    SeriesData basedata = sergen.generate();
    StrategyFactory stratfact(sp);
    Strategy* goodstrategy = stratfact.optimize(basedata.series);
    SeriesData testdata = sergen.generate();
    TransactData baseresult = goodstrategy -> insert_series(basedata.series);
    TransactData testresult = goodstrategy -> insert_series(testdata.series);

    set_lines(upperplot, basedata.trend, basedata.series, baseresult.income,
              baseresult.buy_points, baseresult.sell_points);
    set_lines(bottomplot, testdata.trend, testdata.series, testresult.income,
              testresult.buy_points, testresult.sell_points);
    summary -> setText(FinanceCalculator::html_summary(*goodstrategy, baseresult,
        QString("Base")) + "<br><br>" +
        FinanceCalculator::html_summary(testresult, QString("Test")));
    setWindowTitle("Plot; " + FinanceCalculator::parameter_summary(sp));
    delete goodstrategy;
}

void PlotsWindow::remake() {
    parwidget -> write_pars();
    make_work();
}
