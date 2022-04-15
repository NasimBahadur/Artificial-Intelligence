#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<vector>
#include<iostream>
#include<fstream>
using namespace std;

vector<string>avalue;
vector<string>cvalue;

float numberofobject = 0.0;

struct data{
    string x;
    float y;
}prob[100];

//Misc
int findPrior(string cl)
{
    FILE *fptr;
    char c[100] ;
    int count = 0 ;
    if ((fptr = fopen("data.txt", "r")) == NULL) {
        printf("Error! opening file");
        exit(1);
    }
        while (fscanf(fptr, "%s", c)!= EOF)
        {
        string s2 = "" ;

         for(int i = 0 ; i < strlen(c) ; i++){
            s2 += c[i] ;
         }
         if(s2 == cl) count++ ;
    }
    fclose(fptr);
    return count ;
}

int findOccurance(string att, string cl)
{
    FILE *fptr;
    char a[100], c[100] ;
    int count = 0 ;
    if ((fptr = fopen("data.txt", "r")) == NULL) {
        printf("Error! opening file");
        exit(1);
    }
    while (fscanf(fptr, "%s %s", a, c)!= EOF){
        string s = "" ;
        string s2 = "" ;

        for(int i = 0 ; i < strlen(a) ; i++){
            s += a[i] ;
         }
         for(int i = 0 ; i < strlen(c) ; i++){
            s2 += c[i] ;
         }
         if(s == att && s2 == cl) count++ ;
    }
    fclose(fptr);
    return count ;
}

//Training part
void train()
{
    printf("Total number of Object = %d\n\n", (int)numberofobject) ;

    cout<<"Attributes: "<<endl;
    for(int i = 0 ; i < avalue.size() ; i++){

        cout<< avalue[i] << endl ;
    }
    cout<<endl;

    cout<<"Class: "<<endl;
    for(int i = 0 ; i < cvalue.size() ; i++){

        cout<< cvalue[i] << endl ;
    }
    cout<<endl;

    //Prior calculation
    cout<<"Priors:"<<endl;
    ofstream outdata;
    outdata.open("prior.txt");
    if(!outdata)
    {
        cout<<"File not found"<<endl;
        exit(1);
    }
    for(int i = 0 ; i < cvalue.size() ; i++)
    {

        float occ = findPrior(cvalue[i]);
        cout<<cvalue[i]<<" = "<<occ/numberofobject<< endl ;
        outdata<<cvalue[i]<<" "<<occ/numberofobject<<endl;
    }
    outdata.close();
    cout<<endl;

    //Likelyhood calculation
    cout<<"Likelyhood:"<<endl;
    ofstream outdata2;
    outdata2.open("likelyhood.txt");
    if(!outdata)
    {
        cout<<"File not found"<<endl;
        exit(1);
    }

    for(int i = 0 ; i < cvalue.size() ; i++)
    {
        for(int j = 0 ; j < avalue.size() ; j++)
        {
            float n = findOccurance(avalue[j], cvalue[i]) ;
            float p = findPrior(cvalue[i]);
            cout << avalue[j] << "|" << cvalue[i] << " = "<< n/p << endl ;
            outdata2<< avalue[j] << " " << cvalue[i] << " "<< n/p << endl ;
        }
    }
    outdata2.close();
}

//Testing Part
void test()
{
    string att;
    cout<<"Enter desired attribute: "<<endl;
    cin>>att;

    cout<<endl;
    cout<<"Matched attributes & their likelyhood, prior & probability: "<<endl;

    string a, b, d;
    float c, e;
    int counter=0;
    ifstream indata, indata2;
    indata.open("likelyhood.txt");

    indata>>a>>b>>c;
    while(!indata.eof())
    {
        if(a==att)
        {
            indata2.open("prior.txt");
            indata2>>d>>e;
            while(!indata2.eof())
            {
                if(b==d)
                {
                    cout<<"Matched attributes: ";
                    cout<<a<<" "<<b<<endl;
                    cout<<"Probability = "<<c<<"*"<<e<<endl;
                    cout<<"So, Probability = "<<c*e<<endl<<endl;
                    prob[counter].x = b;
                    prob[counter].y = c*e;
                    counter++;
                }
                indata2>>d>>e;
            }
            indata2.close();
        }
        indata>>a>>b>>c;
    }
    indata.close();

    string best;
    float prb = 0.0;
    for(int i=0; i<counter; i++)
    {
        if(prob[i].y>prb)
        {
            best = prob[i].x;
            prb = prob[i].y;
        }
    }

    cout<<"The best selection is "<<best<<" with probability of "<<prb<<"."<<endl<<endl;
}

//Body part
int main()
{
    //File to vector
    char a[100], c[100];
    FILE *fptr;
    if ((fptr = fopen("data.txt", "r")) == NULL) {
        printf("Error! opening file");
        exit(1);
    }

    string s = "" ;
    while(fscanf(fptr, "%s %s", a, c)!= EOF)
        {
         numberofobject++ ;

         bool flag = false ;
         string s = "" ;
         for(int i = 0 ; i < strlen(a) ; i++){
            s += a[i] ;
         }
         for(int i = 0 ; i < avalue.size() ; i++){
            if(s == avalue[i]) {
                flag = true ;
            }
         }
         if(!flag)
            avalue.push_back(s) ;


         flag = false ;
         s = "" ;
         for(int i = 0 ; i < strlen(c) ; i++){
            s += c[i] ;
         }
         for(int i = 0 ; i < cvalue.size() ; i++){
            if(s == cvalue[i]) {
                flag = true ;
            }
         }
         if(!flag)
            cvalue.push_back(s);
    }
    fclose(fptr);
    //done

    while(1)
    {
    int sel,ftr;
    cout<<"Select any option:"<<endl;
    cout<<"Option 1. Train"<<endl;
    cout<<"Option 2. Test"<<endl<<endl;
    cout<<"Enter selection:"<<endl;
    cin>>sel;
    if(sel==1)
    {
        train();
    }else if(sel==2)
    {
        test();
    }
    }
    return 0;
}

