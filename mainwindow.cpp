#include "mainwindow.h"

MainWindow::MainWindow()
{
    ui.setupUi(this);
    QObject::connect(ui.solve,SIGNAL(clicked()),this,SLOT(solve()));
}
