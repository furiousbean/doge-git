/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Digia Plc and its Subsidiary(-ies) nor the names
**     of its contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtWidgets>

#include "mainwindow.h"
#include "plotswindow.h"
#include "aboutwindow.h"
#include "histowindow.h"

MainWindow::MainWindow() {
    mdiArea = new QMdiArea;
    mdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    mdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    setCentralWidget(mdiArea);
    connect(mdiArea, SIGNAL(subWindowActivated(QMdiSubWindow*)),
            this, SLOT(updateMenus()));
    windowMapper = new QSignalMapper(this);
    connect(windowMapper, SIGNAL(mapped(QWidget*)),
            this, SLOT(setActiveSubWindow(QWidget*)));
    hpbar = new QProgressBar;
    statusBar() ->addPermanentWidget(hpbar);
    hpbar_hide();

    createActions();
    createMenus();
    createToolBars();
    createStatusBar();
    updateMenus();

    setWindowTitle("Stock Simulator Of Doge");
    setUnifiedTitleAndToolBarOnMac(true);
    setWindowIcon (QIcon(":/images/doge-icon.png"));
    showMaximized();
}

void MainWindow::closeEvent(QCloseEvent *event) {
    mdiArea->closeAllSubWindows();
    if (mdiArea->currentSubWindow()) {
        event->ignore();
    } else {
        event->accept();
    }
}

void MainWindow::newPlot() {
    QMdiSubWindow* child = createPlotChild();
    child->show();
}

void MainWindow::newHistogram() {
    StockParameters sp;
    HistoConf dlg(sp);
    int result = dlg.exec();

    if (result == QDialog::Accepted) {
        HistoWindow* hw = new HistoWindow(sp);

        connect(hw, SIGNAL(hpbar_hide()), this, SLOT(hpbar_hide()));
        connect(hw, SIGNAL(hpbar_show()), this, SLOT(hpbar_show()));
        connect(hw, SIGNAL(hpbar_setMinimum(int)), this,
                SLOT(hpbar_setMinimum(int)));
        connect(hw, SIGNAL(hpbar_setMaximum(int)), this,
                SLOT(hpbar_setMaximum(int)));
        connect(hw, SIGNAL(hpbar_setValue(int)), this, SLOT(hpbar_setValue(int)));

        statusBar()->showMessage(tr("Please wait while histogram is baked..."));
        mdiArea->addSubWindow(hw);
        hw -> make_work(dlg.get_sample_size());
        hw -> show();
        statusBar()->clearMessage();
    }

}

void MainWindow::about() {
    AboutWindow aw;
    aw.exec();
}

void MainWindow::updateMenus() {
    bool hasMdiChild = (activeMdiChild() != 0);

    closeAct->setEnabled(hasMdiChild);
    closeAllAct->setEnabled(hasMdiChild);
    tileAct->setEnabled(hasMdiChild);
    cascadeAct->setEnabled(hasMdiChild);
    nextAct->setEnabled(hasMdiChild);
    previousAct->setEnabled(hasMdiChild);
    separatorAct->setVisible(hasMdiChild);

}

void MainWindow::updateWindowMenu() {
    windowMenu->clear();
    windowMenu->addAction(closeAct);
    windowMenu->addAction(closeAllAct);
    windowMenu->addSeparator();
    windowMenu->addAction(tileAct);
    windowMenu->addAction(cascadeAct);
    windowMenu->addSeparator();
    windowMenu->addAction(nextAct);
    windowMenu->addAction(previousAct);
    windowMenu->addAction(separatorAct);

    QList<QMdiSubWindow *> windows = mdiArea->subWindowList();
    separatorAct->setVisible(!windows.isEmpty());

    for (int i = 0; i < windows.size(); ++i) {
        QMdiSubWindow* child = windows.at(i);

        QAction *action  = windowMenu->addAction(child -> windowTitle());
        action->setCheckable(true);
        action ->setChecked(child == activeMdiChild());
        connect(action, SIGNAL(triggered()), windowMapper, SLOT(map()));
        windowMapper->setMapping(action, windows.at(i));
    }
}

QMdiSubWindow* MainWindow::createPlotChild() {
    PlotsWindow *child = new PlotsWindow;
    mdiArea->addSubWindow(child);

    return child;
}

void MainWindow::createActions()
{
    newPlotAct = new QAction(QIcon(":/images/plot.png"), tr("&New Plot"), this);
    newPlotAct->setShortcuts(QKeySequence::New);
    newPlotAct->setStatusTip(tr("Create a new plot"));
    connect(newPlotAct, SIGNAL(triggered()), this, SLOT(newPlot()));
    newHistogramAct = new QAction(QIcon(":/images/histogram.png"),
                                  tr("&New Histogram"), this);
    QList<QKeySequence> histokey;
    histokey.push_back(QKeySequence(tr("Ctrl+h")));
    newHistogramAct->setShortcuts(histokey);
    newHistogramAct->setStatusTip(tr("Create a new histogram"));
    connect(newHistogramAct, SIGNAL(triggered()), this, SLOT(newHistogram()));

//! [0]
    exitAct = new QAction(tr("E&xit"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    exitAct->setStatusTip(tr("Exit the application"));
    connect(exitAct, SIGNAL(triggered()), qApp, SLOT(closeAllWindows()));
//! [0]

    closeAct = new QAction(tr("Cl&ose"), this);
    closeAct->setStatusTip(tr("Close the active window"));
    connect(closeAct, SIGNAL(triggered()),
            mdiArea, SLOT(closeActiveSubWindow()));

    closeAllAct = new QAction(tr("Close &All"), this);
    closeAllAct->setStatusTip(tr("Close all the windows"));
    connect(closeAllAct, SIGNAL(triggered()),
            mdiArea, SLOT(closeAllSubWindows()));

    tileAct = new QAction(tr("&Tile"), this);
    tileAct->setStatusTip(tr("Tile the windows"));
    connect(tileAct, SIGNAL(triggered()), mdiArea, SLOT(tileSubWindows()));

    cascadeAct = new QAction(tr("&Cascade"), this);
    cascadeAct->setStatusTip(tr("Cascade the windows"));
    connect(cascadeAct, SIGNAL(triggered()), mdiArea, SLOT(cascadeSubWindows()));

    nextAct = new QAction(tr("Ne&xt"), this);
    nextAct->setShortcuts(QKeySequence::NextChild);
    nextAct->setStatusTip(tr("Move the focus to the next window"));
    connect(nextAct, SIGNAL(triggered()),
            mdiArea, SLOT(activateNextSubWindow()));

    previousAct = new QAction(tr("Pre&vious"), this);
    previousAct->setShortcuts(QKeySequence::PreviousChild);
    previousAct->setStatusTip(tr("Move the focus to the previous "
                                 "window"));
    connect(previousAct, SIGNAL(triggered()),
            mdiArea, SLOT(activatePreviousSubWindow()));

    separatorAct = new QAction(this);
    separatorAct->setSeparator(true);

    aboutAct = new QAction(tr("&About"), this);
    aboutAct->setStatusTip(tr("Show the application's About box"));
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

    aboutQtAct = new QAction(tr("About &Qt"), this);
    aboutQtAct->setStatusTip(tr("Show the Qt library's About box"));
    connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
}

void MainWindow::createMenus() {
    actionMenu = menuBar()->addMenu(tr("&Action"));
    actionMenu->addAction(newPlotAct);
    actionMenu->addAction(newHistogramAct);
    actionMenu->addSeparator();
    actionMenu->addAction(exitAct);

    windowMenu = menuBar()->addMenu(tr("&Window"));
    updateWindowMenu();
    connect(windowMenu, SIGNAL(aboutToShow()), this, SLOT(updateWindowMenu()));

    menuBar()->addSeparator();

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAct);
    helpMenu->addAction(aboutQtAct);
}

void MainWindow::createToolBars() {
    fileToolBar = new QToolBar(tr("Action"));
    addToolBar(Qt::LeftToolBarArea, fileToolBar);
    fileToolBar -> addAction(newPlotAct);
    fileToolBar -> addAction(newHistogramAct);

}

void MainWindow::createStatusBar() {
    statusBar()->showMessage(tr("Ready"));
}

QMdiSubWindow* MainWindow::activeMdiChild() {
    if (QMdiSubWindow *activeSubWindow = mdiArea->activeSubWindow())
        return activeSubWindow;
    return 0;
}

void MainWindow::setActiveSubWindow(QWidget *window)
{
    if (!window)
        return;
    mdiArea->setActiveSubWindow(qobject_cast<QMdiSubWindow *>(window));
}

void MainWindow::hpbar_hide() {
    hpbar -> hide();
}

void MainWindow::hpbar_show() {
    hpbar -> show();
}

void MainWindow::hpbar_setMinimum(int value) {
    hpbar -> setMinimum(value);
}

void MainWindow::hpbar_setMaximum(int value) {
    hpbar -> setMaximum(value);
}

void MainWindow::hpbar_setValue(int value) {
    hpbar -> setValue(value);
}
