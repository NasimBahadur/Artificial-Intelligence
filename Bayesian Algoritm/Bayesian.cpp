#include<bits/stdc++.h>
using namespace std;

vector<string>avalue,cvalue;
int object=0;

struct data
{
    string s;
    float p;
} probability[100];

int Prior(string Class)
{
    FILE *fp;
    char c[100] ;
    int cnt=0 ;
    if((fp=fopen("data.txt","r"))==NULL)
    {
        cout<<"Error in opening file";
        exit(1);
    }
    while(fscanf(fp,"%s",c)!= EOF)
    {
        string s2="";
        for(int i=0;i<strlen(c);i++) s2+=c[i];
        if(s2 == Class) cnt++ ;
    }
    fclose(fp);
    return cnt ;
}

int Occurance(string attribute, string Class)
{
    FILE *fp;
    char a[100], c[100];
    int cnt=0 ;
    if ((fp=fopen("data.txt","r"))==NULL)
    {
        printf("Error in opening file");
        exit(1);
    }
    while(fscanf(fp,"%s %s",a,c)!=EOF)
    {
        string s1="", s2="";
        for(int i=0;i<strlen(a);i++) s1+=a[i] ;
        for(int i=0;i<strlen(c);i++) s2+=c[i] ;
        if(s1==attribute && s2==Class) cnt++ ;
    }
    fclose(fp);
    return cnt ;
}

void train()
{
    printf("Total number of Object = %d\n", object) ;
    cout<<"\nAttributes: "<<endl;
    for(int i=0;i<avalue.size();i++) cout<<avalue[i]<<endl ;
    cout<<"\nClass: "<<endl;
    for(int i=0;i<cvalue.size();i++) cout<<cvalue[i]<<endl ;
    cout<<"\nPriors:"<<endl;

    ofstream outdata1;
    outdata1.open("prior.txt");
    if(!outdata1)
    {
        cout<<"File not found"<<endl;
        exit(1);
    }
    for(int i=0; i<cvalue.size(); i++)
    {
        float occur=Prior(cvalue[i]);
        cout<<cvalue[i]<<" = "<<occur/object<< endl ;
        outdata1<<cvalue[i]<<" "<<occur/object<<endl;
    }
    outdata1.close();

    cout<<"\nLikelyhood:"<<endl;
    ofstream outdata2;
    outdata2.open("likelyhood.txt");
    if(!outdata1)
    {
        cout<<"File not found"<<endl;
        exit(1);
    }
    for(int i=0; i<cvalue.size(); i++)
    {
        for(int j=0; j<avalue.size(); j++)
        {
            float n=Occurance(avalue[j],cvalue[i]), p=Prior(cvalue[i]);
            cout << "P(" << avalue[j] << " | " << cvalue[i] << ") = "<< n/p <<endl;
            outdata2<< avalue[j] << " " << cvalue[i] << " "<< n/p << endl ;
        }
    }
    outdata2.close();
}

void test()
{
    string attribute;
    cout<<"Enter desired attribute: "<<endl;
    cin>>attribute;
    string a, b, d;
    float c, e;
    int counter=0;
    ifstream indata1, indata2;
    indata1.open("likelyhood.txt");
    indata1>>a>>b>>c;
    while(!indata1.eof())
    {
        if(a==attribute)
        {
            indata2.open("prior.txt");
            indata2>>d>>e;
            while(!indata2.eof())
            {
                if(b==d)
                {
                    cout<<"Matched attributes: "<<a<<" "<<b<<endl;
                    cout<<"Probability = "<<c*e<<endl;
                    probability[counter].s = b;
                    probability[counter].p = c*e;
                    counter++;
                }
                indata2>>d>>e;
            }
            indata2.close();
        }
        indata1>>a>>b>>c;
    }
    indata1.close();

    string best;
    float prb = 0.0;
    for(int i=0; i<counter; i++)
    {
        if(probability[i].p>prb)
        {
            best = probability[i].s;
            prb = probability[i].p;
        }
    }
    cout<<"The best selection is "<<best<<" with probability of "<<prb<<endl;
}

int main()
{
    char ar[100], cr[100];
    FILE *fp;
    if((fp=fopen("data.txt","r"))==NULL)
    {
        printf("Error! opening file");
        exit(1);
    }
    string s;
    while(fscanf(fp,"%s %s",ar,cr)!= EOF)
    {
        object++ ;
        bool flag = false ;
        s="";
        for(int i=0; i<strlen(ar); i++) s+=ar[i];
        for(int i=0; i<avalue.size(); i++) if(s==avalue[i]) flag=true;
        if(!flag) avalue.push_back(s) ;
        flag = false ;
        s="";
        for(int i=0; i<strlen(cr); i++) s+=cr[i] ;
        for(int i=0; i<cvalue.size(); i++) if(s==cvalue[i]) flag=true ;
        if(!flag) cvalue.push_back(s);
    }
    fclose(fp);

    while(1)
    {
        int choice;
        cout<<"\nSelect any option:"<<endl;
        cout<<"Enter 1: For Train"<<endl;
        cout<<"Enter 2: For Test"<<endl<<endl;
        cout<<"Enter selection:"<<endl;
        cin>>choice;
        switch(choice)
        {
            case 1:train();break;
            case 2:test();break;
            default:exit(0);
        }
    }
    return 0;
}

