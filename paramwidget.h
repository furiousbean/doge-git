#ifndef PARAMWIDGET_H
#define PARAMWIDGET_H

#include <QLabel>
#include <QtWidgets/QGridLayout>
#include <QGroupBox>
#include <QComboBox>
#include <QDoubleSpinBox>
#include <QSpinBox>
#include "stockparameters.h"

//! Widget for controlling task's parameters
class ParamWidget : public QGroupBox {
    Q_OBJECT
    StockParameters* sp;
    QGridLayout* layout;
    
    QLabel* lengthlabel;
    QSpinBox* lengthbox;
    QLabel* noiselabel;
    QDoubleSpinBox* noisebox;
    QLabel* angnslabel;
    QDoubleSpinBox* angnsbox;
    QLabel* trendlabel;
    QDoubleSpinBox* trendbox;
    QLabel* inprlabel;
    QDoubleSpinBox* inprbox;
    QLabel* inbaglabel;
    QDoubleSpinBox* inbagbox;
    QLabel* criterialabel;
    QComboBox* criteriabox;

public:
    explicit ParamWidget(StockParameters& sp);
    ~ParamWidget();
public slots:
    //! Scan parameters from sp
    void scan_pars();
    //! Write parameters to sp
    void write_pars();
};

#endif // PARAMWIDGET_H
