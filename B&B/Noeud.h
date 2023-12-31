#ifndef NOEUD_H_INCLUDED
#define NOEUD_H_INCLUDED
#include<stack>
#include <cmath>
#include <limits>

struct couple
{
    int A;
    int B;
};
class Noeud
{
private :

    long ** M;
    couple *list;
    long BI;
    int size;
public :
int nom;
    Noeud(int n)
    {
        size = n;
        M=new long*[n];
        for(int i=0 ; i< n ; i++)
            M[i]=new long [n];
        for(int i=0 ; i<n ; i++)
           for(int j=0;j<n;j++)
             M[i][j]=0;
        list = new couple[n];
        for(int i=0;i<n;i++)
        {
            list[i].A = -1;
            list[i].B = -1;
        }
    }
    long** get_matrix(){return M;}
    long get_BI(){return BI;}
    couple* get_list(){return list;}
    void set_matrix(long **mat)
    {
        for(int i=0 ; i<size ; i++)
          for(int j=0 ; j<size ;j++)
           M[i][j]=mat[i][j];
    }

    void set_BI(long b){BI=b;}
    void set_list(couple *c)
    {
        for(int i=0;i<size;i++)
        {
            list[i].A = c[i].A;
            list[i].B=c[i].B;
        }
    }
    void affiche_list()
    {
        for(int i=0;i<size;i++)
          if(list[i].A!=-1)
            cout << "( " << list[i].A << "," <<list[i].B << " )";
        cout<<endl;
    }
    void ajouter_dans_list( couple x)
    {
        for(int i=0;i<size;i++)
           if(list[i].A==-1)
           {
               list[i].A=x.A;
               list[i].B=x.B;
               break;
           }
    }
    long borne_inf()
    {
        int  minl,mingl=0, minc , mingc=0 , lb=0 ;
	    for(int i=0 ; i<size ; i++)
	     {
	         minl=M[i][0];
	         for(int j =0 ; j <size ; j++)
	             {
	                 if(minl>M[i][j])
	                 minl=M[i][j];
	             }
	             for(int j=0; j<size ; j++)
	             if(i!=j)
	             M[i][j]-=minl;
	             mingl+=minl;
	     }

	     for(int i=0 ; i<size ; i++ )
	       {
	           minc=M[0][i];
	           for(int j=0 ; j<size ; j++)
	           {
	               if(minc>M[j][i])
	               minc=M[j][i];
	           }
	           mingc+=minc;
	       }
         if(mingc != M[0][0] && mingl != M[0][0])
	        return mingc+mingl;
	     return M[0][0];
    }
    bool existe(int l,int c)
    {
        for(int i=0;i<size;i++)
            if(list[i].A!=-1)
                if(list[i].A == l && list[i].B==c)
                    return true;
        return false;
    }
    long regret_temp(int l,int c)
    {
        int min1,min2;
        min1=0;
        min2=0;
        for(int i=0;i<size;i++)
            if(i!=c && M[l][i]<=M[l][min1])
            {
                 min1 = i;
            }

        for(int i=0;i<size;i++)
            if(i!=l && M[i][c]<=M[min2][c])
            {
                 min2 = c;
            }
        if(M[l][min1]==M[0][0] || M[min2][c]==M[0][0])
            return M[0][0];

        return M[l][min1]+M[min2][c];
    }
    couple regret()
    {
        int t=0;
        int l,c;
        long regret;
        for(int i=0;i<size;i++)
            {
                for(int j=0;j<size;j++)
                   if(M[i][j]==0 && existe(i,j)==false)
                   {
                       regret = regret_temp(i,j);
                       l = i;
                       c = j;
                       t=1;
                       break;
                   }
                 if(t==1)
                    break;
            }
        for(int i=0;i<size;i++)
        {
            for(int j=0;j<size;j++)
            {
                if(M[i][j]==0 && regret < regret_temp(i,j) && existe(i,j)==false)
                {
                    regret = regret_temp(i,j);
                    l= i;
                    c = j;
                }
            }
        }
        couple x;
        x.A=l;
        x.B=c;
        return x;
    }
    long ** fils_gauche(int l,int c)
    {
        long **Matrix;
        Matrix = new long*[size];
        for(int i=0;i<size;i++)
           Matrix[i] = new long [size];
        for(int i=0;i<size;i++)
           for(int j=0;j<size;j++)
               Matrix[i][j]=M[i][j];

        for(int i=0;i<size ; i++)
        {
            if(i!=c)
            Matrix[l][i]=M[0][0];
        }

        for(int i=0 ; i<size ; i++)
        {
            if(i!=l)
            Matrix[i][c]=Matrix[0][0];

        }
        Matrix[c][l]=M[0][0];
        return Matrix;
    }
    long ** fils_droit(int l,int c)
    {
        long **Matrix;
        Matrix = new long*[size];
        for(int i=0;i<size;i++)
           Matrix[i] = new long [size];
        for(int i=0;i<size;i++)
           for(int j=0;j<size;j++)
               Matrix[i][j]=M[i][j];
        Matrix[l][c]=M[0][0];
        return Matrix;
    }
    bool feuille()
    {
        int k=0;
        for(int i=0;i<size;i++)
            if(list[i].A!=-1)
               k++;
        return(k==size);
    }
    void affiche()
    {
        for(int i=0;i<size;i++)
        {

            for(int j=0 ; j<size ; j++)
	             {

	                 if(M[i][j]==M[0][0])
	                 cout<<"inf"<<" ";
	                 else
	                 cout<<M[i][j]<<" ";

	             }
	             cout<<endl;
        }
    }
};
#endif // NOEUD_H_INCLUDED
