#ifndef PLOTSWINDOW_H
#define PLOTSWINDOW_H

#include <QtWidgets/QMdiSubWindow>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QMessageBox>
#include "common.h"
#include "qcustomplot.h"
#include "stockparameters.h"
#include "paramwidget.h"

//! Window with plots widget
class PlotsWindow : public QMdiSubWindow {
    Q_OBJECT

    QCustomPlot* upperplot;
    QCustomPlot* bottomplot;
    QWidget* center;
    QWidget* rightpanel;
    QWidget* leftpanel;
    QHBoxLayout* hlayout;
    QVBoxLayout* vlayout;
    QVBoxLayout* plotslayout;
    QPushButton* refreshbutton;
    QLabel* summary;
    ParamWidget* parwidget;

    StockParameters sp;
    
    void init_plot(QCustomPlot* plot, QString title);
    void set_lines(QCustomPlot* plot, dvector& trend, dvector& series,
                   dvector& income, dvector& buy, dvector& sell);
public:
    explicit PlotsWindow();
    ~PlotsWindow();
signals:

public slots:
    void remake();
    void make_work();
};

#endif // PLOTSWINDOW_H
