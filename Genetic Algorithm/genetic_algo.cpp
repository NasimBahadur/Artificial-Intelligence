#include<bits/stdc++.h>
#include<stdio.h>
#include<cstdlib>
#include<vector>
#include<cmath>

using namespace std;

struct chromosome
{
    int a, b;
    double fitness;
    double prob;
    double cum_prob;
} temp, dvalue[6], newdvalue[6];

int f(int a, int b)
{
    return 2*a*a + 3*b - 38;
}

void Selection()
{
    for(int i=0; i<6; i++)
    {
        // step 2: evaluation
        int f_obj = abs(f(dvalue[i].a, dvalue[i].b));
        // fitness calculation
        dvalue[i].fitness = 1.00/(1.00+f_obj);
        //printf("fitness %d = %f\n", i, dvalue[i].fitness);
    }
    double total = 0;
    for(int i=0; i<6; i++)
    {
        total = total + dvalue[i].fitness;
    }
    //printf("total fitness %f\n", total);
    // calculating the probability for each chromosomes
    for(int i=0; i<6; i++)
    {
        dvalue[i].prob = dvalue[i].fitness / total;
    }

    // computing the cumulative probability values
    double sum = 0;
    for(int i=0; i<6; i++)
    {
        sum = sum + dvalue[i].prob;
        dvalue[i].cum_prob = sum;
    }
    // generating random numbers
    double R[6];
    for(int i=0; i<6; i++)
    {
        R[i] = ((double) rand() / (RAND_MAX));
    }

    // selection of new chromosomes
    for(int i=0; i<6; i++)
    {
        //i number jar range a ase tai cole ashbe
        if(R[i] >= 0 && R[i] <= dvalue[0].cum_prob)
            newdvalue[i] = dvalue[0];
        else if(R[i] > dvalue[0].cum_prob && R[i] <= dvalue[1].cum_prob)
            newdvalue[i] = dvalue[1];
        else if(R[i] > dvalue[1].cum_prob && R[i] <= dvalue[2].cum_prob)
            newdvalue[i] = dvalue[2];
        else if(R[i] > dvalue[2].cum_prob && R[i] <= dvalue[3].cum_prob)
            newdvalue[i] = dvalue[3];
        else if(R[i] > dvalue[3].cum_prob && R[i] <= dvalue[4].cum_prob)
            newdvalue[i] = dvalue[4];
        else if(R[i] > dvalue[4].cum_prob && R[i] <= dvalue[5].cum_prob)
            newdvalue[i] = dvalue[5];
    }

    // new selected chromosomes
    for(int i=0; i<6; i++)
    {
        dvalue[i] = newdvalue[i];
    }
}
void crossOver(int x, int y)
{
    int a[8] = {0}, b[8] = {0}, c[8];
    int p = dvalue[x].a;
    int q = dvalue[x].b;
    int i = 3;
    while(p!=0)
    {
        a[i] = p%2;
        p = p/2;
        i--;
    }

    i = 7;
    while(q!=0)
    {
        a[i] = q%2;
        q = q/2;
        i--;
    }
    p = dvalue[y].a;
    q = dvalue[y].b;
    i = 3;
    while(p!=0)
    {
        b[i] = p%2;
        p = p/2;
        i--;
    }

    i = 7;
    while(q!=0)
    {
        b[i] = q%2;
        q = q/2;
        i--;
    }

    int r = rand() % 8;

    for(int i = 0; i<r; i++)
    {
        c[i] = a[i];
    }

    for(int i = r; i<8; i++)
    {
        c[i] = b[i];
    }

    p = c[0]*8 + c[1]*4 + c[2]*2 + c[3]*1;
    q = c[4]*8 + c[5]*4 + c[6]*2 + c[7]*1;

    dvalue[x].a = p;
    dvalue[x].b = q;
}

void parentSelection()
{
    vector<int> par;
    double rhoc = 0.25;
    for(int i=0; i<6; i++)
    {
        double r = ((double) rand() / (RAND_MAX));
        if(r<rhoc)
        {
            par.push_back(i);
        }
    }

    int i;
    if(par.size() > 1)
    {
        int lim = par.size() - 1;
        for(i=0; i<lim; i++)
        {
            //printf("%d  %d\n", par[i], par[i+1]);
            crossOver(par[i], par[i+1]);
        }
        //printf("%d  %d\n", par[lim], par[0]);
        crossOver(par[lim], par[0]);
    }
}

void mutation()
{
    int total_gene = 8 * 6;
    double rhom = 0.1;
    int no_of_mutation = round(total_gene*rhom);
    vector<int> rn;
    for(int i = 0; i<no_of_mutation;i++)
    {
        int r = rand() % total_gene;
        rn.push_back(r);
    }
    int lim = rn.size();
    for(int j = 0; j< lim; j++)
    {
        int chr = rn[j] / 8;
        int gen = rn[j] % 8;

        int a[8] = {0};
        int p = dvalue[chr].a;
        int q = dvalue[chr].b;

        int i = 3;
        while(p!=0)
        {
            a[i] = p%2;
            p = p/2;
            i--;
        }

        i = 7;
        while(q!=0)
        {
            a[i] = q%2;
            q = q/2;
            i--;
        }

        if(a[gen] == 1)
            a[gen] = 0;
        else
            a[gen] = 1;

        p = a[0]*8 + a[1]*4 + a[2]*2 + a[3]*1;
        q = a[4]*8 + a[5]*4 + a[6]*2 + a[7]*1;

        dvalue[chr].a = p;
        dvalue[chr].b = q;
    }
}

int main()
{
    int i, j;
    // step 1: Initialization
    for(i = 0; i < 6; i++)
    {
        int x = rand() % 10;
        int y = rand() % 10;
        dvalue[i].a = x;
        dvalue[i].b = y;
        dvalue[i].fitness = 0;
    }

    for(i=0; i < 1000 ; i++)
    {
        // Terminating condition
        for(j = 0 ; j < 6 ; j++)
        {
            if(f(dvalue[j].a, dvalue[j].b) == 0)
            {
                printf("Solution %d %d\n", dvalue[j].a, dvalue[j].b);
                return 0;
            }
        }
        printf("\nIteration: %d\n\n", i);
        Selection();
        parentSelection(); // crossover is inside it
        mutation();
        for(j = 0 ; j < 6 ; j++)
        {
            printf("chromosome-%d : %d %d\n",j,dvalue[j].a,dvalue[j].b );
        }
    }
}
