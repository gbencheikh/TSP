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
#include"Heuristique1.h"
#include"Heuristique2.h"
#include<ctime>

using namespace std;

void afficher_matrice(long **M,int siz)
{
    for(int i=0;i<siz;i++)
    {
        for(int j=0;j<siz;j++)
            if(M[i][j]<M[0][0])
               cout<<M[i][j]<<" ";
            else
                cout<<"inf ";
        cout<<endl;
    }
}

int main(int argc, char * argv[]) {

	fstream toto(argv[1], fstream::in);

    clock_t time=clock();
	TSPData data(toto);


	toto.close();
    afficher_matrice(data.getMatrix(),data.getSize());


    time = clock();
    double time_lecture = (double) time/CLOCKS_PER_SEC;

    Heuristique1 heur;
    heur.set_size(data.getSize());
    heur.set_matrice(data.getMatrix());
    heur.Find_solution();
    heur.afficher_solution();
    time=clock();
    double temps_heuristique1 = (double) time/CLOCKS_PER_SEC - time_lecture;
    cout<<"temps d'execution : "<<temps_heuristique1<<" seconds"<<endl<<endl;

    Heuristique2 heur2;
    heur2.set_size(data.getSize());
    heur2.set_matrice(data.getMatrix());
    heur2.Find_solution();
    long val = heur2.afficher_solution();
    cout<<" de valeur : "<< val << endl;
    time = clock();
    double temps_heuristique2 = (double) time/CLOCKS_PER_SEC - time_lecture - temps_heuristique1;
    cout<<"temps d'execution : "<<temps_heuristique2<<" seconds"<<endl<<endl;

	return 0;
}
