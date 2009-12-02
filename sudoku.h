#ifndef SUDOKU_H
#define SUDOKU_H

#include <QList>
#define EMPTY 99    //input 99 in place of an empty block

struct block
{
    int val;
    QList<int> p;
};
bool sudoku(block table[][9]);

#endif // SUDOKU_H
