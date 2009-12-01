

//      main.cpp
//
//      Copyright 2009 Unknown <abhi@eeepc>
//
//      This program is free software; you can redistribute it and/or modify
//      it under the terms of the GNU General Public License as published by
//      the Free Software Foundation; either version 2 of the License, or
//      (at your option) any later version.
//
//      This program is distributed in the hope that it will be useful,
//      but WITHOUT ANY WARRANTY; without even the implied warranty of
//      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//      GNU General Public License for more details.
//
//      You should have received a copy of the GNU General Public License
//      along with this program; if not, write to the Free Software
//      Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
//      MA 02110-1301, USA.


#include <iostream>
#include <QList>
#define EMPTY 99

using std::cout;
using std::cin;
using std::endl;

struct block
{
        int val;
        QList<int> p;
};

void calcPossibilities(block table[][9]);
void eliminate3x3P(block& item,int row,int col);

int main(int argc, char** argv)
{
        block table[9][9];
        cout<<"enter the table";
        for(int i=0,j=0;i<9;i++)
        {
                for(j=0;j<9;j++)
                {
                        cout<<i<<" "<<j;
                        cin>>table[i][j].val;
                }
        }

     calcPossibilities(table);

        return 0;
}

void calcPossibilities(block table[][9])
{
        for(int i=0;i<9;i++)             //fill lists with values from 0-9
            for(int j=0;j<9;j++)
            {     if(table[i][j].val==EMPTY)
                            continue;
                for(int k=0;k<=9;k++)
                    table[i][j].p+=k;
            }
        //eliminate items in same row from possibilities
        for(int i=0;i<9;i++)
                for(int j=0;j<9;j++)
                {
                        if(table[i][j].val==EMPTY)
                            continue;
                        for(int k=0;k<9;k++)
                                if(table[i][j].p.contains(table[i][k].val))
                                        table[i][j].p.removeOne(table[i][k].val);
                    }

        //eliminate items in same column from possibilities
        for(int i=0;i<9;i++)
                for(int j=0;j<9;j++)
                 {   if(table[i][j].val==EMPTY)
                            continue;
                    for(int k=0;k<9;k++)
                                if(table[i][j].p.contains(table[k][j].val))
                                        table[i][j].p.removeOne(table[k][j].val);
                }
        //eliminate items in 3x3 square from possibilities
        for(int i=0;i<9;i++)
                for(int j=0;j<9;j++)
            {
             if(table[i][j].val==EMPTY)
                            continue;
             eliminate3x3P(table[i][j],i,j);
         }

}

void eliminate3x3P(block& item,int row,int col)
{
    int startRow,startCol;
    startRow=row-row%3;
    //startCol=;
    cout<<startRow<<startCol<<endl;
}


