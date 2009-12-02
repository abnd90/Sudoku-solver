#include "mainwindow.h"

MainWindow::MainWindow(QMainWindow *parent):QMainWindow(parent)
{
    ui.setupUi(this);
    QObject::connect(ui.solve,SIGNAL(clicked()),this,SLOT(solve()));
    QObject::connect(ui.clear,SIGNAL(clicked()),this,SLOT(clear()));
    QObject::connect(ui.action_About,SIGNAL(triggered()),this,SLOT(about()));
    ui.tableWidget->clearContents();
    ui.tableWidget->setRowCount(9);
    ui.tableWidget->setColumnCount(9);
    QString color="#cccccc";
    for(int i=0;i<9;i++)
    {   for(int j=0;j<9;j++)
        {

            QLineEdit* tmp=new QLineEdit;
            tmp->setValidator(new QRegExpValidator(QRegExp("[1-9]"),this));
            tmp->setStyleSheet("background-color: "+color+";font: bold 16px;" );
            ui.tableWidget->setCellWidget(i,j,tmp);

            if(j==2||j==5)
            {    if(color=="#ffffff")
                color="#cccccc";
                else
                    color="#ffffff";
            }
        }
        if(i==2||i==5)
        {    if(color=="#ffffff")
            color="#cccccc";
            else
                color="#ffffff";
        }
    }

}

void MainWindow::solve()
{
    block table[9][9];
    for(int i=0;i<9;i++)
        for(int j=0;j<9;j++)
        {
               QLineEdit *cell=static_cast<QLineEdit *>(ui.tableWidget->cellWidget(i,j));
               if(cell->text().isEmpty())
               {
                   table[i][j].val=EMPTY;
                   cell->setStyleSheet(cell->styleSheet()+"color: red;");
               }
               else
                   table[i][j].val=cell->text().toInt();
           }

    if(!sudoku(table))
    {
        QMessageBox *mb=new QMessageBox(QMessageBox::Critical,"Oops!","Sorry, wrong input"
                       " or the given puzzle is too difficult for me!",QMessageBox::Ok,this);
        mb->show();
    }
    else
    {
        for(int i=0;i<9;i++)
        for(int j=0;j<9;j++)
        {
             QLineEdit *cell=static_cast<QLineEdit *>(ui.tableWidget->cellWidget(i,j));
             QChar chr=intToChar(table[i][j].val);
             cell->setText(QString(chr));
         }
    }
}

char intToChar(int x)
{
    return ('0'+x);
}

void MainWindow::clear()
{
    QString color="#cccccc";
    for(int i=0;i<9;i++)
    {  for(int j=0;j<9;j++)
        {     QLineEdit *cell=static_cast<QLineEdit *>(ui.tableWidget->cellWidget(i,j));
            cell->setText("");
            cell->setStyleSheet("background-color: "+color+";font: bold 16px;" );
            if(j==2||j==5)
            {    if(color=="#ffffff")
                color="#cccccc";
                else
                    color="#ffffff";
            }
        }
        if(i==2||i==5)
        {    if(color=="#ffffff")
            color="#cccccc";
            else
                color="#ffffff";
        }
    }
}

void MainWindow::about()
{
    QMessageBox::about(this,"About Sudoku solver",
                       "<h2>Sudoku solver v1</h2>"
                       "<p>A Qt4 application which"
                       " solves sudoku puzzles."
                       "<p>Copyright Abhinandh, http://abhinandh.com"
                       "<p>Licensed under GPL V3");
}




