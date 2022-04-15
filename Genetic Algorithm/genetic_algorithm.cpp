#include<bits/stdc++.h>
using namespace std;

struct chromosome
{
    int a, b;
    double fitness ;
    vector<int>prob ;
}temp, dvalue[6], par[6], decx[6];
int bin[6][8];
int tempx[4];
int total = 0;

//function
int f(int a, int b)
{
    return 2*a*a + 3*b - 38 ;
}

int dec_to_bin(int p, int x, int num)
{
    if(x==0)
    {
        bin[p][num] = 0;
        bin[p][num+1] = 0;
        bin[p][num+2] = 0;
        bin[p][num+3] = 0;
    }else if(x==1)
    {
        bin[p][num] = 0;
        bin[p][num+1] = 0;
        bin[p][num+2] = 0;
        bin[p][num+3] = 1;
    }else if(x==2)
    {
        bin[p][num] = 0;
        bin[p][num+1] = 0;
        bin[p][num+2] = 1;
        bin[p][num+3] = 0;
    }else if(x==3)
    {
        bin[p][num] = 0;
        bin[p][num+1] = 0;
        bin[p][num+2] = 1;
        bin[p][num+3] = 1;
    }else if(x==4)
    {
        bin[p][num] = 0;
        bin[p][num+1] = 1;
        bin[p][num+2] = 0;
        bin[p][num+3] = 0;
    }else if(x==5)
    {
        bin[p][num] = 0;
        bin[p][num+1] = 1;
        bin[p][num+2] = 0;
        bin[p][num+3] = 1;
    }else if(x==6)
    {
        bin[p][num] = 0;
        bin[p][num+1] = 1;
        bin[p][num+2] = 1;
        bin[p][num+3] = 0;
    }else if(x==7)
    {
        bin[p][num] = 0;
        bin[p][num+1] = 1;
        bin[p][num+2] = 1;
        bin[p][num+3] = 1;
    }else if(x==8)
    {
        bin[p][num] = 1;
        bin[p][num+1] = 0;
        bin[p][num+2] = 0;
        bin[p][num+3] = 0;
    }else if(x==9)
    {
        bin[p][num] = 1;
        bin[p][num+1] = 0;
        bin[p][num+2] = 0;
        bin[p][num+3] = 1;
    }
}

void int_to_dec(int i)
{
    total = 0;
    total = (bin[i][0]*1) + (bin[i][1]*2) + (bin[i][2]*4) + (bin[i][3]*8);
    decx[i].a = total;

    total = 0;
    total = (bin[i][4]*1) + (bin[i][5]*2) + (bin[i][6]*4) + (bin[i][7]*8);
    decx[i].b = total;
}

//fitness
void calculateFitness()
{
    for(int i = 0 ; i < 6 ; i++)
    {
        int fVal = abs(f(dvalue[i].a, dvalue[i].b)) ;
        dvalue[i].fitness = 1.00/fVal ;
    }
}


void copyToPar(int x, int y)
{
    par[y].a = dvalue[x].a ;
    par[y].b = dvalue[y].b ;
}

void chooseParent()
{
    for(int i = 0 ; i < 6 ; i++)
    {
        for(int j = 1 ; j < 6 ; j++)
        {
            if(dvalue[i].fitness < dvalue[j].fitness)
            {
                temp = dvalue[i] ;
                dvalue[i] = dvalue[j] ;
                dvalue[j] = temp ;
            }
        }
    }

    for(int i = 0 ; i < 6 ; i++)
    {
        dvalue[i].prob.push_back(i) ;
    }

    dvalue[0].prob.push_back(6) ;
    dvalue[0].prob.push_back(7) ;
    dvalue[1].prob.push_back(8) ;

    int cur = 0 ;
    for(int i = 0 ; i < 6 ; i++)
    {
        int randVal = rand() % 9 ;
        if(randVal == 0 || randVal == 6 || randVal == 7)
        {
         copyToPar(0, i) ;
        }else if(randVal == 1 || randVal == 8)
        {
            copyToPar(1, i) ;
        }else if(randVal == 2)
        {
            copyToPar(2, i) ;
        }else if(randVal == 3)
        {
            copyToPar(3, i) ;
        }else if(randVal == 4)
        {
            copyToPar(4, i) ;
        }else if(randVal == 5)
        {
            copyToPar(5, i) ;
        }
    }
}

void crossOver()
{
    for(int i=0; i<6; i++)
    {
        int x = par[i].a;
        int y = par[i].b;
        dec_to_bin(i, x, 0);
        dec_to_bin(i, y, 4);
    }

    int swap_pos1 = rand()%7;
    int tempo = bin[0][swap_pos1];
    bin[0][swap_pos1] = bin[1][swap_pos1];
    bin[1][swap_pos1] = tempo;

    int swap_pos2 = rand()%7;
    tempo = bin[2][swap_pos1];
    bin[2][swap_pos2] = bin[3][swap_pos2];
    bin[3][swap_pos2] = tempo;

    int swap_pos3 = rand()%7;
    tempo = bin[4][swap_pos3];
    bin[4][swap_pos3] = bin[5][swap_pos3];
    bin[5][swap_pos3] = tempo;
}

void mutation()
{
    int mut = rand() % 7;

    for(int i=0; i<mut; i++)
    {
        int r = rand() % 47;
        int row = floor(r/8);
        int col = r%8;

        int tempx = bin[row][col];

        if(tempx == 0)
        {
            bin[row][col] = 1;
        }else{
            bin[row][col] = 0;
        }
    }

    for(int i=0; i<6; i++)
    {
        int_to_dec(i);
    }

    for(int i=0; i<6; i++)
    {
        dvalue[i].a = decx[i].a;
        dvalue[i].b = decx[i].b;
    }
}


int main()
{
    int i, j ;
    for(i = 0 ; i < 6 ; i++)
    {
        int x = rand() % 10 ;
        int y = rand() % 10 ;
        dvalue[i].a = x ;
        dvalue[i].b = y ;
        dvalue[i].fitness = 0 ;
    }

    for(i = 0 ; i < 400 ; i++)
    {
        printf("Iteration: %d\n", i) ;
        for(j = 0 ; j < 6 ; j++)
        {
        if(f(dvalue[j].a , dvalue[j].b) == 0)
        {
            printf("Solution %d %d\n", dvalue[j].a, dvalue[j].b) ;
            return 0;
        }
    calculateFitness() ;
    chooseParent() ;
    crossOver() ;
    mutation() ;
        }
    }
    return 0;
}
