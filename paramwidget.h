#ifndef PARAMWIDGET_H
#define PARAMWIDGET_H

//#include <QMainWindow>
#include <QLabel>
//#include <QSlider>
//#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QGridLayout>
//#include <QPushButton>
#include <QGroupBox>
//#include <QRadioButton>
#include <QComboBox>
#include <QDoubleSpinBox>
#include <QSpinBox>
//#include <QMessageBox>
#include "stockparameters.h"

//! Constructs & performs settings change using GUI
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

    //QGroupBox* advancedbox;
    //QVBoxLayout* advancedlayout;
    
    //QMessageBox* errorbox;

public:
    explicit ParamWidget(StockParameters& sp);
    ~ParamWidget();
//signals:
    //! Sends reset signal to SearchWidget
//    void make_reset();
public slots:
    //! Scan parameters from sp
    void scan_pars();
    //! Write parameters to sp
    void write_pars();
};

#endif // PARAMWIDGET_H
