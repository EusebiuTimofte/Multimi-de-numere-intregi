#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
using namespace std;

class multime
{
    int* m;
    int nr_el;
public:
    multime(){nr_el=0 ;}
    multime(int nr){this->nr_el=nr;m=new int[nr_el];for(int i=0;i<nr_el;i++)cin>>m[i];}
    multime(const multime& mt)
    {
        nr_el=mt.nr_el;
        m=new int[nr_el];
        for(int i=0;i<nr_el;i++)
            m[i]=mt.m[i];
    }
    multime& operator=(const multime &);//operator de atribuire
    void transformare();//Transforma vectorul in multime
    void scoate_unice();//Elimina elementele care nu se repeta din vector
    friend istream& operator>>(istream& , multime&);
    friend ifstream& operator>>(ifstream& , multime&);
    friend ostream& operator<<(ostream& , multime&);
    friend multime operator+(multime , multime );//reuniune
    friend multime operator*(multime , multime);//intersectie
    friend multime operator-(multime , multime);//scadere
    friend class multime_perechi_nr_intregi;
    int get_el(int nr){return m[nr];}
    int get_nr_el(){return nr_el;}
    ~multime(){delete[] m;}
};

class pereche_nr_intregi
{
    int st,dr;
public:
    pereche_nr_intregi(int s=0,int d=0){st=s;dr=d;}
    pereche_nr_intregi(const pereche_nr_intregi& p){this->st=p.st;this->dr=p.dr;}
    pereche_nr_intregi& operator=(const pereche_nr_intregi&);
    friend istream& operator>>(istream& , pereche_nr_intregi&);
    friend ifstream& operator>>(ifstream& , pereche_nr_intregi&);
    friend ostream& operator<<(ostream& , pereche_nr_intregi&);
    friend class multime_perechi_nr_intregi;
    friend bool operator==(pereche_nr_intregi , pereche_nr_intregi);
    friend bool operator!=(pereche_nr_intregi , pereche_nr_intregi);
    friend bool operator<(pereche_nr_intregi , pereche_nr_intregi);
    int get_st(){return st;}
    int get_dr(){return dr;}
    void set_st(int x){st=x;}
    void set_dr(int x){dr=x;}
};

class multime_perechi_nr_intregi
{
    int nrp;//numar perechi
    pereche_nr_intregi* mpni;//multime perechi de numere intregi
public:
    multime_perechi_nr_intregi& operator=(const multime_perechi_nr_intregi&);
    multime_perechi_nr_intregi(const multime_perechi_nr_intregi& mt)
    {
        this->nrp=mt.nrp;
        this->mpni=new pereche_nr_intregi[this->nrp];
        for(int i=0;i<this->nrp;i++)
            this->mpni[i]=mt.mpni[i];
    }
    multime_perechi_nr_intregi(int nr=0){nrp=nr;mpni=new pereche_nr_intregi[nrp];for(int i=0;i<nrp;i++)cin>>mpni[i];}
    friend istream& operator>>(istream& , multime_perechi_nr_intregi&);
    friend ifstream& operator>>(ifstream&, multime_perechi_nr_intregi&);
    friend ostream& operator<<(ostream& , multime_perechi_nr_intregi&);
    friend multime_perechi_nr_intregi produs_cartezian(multime M1,multime M2);
    int get_nrp(){return nrp;}
    pereche_nr_intregi* get_mpni(){return mpni;}
    ~multime_perechi_nr_intregi(){delete[] mpni;}
};


template <class myclass>
int GetMin (const void* , const void* );

//int cmp_mtp(const void*,const void*);
multime_perechi_nr_intregi produs_cartezian(multime  , multime );

int main()
{

    /*multime M1,M2;
    cin>>M1>>M2;
    cout<<"M1:"<<M1<<"M2:"<<M2;
    multime ID;
    ID=(M1-M2);
    cout<<"diferenta:  "<<ID;
    multime IR=M1+M2;
    cout<<"reuniunea:  "<<IR;
    multime II=M1*M2;
    cout<<"intersectia:  "<<II;

    multime_perechi_nr_intregi M,MP;
    M = produs_cartezian(M1,M2);
    cout<<"Produs cartezian: "<<endl<<M<<endl;

    cout<<endl<<"Citeste multime perechi:"<<endl;
    cin>>MP;
    cout<<MP;
    //qsort(MP.get_mpni(),MP.get_nrp(),sizeof(pereche_nr_intregi),cmp_mtp);
    cout<<"Multime perechi dupa sortare:"<<endl;
    qsort(MP.get_mpni(),MP.get_nrp(),sizeof(pereche_nr_intregi),GetMin<pereche_nr_intregi>);
    cout<<MP;*/

    ifstream f;
    f.open("in.txt");
    if(f.is_open())
        cout<<"Deschis"<<endl;
    multime M1,M2;
    f>>M1>>M2;
    cout<<"M1:"<<M1<<"M2:"<<M2;
    multime ID;
    ID=(M1-M2);
    cout<<"diferenta:  "<<ID;
    multime IR=M1+M2;
    cout<<"reuniunea:  "<<IR;
    multime II=M1*M2;
    cout<<"intersectia:  "<<II;

    multime_perechi_nr_intregi M,MP;
    M = produs_cartezian(M1,M2);
    cout<<"Produs cartezian: "<<endl<<M<<endl;

    f>>MP;
    cout<<"Afiseaza multime de perechi"<<endl;
    cout<<MP;
    //qsort(MP.get_mpni(),MP.get_nrp(),sizeof(pereche_nr_intregi),cmp_mtp);
    cout<<"Multime perechi dupa sortare:"<<endl;
    qsort(MP.get_mpni(),MP.get_nrp(),sizeof(pereche_nr_intregi),GetMin<pereche_nr_intregi>);
    cout<<MP;

    return 0;
}

///METODE CLASA MULTIME
multime& multime::operator=(const multime &M)
{
    if(this != &M)
    {
        nr_el=M.nr_el;
        m=new int[nr_el];
        for(int i=0;i<nr_el;i++)
            m[i]=M.m[i];
        return *this;
    }
}

istream& operator>>(istream& in,multime& M)
{
    in>>M.nr_el;
    M.m=new int[M.nr_el];
    for(int i=0;i<M.nr_el;i++)
        in>>M.m[i];
    M.transformare();
    return in;
}

ifstream& operator>>(ifstream& fin,multime &M)
{
    fin>>M.nr_el;
    M.m=new int[M.nr_el];
    for(int i=0;i<M.nr_el;i++)
        fin>>M.m[i];
    M.transformare();
    return fin;
}

ostream& operator<<(ostream& out,multime &M)
{
    out<<'{';
    for(int i=0;i<M.nr_el-1;i++)
        out<<' '<<M.m[i]<<';';
    if(M.nr_el!=0)out<<' '<<M.m[M.nr_el-1]<<" }";
    else
        out<<"Multime vida";
    out<<endl;
    return out;
}




int cmp(const void* el1 , const void* el2)
    {
        int e1=*(int *)el1;
        int e2=*(int *)el2;
        return e1-e2;
    }

void multime::transformare()
{
    qsort(m,nr_el,sizeof(int),cmp);
    int k=0;
    for(int i=1;i<nr_el;i++)
    {
        if(m[i]==m[i-1-k])
        {
            k++;
        }
        else
        {
            m[i-k]=m[i];
        }
    }
    nr_el=nr_el-k;

}

void multime::scoate_unice()
{
    qsort(m,nr_el,sizeof(int),cmp);
    int k=0;
    if(m[0]!=m[1])
        {
            k++;
        }
    for(int i=1;i<nr_el-1;i++)
    {
        if(m[i]!=m[i-1] && m[i]!=m[i+1])
        {
            k++;
        }
        else
        {
            m[i-k]=m[i];
        }
    }
    if(m[nr_el-1]!=m[nr_el-2])
        nr_el--;
    nr_el=nr_el-k;

}


multime operator+(multime M1, multime M2)
{
    multime R;
    R.nr_el=M1.nr_el+M2.nr_el;
    R.m=new int[R.nr_el];

    int i;
    for(i=1;i<=M1.nr_el;i++)
        R.m[i-1]=M1.m[i-1];
    for(i=1;i<=M2.nr_el;i++)
        R.m[M1.nr_el-1+i]=M2.m[i-1];
    R.transformare();
    return R;
}

multime operator*(multime M1, multime M2)
{
    multime I;
    I.nr_el=M1.nr_el+M2.nr_el;
    I.m=new int[I.nr_el];

    int i;
    for(i=1;i<=M1.nr_el;i++)
        I.m[i-1]=M1.m[i-1];
    for(i=1;i<=M2.nr_el;i++)
        I.m[M1.nr_el-1+i]=M2.m[i-1];
    qsort(I.m,I.nr_el,sizeof(int),cmp);
    I.scoate_unice();
    I.transformare();
    return I;

}

multime operator-(multime M1, multime M2)
{
    int j=0,i=1,k=0;
    while(M2.m[j]<M1.m[0] && j<M2.m[j])
    j++;
    if(j<M2.m[j] && M2.m[j]==M1.m[0])
        k++;
    j=0;
    while(j<M2.nr_el && i<M1.nr_el)
    {
        if(M2.m[j]==M1.m[i])
        {
            k++;
            j++;
        }
        else
        {
            if(M2.m[j]>=M1.m[i-1] && M2.m[j]<M1.m[i])
            {
                j++;
            }
            M1.m[i-k]=M1.m[i];
        }
        i++;
    }
    while(i<M1.nr_el)
    {
        M1.m[i-k]=M1.m[i];
        i++;
    }
    M1.nr_el=M1.nr_el-k;
    return M1;

}

///METODE CLASA PERECHE_NR_INTREGI
istream& operator>>(istream& in, pereche_nr_intregi& P)
{
    in>>P.st>>P.dr;
    return in;
}

ifstream& operator>>(ifstream& fin, pereche_nr_intregi& P)
{
    fin>>P.st>>P.dr;
    return fin;
}

ostream& operator<<(ostream& out,pereche_nr_intregi& P)
{
    out<<'('<<P.st<<" ; "<<P.dr<<')';
    return out;
}

pereche_nr_intregi& pereche_nr_intregi::operator=(const pereche_nr_intregi& P)
{
    if(this != &P)
    {
        this->st=P.st;
        this->dr=P.dr;
    }
    return *this;
}

bool operator==(pereche_nr_intregi p1 , pereche_nr_intregi p2)
{
    return p1.st==p2.st && p1.dr==p2.dr;
}
bool operator!=(pereche_nr_intregi p1, pereche_nr_intregi p2)
{
    return p1.st!=p2.st || p1.dr!=p2.dr;
}
bool operator<(pereche_nr_intregi p1, pereche_nr_intregi p2)
{
    if(p1.st<p2.st)
        return 1;
    else
    {
        if(p1.st==p2.st)
        {
            return p1.dr<p2.dr;
        }
        else
            return 0;
    }
}


///METODE CLASA MUTIME_PERECHI_NR_INTREGI

multime_perechi_nr_intregi& multime_perechi_nr_intregi::operator=(const multime_perechi_nr_intregi& M)
{
    if(this != &M)
    {
        this->nrp=M.nrp;
        this->mpni=new pereche_nr_intregi[this->nrp];
        for(int i=0;i<nrp;i++)
            this->mpni[i]=M.mpni[i];
    }
    return *this;
}



istream& operator>>(istream& in , multime_perechi_nr_intregi& M)
{
    cout<<"Numar perechi:";
    in>>M.nrp;
    M.mpni=new pereche_nr_intregi[M.nrp];
    cout<<endl<<"Introduceti perechile"<<endl;
    for(int i=0;i<M.nrp;i++)
        cin>>M.mpni[i];
    return in;
}

ifstream& operator>>(ifstream& fin , multime_perechi_nr_intregi& M)
{
    cout<<"Citeste multime de perechi"<<endl;
    fin>>M.nrp;
    M.mpni=new pereche_nr_intregi[M.nrp];
    for(int i=0;i<M.nrp;i++)
        fin>>M.mpni[i];
    return fin;
}

ostream& operator<<(ostream& out, multime_perechi_nr_intregi& M)
{
    out<<"Nr perechi: "<<M.nrp<<endl;
    out<<"Perechi:"<<endl;
    for(int i=0;i<M.nrp;i++)
        cout<<M.mpni[i]<<' ';
    out<<endl;
    return out;
}

template <class myclass>
int GetMin(const void* a,const void* b)
{
    myclass va=*(myclass*)a;
    myclass vb=*(myclass*)b;
    return !(va<vb);
}


/*int cmp_mtp(const void *a,const void *b)
{
    pereche_nr_intregi va=*(pereche_nr_intregi*)a;
    pereche_nr_intregi vb=*(pereche_nr_intregi*)b;
    return !(va<vb);
}*/

///FUNCTIE INDEPENDENTA


multime_perechi_nr_intregi produs_cartezian(multime M1 , multime M2)
{
    multime_perechi_nr_intregi MP;
    MP.nrp = M1.get_nr_el() * M2.get_nr_el();
    MP.mpni=new pereche_nr_intregi[MP.nrp];

    int i,j;
    for(i=0;i<M1.get_nr_el();i++)
        for(j=0;j<M2.get_nr_el();j++)
    {
        MP.mpni[i*M2.get_nr_el()+j].set_st(M1.get_el(i));
        MP.mpni[i*M2.get_nr_el()+j].set_dr(M2.get_el(j));
    }
    return MP;
}
