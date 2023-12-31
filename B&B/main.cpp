//============================================================================
// Name        : TSP.cpp
// Author      : F.C.
// Version     :
// Copyright   : Free for all
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include "TSP.h"
#include"Noeud.h"
#include<stack>
#include<stdio.h>
#include<stdlib.h>

using namespace :: std;

Noeud solution_init(long **M,int n)
{
    Noeud solution(n);
    int val =0;
    for(int i=0;i<n-1;i++)
    {
        couple x;
        x.A = i;
        x.B = i+1;
        val += M[i][i+1];
        solution.ajouter_dans_list(x);
    }
    couple x;
        x.A = n-1;
        x.B = 0;
        val += M[n-1][0];
        solution.ajouter_dans_list(x);
    solution.set_BI(val);

    return solution;
}
int main(int argc, char * argv[]) {

	fstream toto(argv[1], fstream::in);

	TSPData data(toto);
    data.affiche();
    cout<<endl;
    long **Matrice;
    Matrice = data.getMatrix();
    Noeud solution = solution_init(Matrice,data.getSize());
    cout<<"solution initiale : "<<endl;
    solution.affiche_list();
    cout<<"de valeur = "<<solution.get_BI()<<endl;

    cout<<"Procedure de separation et evaluation : "<<endl;
    cout<<"La matrice optenu epres le calcul de la borne inferieure est : "<<endl<<endl;
    long borne_inf = data.borninf();
    cout<<"la borne inf = "<<borne_inf<<endl;
    data.affiche();
    cout<<endl;
	toto.close();

    Noeud elem(data.getSize());
    elem.set_matrix(data.getMatrix());
    elem.set_BI(borne_inf);
    stack<Noeud> arbre;
    arbre.push(elem);

    while (!arbre.empty())
    {
        Noeud temp(data.getSize());

        temp = arbre.top();
        arbre.pop();
        if(temp.feuille()==false && temp.get_BI()<solution.get_BI())
        {
            couple  x = temp.regret();

            long reg = temp.regret_temp(x.A,x.B);
            if(reg < data.getVal(0,0))
            {

                Noeud fils_droit(data.getSize());
                fils_droit.set_matrix(temp.fils_droit(x.A,x.B));
                fils_droit.set_BI(temp.get_BI()+reg);
                fils_droit.set_list(temp.get_list());
                if(fils_droit.get_BI()<solution.get_BI())
                    arbre.push(fils_droit);
            }

            Noeud fils_gauche(data.getSize());
            fils_gauche.set_matrix(temp.fils_gauche(x.A,x.B));
            long borne = fils_gauche.borne_inf();
            if(borne < data.getVal(0,0))
            {
                fils_gauche.set_BI(temp.get_BI()+borne);
                fils_gauche.set_list(temp.get_list());
                fils_gauche.ajouter_dans_list(x);
                arbre.push(fils_gauche);
            }

        }
        else
        {
            if(temp.get_BI()<solution.get_BI())
                solution = temp;

        }
    }
    solution.affiche_list();
    cout<<"Solution :"<<solution.get_BI()<<endl;
    return 0;
}
