

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


#include <iostream>
#include <QList>
#define EMPTY 99    //input 99 in place of an empty block

using std::cout;
using std::cin;
using std::endl;

int filled;
struct block
{
        int val;
        QList<int> p;
};

void fillLists(block table[][9]);
void calcPossibilities(block table[][9]);
inline void eliminate3x3P(block table[][9],block& item,int row,int col);

void calcValues(block table[][9]);
template <typename T>
QList<T> & operator-= ( QList<T> & first,const QList<T> & other );

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
     fillLists(table);
     //calcPossibilities(table);


     while(filled<81)
     {
       calcPossibilities(table);
       calcValues(table);
       cout<<filled<<endl;
       /*for(int i=0;i<9;i++)            //display possibility list
                for(int j=0;j<9;j++)
         { for (int k = 0; k < table[i][j].p.size(); ++k) {
                         cout<<table[i][j].p[k]<<" ";
                     }
           cout<<endl;
         }
       cout<<"foo";*/
     }

     /*for(int i=0;i<9;i++)            //display possibility list
                for(int j=0;j<9;j++)
         { for (int k = 0; k < table[i][j].p.size(); ++k) {
                         cout<<table[i][j].p[k]<<" ";
                     }
           cout<<endl;
       }*/

     cout<<endl;
     for(int i=0;i<9;i++) {           //display values
         for(int j=0;j<9;j++)
             cout<<table[i][j].val<<"\t";
         cout<<"\n";
     }

     return 0;
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
      for(int i=0;i<9;i++)
          for(int j=0;j<9;j++)
          {
            if(table[i][j].p.isEmpty())       //skip already filled blocks
                continue;
            QList<int> tmp=table[i][j].p;
            if(tmp.size()==1) {
                table[i][j].val=tmp[0];
                table[i][j].p.clear();
                calcPossibilities(table);
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
                ++filled;
                continue;
            }

            }

 }

template <typename T>
QList<T> & operator-= (QList<T> & first,const QList<T> & second )
{
    /*cout<<"first";
    for (int i = 0; i < first.size(); ++i)
        cout<<first[i];
    cout<<"second";
    for (int i = 0; i < second.size(); ++i)
        cout<<second[i];*/
    for (int i = 0; i < second.size(); ++i) {
        if(first.contains(second[i]))
            first.removeOne(second[i]);
    }

    return first;
}





