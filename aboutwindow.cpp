#include "aboutwindow.h"

AboutWindow::AboutWindow() {
    setWindowTitle("About Doge =)");
    vlayout = new QVBoxLayout;
    dogeimage = new QLabel;
    dogeimage -> setPixmap(QPixmap(":/images/doge.jpg"));
    vlayout -> addWidget(dogeimage);
    info = new QLabel("The <b>Doge</b> is my Stock Simulator"
       "<br> Nikita Zvonarev, 2014");
    vlayout -> addWidget(info);
    buttonbox = new QDialogButtonBox(QDialogButtonBox::Ok);

    connect(buttonbox, SIGNAL(accepted()), this, SLOT(accept()));

    vlayout -> addWidget(buttonbox);

    this -> setLayout(vlayout);

    layout()->setSizeConstraint( QLayout::SetFixedSize );
    setWindowIcon (QIcon(":/images/doge-icon.png"));
}

AboutWindow::~AboutWindow() {
    delete buttonbox;
    delete info;
    delete dogeimage;
    delete vlayout;
}
