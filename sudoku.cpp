#include "sudoku.h"



//      main.cpp
//
//      Copyright 2009 Abhinandh <abhi@abhinandh.com>
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


int filled,passes,tmp;
bool guessed=false;
bool stuck=false;

void fillLists(block table[][9]);
void calcPossibilities(block table[][9]);
inline void eliminate3x3P(block table[][9],block& item,int row,int col);

void calcValues(block table[][9]);
template <typename T>
        QList<T> & operator-= ( QList<T> & first,const QList<T> & other );

bool sudoku(block table[][9])
{

    filled=0;
    passes=0;
    tmp=0;
    guessed=false;
    fillLists(table);
    calcPossibilities(table);

    int prevfilled;
    while(filled<81 && passes<200)
    {
        calcValues(table);
        if(prevfilled==filled)
            stuck=true;
        prevfilled=filled;
        ++passes;
     }

    //   for(int i=0;i<9;i++)            //display possibility list
    //                for(int j=0;j<9;j++)
    //         { for (int k = 0; k < table[i][j].p.size(); ++k) {
    //                         cout<<table[i][j].p[k]<<" ";
    //                     }
    //           cout<<endl;
    //       }

    //    cout<<filled<<endl;
    //    for(int i=0;i<9;i++) {           //display values
    //        for(int j=0;j<9;j++)
    //            cout<<table[i][j].val<<"\t";
    //        cout<<"\n";
    //    }

    if(filled==81)
        return true;
    else
        return false;
}

void fillLists(block table[][9])
{
    for(int i=0;i<9;i++)             //fill lists with values from 0-9
        for(int j=0;j<9;j++)
        {     if(table[i][j].val!=EMPTY)
        {++filled;continue;}
        for(int k=1;k<=9;k++)
            table[i][j].p+=k;
    }
}


void calcPossibilities(block table[][9])
{

    //eliminate items in same row from possibilities
    for(int i=0;i<9;i++)
        for(int j=0;j<9;j++)
        {
        if(table[i][j].val!=EMPTY)
            continue;
        for(int k=0;k<9;k++)
            if(table[i][j].p.contains(table[i][k].val))
                table[i][j].p.removeOne(table[i][k].val);
    }

    //eliminate items in same column from possibilities
    for(int i=0;i<9;i++)
        for(int j=0;j<9;j++)
        {
        if(table[i][j].val!=EMPTY)
            continue;
        for(int k=0;k<9;k++)
            if(table[i][j].p.contains(table[k][j].val))
                table[i][j].p.removeOne(table[k][j].val);
    }
    //eliminate items in 3x3 square from possibilities
    for(int i=0;i<9;i++)
        for(int j=0;j<9;j++)
        {
        if(table[i][j].val!=EMPTY)
            continue;
        eliminate3x3P(table,table[i][j],i,j);
    }

}

void eliminate3x3P(block table[][9],block& item,int row,int col)
{
    int startRow,startCol;
    startRow=row-row%3;
    startCol=col-col%3;

    for(int i=startRow; i!=startRow+3 ; i++)
        for(int j=startCol;j!=startCol+3;j++)
        {
        if(item.p.contains(table[i][j].val))
            item.p.removeOne(table[i][j].val);
    }
}


void calcValues(block table[][9])
{
    static int tmpFilled,tryrow,trycol; //this code makes a guess if not solved in 10 passes
    static block tmptable[9][9];
    if(stuck && !guessed)
    {   for(int i=0;i<9;i++)
        for(int j=0;j<9;j++)
        {
            if(table[i][j].p.size()==2)
            {
                tryrow=i;trycol=j;
                for(int k=0;k<9;k++)
                    for(int l=0;l<9;l++)
                        tmptable[k][l]=table[k][l];         //save current table state
                table[i][j].val=table[i][j].p[0];
                //cerr<<"guess"<<i<<j<<" "<<table[i][j].val<<" "<<filled<<endl;
                tmp=table[i][j].p[1];


                table[i][j].p.clear();
                calcPossibilities(table);

                tmpFilled=filled;
                filled++;
                guessed=true;stuck=false;
                goto out; //just breaks the two loops
            }
        }
    }
    if(stuck && guessed)     //guess wrong,swap the guess
    {
        for(int k=0;k<9;k++)
            for(int l=0;l<9;l++)           //restore table state
                table[k][l]=tmptable[k][l];
        filled=tmpFilled+1;
        table[tryrow][trycol].val=tmp;
        //cerr<<"wrong guess"<<tryrow<<trycol<<" "<<tmp<<" "<<filled<<endl;
        table[tryrow][trycol].p.clear();
        calcPossibilities(table);
        guessed=false;stuck=false;
        goto out;
    }

    out:                                       //guess code ends
    for(int i=0;i<9;i++)
        for(int j=0;j<9;j++)
        {
        if(table[i][j].p.isEmpty())       //skip already filled blocks
            continue;
        QList<int> tmp=table[i][j].p;   //row check

        if(tmp.size()==1) {
            table[i][j].val=tmp[0];
            table[i][j].p.clear();
            calcPossibilities(table);
            //cerr<<i<<j<<" "<<table[i][j].val<<" "<<filled<<endl;
            ++filled;
            continue;
        }
        for(int k=0;k<9;k++)
        {
            if(k==i)
                continue;
            tmp-=table[k][j].p;
        }
        if(tmp.size()==1) {
            table[i][j].val=tmp[0];
            table[i][j].p.clear();
            calcPossibilities(table);
            //cerr<<i<<j<<" "<<table[i][j].val<<" "<<filled<<endl;
            ++filled;
            continue;
        }
        tmp=table[i][j].p; //col check
        for(int k=0;k<9;k++)
        {
            if(k==j)
                continue;
            tmp-=table[i][k].p;
        }

        if(tmp.size()==1) {
            table[i][j].val=tmp[0];
            table[i][j].p.clear();
            calcPossibilities(table);
            //cerr<<i<<j<<" "<<table[i][j].val<<" "<<filled<<endl;
            ++filled;
            continue;
        }

        tmp=table[i][j].p; //3x3 check check
        int startRow,startCol;
        startRow=i-i%3;
        startCol=j-j%3;

        for(int k=startRow; k!=startRow+3 ; k++)
            for(int l=startCol;l!=startCol+3;l++)
            {
            if(k==i&&l==j)
                continue;
            tmp-=table[k][l].p;

        }
        //        for(int x=0;x<tmp.size();x++)
        //                cout<<tmp[x]<<" ";
        //            cout<<endl;
        if(tmp.size()==1) {
            table[i][j].val=tmp[0];
            table[i][j].p.clear();
            calcPossibilities(table);
            //cerr<<i<<j<<" "<<table[i][j].val<<" "<<filled<<endl;
            ++filled;
            continue;
        }

    }

}

template <typename T>
        QList<T> & operator-= (QList<T> & first,const QList<T> & second )
                              {
    for (int i = 0; i < second.size(); ++i) {
        if(first.contains(second[i]))
            first.removeOne(second[i]);
    }

    return first;
}
