#ifndef HEURISTIQUE2_H_INCLUDED
#define HEURISTIQUE2_H_INCLUDED
#include<iostream>
#include"TSP.h"

using namespace std;

class Heuristique2
{
private :
    long **Matrix;
    int siz;
    int *succ;
    long val;

public :
    couple *solution;
    void set_size(int n)
    {
        siz = n;
    }
    void set_matrice(long **M)
    {
        Matrix = new long*[siz];
        for(int i=0;i<siz;i++)
            Matrix[i]=new long [siz];

        for(int i= 0;i<siz;i++)
            for(int j=0;j<siz;j++)
                Matrix[i][j]=M[i][j];
    }
    bool non_valide(couple X )
    {
        int depart = X.B;
        for(int i=0;i<siz;i++)
            if(solution[i].A==X.A && solution[i].B==X.B)
                return true;
        if(X.A == X.B)
            return true;
        if(succ[X.A]!=-1)
            return true;
        for(int i=0;i<siz;i++)
            if(succ[i]==X.B)
               return true;
        int iter = 0;
        while (succ[depart] != -1 && iter < siz-2)
        {
            if(succ[depart] == X.A)
                return true;
            depart = succ[depart];
            iter ++;
        }
        return false;
    }
    couple * Find_solution()
    {
        val = 0;
        solution = new couple[siz];
        succ = new int [siz];
        for(int i=0;i<siz;i++)
            succ[i]=-1;

        for(int i=0;i<siz;i++)
        {
            solution[i].A = -1;
            solution[i].B = -1;
        }

        int iter = 0;
        while(iter < siz)
        {
            couple minimum;
            for(int i=0;i<siz;i++)
                for(int j=0;j<siz;j++)
                {
                    couple X;
                    X.A = i;
                    X.B = j;
                    if( non_valide(X)!= true )
                    {
                         minimum.A=i;
                         minimum.B=j;
                    }
                }
            for(int i=0;i<siz;i++)
                for(int j=0;j<siz;j++)
                {
                    couple X;
                    X.A = i;
                    X.B = j;
                    if(Matrix[i][j]<Matrix[minimum.A][minimum.B])
                       if(non_valide(X) != true)
                       {
                          minimum.A = i;
                          minimum.B=j;
                       }
                }
                couple X;
                    X.A = minimum.A;
                    X.B = minimum.B;
            solution[iter].A=minimum.A;
            solution[iter].B=minimum.B;
            succ[minimum.A]=minimum.B;
            val += Matrix[minimum.A][minimum.B];
            iter ++;
        }

    }
    long afficher_solution()
    {
        for(int i=0;i<siz;i++)
            cout <<" (" << solution[i].A << "," << solution[i].B << ")";
        return val;
    }
};

#endif // HEURISTIQUE2_H_INCLUDED
