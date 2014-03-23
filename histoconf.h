#ifndef HISTOCONF_H
#define HISTOCONF_H

#include <QtWidgets/QDialog>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QLabel>
#include <QSpinBox>
#include <QtWidgets/QDialogButtonBox>
#include <QMessageBox>
#include "common.h"
#include "qcustomplot.h"
#include "stockparameters.h"
#include "paramwidget.h"

//! Histogram configuration window
class HistoConf : public QDialog {
    Q_OBJECT

    QVBoxLayout* vlayout;
    ParamWidget* parwidget;
    QDialogButtonBox* buttonbox;
    StockParameters* sp;
    QLabel* samplabel;
    QSpinBox* sampbox;
public:
    explicit HistoConf(StockParameters& sp);
    int get_sample_size() const;
    ~HistoConf();
signals:

public slots:
    void apply_pars();

};

#endif // HISTOCONF_H
