#ifndef HISTOWINDOW_H
#define HISTOWINDOW_H

#include <QtWidgets/QMdiSubWindow>
#include <QtWidgets/QGridLayout>
#include "common.h"
#include "qcustomplot.h"
#include "stockparameters.h"

struct InnerHist {
    QVector<double> freqs;
    QVector<QString> capts;
};

//! Histogram window

class HistoWindow : public QMdiSubWindow {
    Q_OBJECT

    QCustomPlot* baseincplot;
    QCustomPlot* baseriskplot;
    QCustomPlot* baseincriskplot;

    QCustomPlot* testincplot;
    QCustomPlot* testriskplot;
    QCustomPlot* testincriskplot;

    QWidget* center;
    QGridLayout* centerlayout;

    StockParameters* sp;
    
    void init_plot(QCustomPlot* plot, QString title, InnerHist& ih);
    InnerHist make_inner_hist(dvector sample);
    QString make_full_title(QString title, dvector sample);
public:
    explicit HistoWindow(StockParameters& sp);
    void make_work(int sample_size);
    ~HistoWindow();
signals:
    void hpbar_hide();
    void hpbar_show();
    void hpbar_setMinimum(int value);
    void hpbar_setMaximum(int value);
    void hpbar_setValue(int value);
};

#endif // HISTOWINDOW_H
