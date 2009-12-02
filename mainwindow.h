#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "ui_mainwindow.h"
#include <QtGui>
#include "sudoku.h"

char intToChar(int x);

class MainWindow:public QMainWindow
{
    Q_OBJECT

 public:
     MainWindow(QMainWindow *parent=0);
 private:
     Ui_MainWindow ui;
 private slots:
     void solve();
     void clear();
     void about();
 };

#endif // MAINWINDOW_H
