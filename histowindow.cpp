#include "basestrategy.h"
#include "strategy.h"
#include "seriesgen.h"
#include "stockparameters.h"
#include "strategyfactory.h"
#include "common.h"
#include "histowindow.h"
#include "financecalculator.h"
#include <cmath>
#include <algorithm>

const int dimx = 780;
const int dimy = 420;

HistoWindow::HistoWindow(StockParameters& sp) : sp(&sp) {
    setAttribute(Qt::WA_DeleteOnClose);
    baseincplot = new QCustomPlot;
    baseriskplot = new QCustomPlot;
    baseincriskplot = new QCustomPlot;

    testincplot = new QCustomPlot;
    testriskplot = new QCustomPlot;
    testincriskplot = new QCustomPlot;
    center = new QWidget;
    centerlayout = new QGridLayout();
    centerlayout -> addWidget(baseincplot, 0, 0);
    centerlayout -> addWidget(testincplot, 0, 1);
    centerlayout -> addWidget(baseriskplot, 1, 0);
    centerlayout -> addWidget(testriskplot, 1, 1);
    centerlayout -> addWidget(baseincriskplot, 2, 0);
    centerlayout -> addWidget(testincriskplot, 2, 1);
    center -> setLayout(centerlayout);
    setWidget(center);
    sizeHint() = QSize(dimx, dimy);
    setMinimumSize(dimx, dimy);

    resize(QSize(dimx, dimy));
    setWindowIcon (QIcon(":/images/histogram.png"));

}

HistoWindow::~HistoWindow() {
    delete baseincplot;
    delete testincplot;
    delete baseriskplot;
    delete testriskplot;
    delete baseincriskplot;
    delete testincriskplot;
    delete centerlayout;
    delete center;
}

void HistoWindow::make_work(int sample_size) {
    setWindowTitle("Histogram; " + FinanceCalculator::parameter_summary(*sp));
    emit hpbar_show();
    emit hpbar_setMinimum(0);
    emit hpbar_setMaximum(sample_size - 1);
    SeriesGenerator sergen(*sp);
    dvector baseincome;
    dvector testincome;
    dvector baserisk;
    dvector testrisk;
    dvector baseincrisk;
    dvector testincrisk;

    for (int k = 0; k < sample_size; k++) {
        emit hpbar_setValue(k);
        SeriesData basedata = sergen.generate();
        StrategyFactory stratfact(*sp);
        Strategy* goodstrategy = stratfact.optimize(basedata.series);
        SeriesData testdata = sergen.generate();
        TransactData baseresult = goodstrategy -> insert_series(basedata.series);
        TransactData testresult = goodstrategy -> insert_series(testdata.series);
        baseincome.push_back(baseresult.income.back());
        testincome.push_back(testresult.income.back());
        baserisk.push_back(FinanceCalculator::eval_risk(baseresult.income));
        testrisk.push_back(FinanceCalculator::eval_risk(testresult.income));
        if (baserisk.back() != 0) baseincrisk.push_back(
            baseincome.back() / baserisk.back()); else
            baseincrisk.push_back(0);
        if (testrisk.back() != 0) testincrisk.push_back(
            testincome.back() / testrisk.back()); else
            testincrisk.push_back(0);

        delete goodstrategy;       
    }

    InnerHist baseincomeinhist = make_inner_hist(baseincome);
    InnerHist testincomeinhist = make_inner_hist(testincome);
    InnerHist baseriskinhist = make_inner_hist(baserisk);
    InnerHist testriskinhist = make_inner_hist(testrisk);
    InnerHist baseincriskinhist = make_inner_hist(baseincrisk);
    InnerHist testincriskinhist = make_inner_hist(testincrisk);

    init_plot(baseincplot, make_full_title("Base income", baseincome),
              baseincomeinhist);
    init_plot(testincplot, make_full_title("Test income", testincome),
              testincomeinhist);
    init_plot(baseriskplot, make_full_title("Base risk", baserisk),
              baseriskinhist);
    init_plot(testriskplot, make_full_title("Test risk", testrisk),
              testriskinhist);
    init_plot(baseincriskplot, make_full_title("Base income/risk", baseincrisk),
              baseincriskinhist);
    init_plot(testincriskplot, make_full_title("Test income/risk", testincrisk),
              testincriskinhist);

    emit hpbar_hide();
}

InnerHist HistoWindow::make_inner_hist(dvector sample) {
    std::sort(sample.begin(), sample.end());
    int sz = sample.size();
    if (sz == 0) {
        sample.push_back(0);
        sz = 1;
    }
    double xl = sample[sz / 4]; //left quartile
    double xr = sample[3 * sz / 4]; //right quartile
    double center = sample[sz / 2];
    double wdt = xr - xl;
    double l_b = center - wdt * HISTOGRAM_BW_SZ;
    double bwdt = wdt * HISTOGRAM_BW_SZ * 2;
    int bins_cnt = 2 * std::pow(sz, (double)1 / 3); //Rice rule
    InnerHist ans;
    ans.freqs.push_back(0);
    int cur_bin = 0;
    for (int i = 0; i < sz; i++) {
        while (sample[i] > cur_bin * (bwdt / bins_cnt) + l_b &&
               cur_bin <= bins_cnt) {
            ans.freqs.push_back(0);
            cur_bin++;
        }
        ans.freqs[cur_bin]++;
    }
    if (ans.freqs.size() < bins_cnt + 2) {
        int diff = ans.freqs.size() - bins_cnt - 2;
        for (int i = 0; i < diff; ++i) ans.freqs.push_back(0);
    }

    for (int i = 0; i <= bins_cnt; i++) ans.capts.push_back(
                double_to_QString(i * (bwdt / bins_cnt) + l_b, 1, 1));

    return ans;
}


 void HistoWindow::init_plot(QCustomPlot* plot, QString title, InnerHist& ih) {
     plot->plotLayout()->insertRow(0); // inserts an empty row
     QCPPlotTitle* Ptitle = new QCPPlotTitle(plot, title);
     QFont tfont(Ptitle->font());
     tfont.setPointSize(10);
     Ptitle ->setFont(tfont);
     plot->plotLayout()->addElement(0, 0, Ptitle);

     QCPBars *bars = new QCPBars(plot->xAxis, plot->yAxis);

     plot->addPlottable(bars);

     QVector<double> ticks;
     QVector<double> barlegs;

     for (int i = 0; i < ih.capts.size(); i++) {
         barlegs << i;
         ticks << (float)i + 0.5;
     }

     barlegs << ih.capts.size();

     plot->xAxis->setAutoTicks(false);
     plot->xAxis->setAutoTickLabels(false);
     plot->xAxis->setTickVector(ticks);
     plot->xAxis->setTickVectorLabels(ih.capts);

     plot->xAxis->setSubTickCount(0);
     plot->xAxis->setTickLength(0, 4);
     plot->xAxis->grid()->setVisible(true);
     plot->xAxis->setRange(-1, ih.capts.size() + 1);

     int ymax = 0;
     for (int i = 0; i < ih.freqs.size(); i++)
         if (ih.freqs[i] > ymax) ymax = ih.freqs[i];

     // prepare y axis:
     plot->yAxis->setRange(0, ymax + 1);
     plot->yAxis->setPadding(5); // a bit more space to the left border
     plot->yAxis->setLabel("Frequency");
     plot->yAxis->grid()->setSubGridVisible(true);
     QPen gridPen;
     gridPen.setStyle(Qt::SolidLine);
     gridPen.setColor(QColor(0, 0, 0, 25));
     plot->yAxis->grid()->setPen(gridPen);
     gridPen.setStyle(Qt::DotLine);
     plot->yAxis->grid()->setSubGridPen(gridPen);

     // Add data:
     bars -> setData(barlegs, ih.freqs);
     plot->replot();
}

QString HistoWindow::make_full_title(QString title, dvector sample) {
    if (sample.size() == 0) return title;
    double mean = 0;
    for (uint i = 0; i < sample.size(); i++) mean += sample[i];
    mean /= sample.size();
    double sd = 0;
    for (uint i = 0; i < sample.size(); i++) sd += sample[i] * sample[i];
    sd = std::sqrt((sd / sample.size()) - mean * mean);
    return title + ": mean = " + double_to_QString(mean) +
            ", sd = " + double_to_QString(sd);
}
