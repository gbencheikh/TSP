#ifndef HEURISTIQUE1_H_INCLUDED
#define HEURISTIQUE1_H_INCLUDED

#include<iostream>
#include"TSP.h"

using namespace std;
struct couple
{
    int A;
    int B;
};
class Heuristique1
{
private :
    long **Matrix;
    int siz;
    couple *solution;
    long val;
    bool *visite;
public :
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
    couple * Find_solution()
    {
        val = 0;
        visite = new bool[siz];
        solution = new couple[siz];
        for(int i=0;i<siz;i++)
        {
            visite[i]=false;
            solution[i].A = -1;
            solution[i].B = -1;
        }

        int iter = 0;
        int depart = 0;
        visite[depart] = true;
        while(iter < siz-1)
        {
            int minimum;
            for(int i=0;i<siz;i++)
                if(visite[i]==false)
                {
                    minimum = i;
                    break;
                }

            for(int i=0;i<siz;i++)
            {
                if(Matrix[depart][i]<Matrix[depart][minimum] && visite[i] == false)
                    minimum = i;
            }
            solution[iter].A=depart;
            solution[iter].B=minimum;
            val += Matrix[depart][minimum];
            visite[minimum]= true;
            depart = minimum;
            iter++;
        }
        solution[iter].A = solution[iter-1].B;
        solution[iter].B = solution[0].A;
        val += Matrix[solution[iter].A][solution[iter].B];
    }
    void afficher_solution()
    {
        for(int i=0;i<siz;i++)
            cout <<" (" << solution[i].A << "," << solution[i].B << ")";
        cout<< " de valeur : " <<val << endl;
    }
};


#endif // HEURISTIQUE1_H_INCLUDED
