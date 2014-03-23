#ifndef ABOUTWINDOW_H
#define ABOUTWINDOW_H

#include <QtWidgets/QDialog>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QDialogButtonBox>
#include "common.h"
#include "qcustomplot.h"
#include "stockparameters.h"
#include "paramwidget.h"

//! Histogram configuration window
class AboutWindow : public QDialog {
    Q_OBJECT

    QVBoxLayout* vlayout;
    QLabel* dogeimage;
    QLabel* info;
    QDialogButtonBox* buttonbox;
    
public:
    explicit AboutWindow();
    ~AboutWindow();
signals:

public slots:

};

#endif // ABOUTWINDOW_H
