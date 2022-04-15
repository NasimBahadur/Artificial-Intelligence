#include<stdio.h>
#include<stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include<vector>
#include <bits/stdc++.h>
using namespace std ;
/* y_pred = w0x0 + w1x1 + w2x2 + w3x3*/
int m;
vector<float>w , y_pred, slop, y, x[100];


void linearRegression(int feature, int m){
    float cal = 0.0 ;
    for(int i = 0 ; i < m ; i++)
    {
            for(int j = 0 ; j <= feature ; j++){
            cal += w[j]*x[j][i] ;
        }
        y_pred.push_back(cal) ;
    }
}

void findSlop(int feature, int m)
{
    for(int i = 0 ; i < m ; i++)
    {
        float temp = 0.0 ;
        for(int j = 0; j <= feature; j++)
        {
            temp += (y_pred[i] - y[i]) * x[j][i] ;
        }
        slop.push_back(temp) ;
    }
}

void findNewW(int feature, int m)
{
     for(int i = 0; i <= feature; i++)  w[i] = w[i] - 0.002*slop[i];

     fstream new_file;
     new_file.open("valuesofW.txt",ios::out);
     for(int i=0; i<=feature; i++)
     {
         new_file<<w[i]<<"   ";
     }
     new_file.close();
}

void prediction(int feature)
{
    float predict, x[100], w[100];
    for(int i = 1; i <= feature; i++)
    {
        cout<< "X" <<i << " " ;
        cin>>x[i];
    }

    fstream newfile;
    newfile.open("valuesofW.txt",ios::in);
    newfile>>w[0];
    predict = w[0];

    for(int i=1; i<=feature; i++)
    {
        if(!newfile) cout<<"Not Found";
        else
        {
            newfile >> w[i];
            predict += w[i]*x[i];
        }
    }
    printf("\ny = %f\n",predict);
}

int main()
{
    fstream newfile;
    m = 0 ;
    int feature ;
    cout<< "Number of feature : " ;
    cin>> feature ;
    newfile.open("dataRegression.txt",ios::in);
    if(newfile.is_open()){
        string str ;
        while(getline(newfile, str)){
        m++ ;
        stringstream check1(str);
        string intermediate;
        int i = 1 ;
        for(int k = 0 ; k < m ; k++)
        x[0].push_back(1) ;

            while(getline(check1, intermediate, ','))
            {
                float val = atof(intermediate.c_str()) ;
                if(i<=feature){

                    x[i].push_back(val) ;
                    i++ ;
                }
                else{
                    y.push_back(val) ;
                }

            }
        }

        newfile.close() ;
    }
    cout<< m << endl ;
    for(int i = 0 ; i <= feature ; i++){
        float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        w.push_back(r) ;
    }
    cout<< "Initial value of W : " ;
    for(int i = 0 ; i <= feature ; i++){
        cout << w[i] << " " ;
    }
    cout<< endl ;
   linearRegression(feature, m) ;
   findSlop(feature, m) ;
   cout<< "Learn value of W : " ;
    for(int i = 0 ; i <= feature ; i++){
        printf("%f ", w[i]) ;
    }
    cout<< endl ;

    findSlop(feature, m);
    findNewW(feature, m);
    prediction(feature);
}
