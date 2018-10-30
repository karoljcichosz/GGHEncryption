#include<iostream>
#include<math.h>
#include<conio.h>
#include<stdlib.h>
#include<cstdlib>
#include<vector>
#include<iomanip>
#include <time.h>
#include <windows.h>

using namespace std;
typedef double typ;

void print(typ** a, int n);
void wyp(typ** mat, int n, bool pusta);
void wypLosowe(typ** mat, int n, int d);
void jednostkowa(typ** mat, int n);
void psujU(typ** mat, int n);
void printvek(typ* m, int n);

typ** mnozeniemac(typ **A, typ **B, int n);

typ** dekTab(int n);

typ chio(typ **a, int n);

typ** transponowanie(typ** a, int n);

typ ilV(typ** a, int n);

typ wspH(typ** B, int n);

typ** odwroc(typ** A, int n);

typ* mnozeniemacvek(typ* A, typ** B, int n);

typ* encryption(typ* m, typ* e, typ** BZ, int n);

typ* decryption(typ* c, typ** B,typ** U, int n);

int test(int n, int d, int ze);

int main()
{
    srand (time(NULL));
//    int l=0;
//    for(int i=0;i<1000;i++)
//        l=l+test(5,20,1);
//    cout<<l;
    int n,d;
    typ HB=0;
    typ HBZ=1;
    cout<<"Podaj n:";
    cin>>n;
    cout<<"Podaj d:";
    cin>>d;

    typ** B = dekTab(n);
    typ** U = dekTab(n);
    typ** BZ= dekTab(n);
    while(HB<0.85)                                  //znajdowanie bazy o wsp H >= 0.85
    {
        wypLosowe(B,n,d);
        HB=wspH(B,n);
    }
    cout<<"Baza dobra:"<<endl;
    print(B,n);
    cout<<"Wsp Hadamarda: "<<HB<<endl<<endl;
    while(HBZ>0.1||HBZ==0)                          //znajdowanie bazy o wsp H <= 0.1
    {
        jednostkowa(U,n);
        psujU(U,n);
        BZ=mnozeniemac(U,B,n);
        HBZ=wspH(BZ,n);
    }
    cout<<"Baza zla:"<<endl;
    print(BZ,n);
    cout<<"Wsp Hadamarda: "<<HBZ<<endl<<endl;
    cout<<"Macierz unimodularna:"<<endl;
    print(U,n);
    typ* m= new typ[n];                             //definiowanie wektora m
    int ze;
    cout<<"podaj wiadomosc:\n";
    for(int i=0;i<n;i++)
    {
        cin>>m[i];
    }
    cout<<"e[i] nalezy do <-ze,ze>, podaj ze:";
    cin>>ze;
    typ* e= new typ[n];                             //definiowanie wektora e
    for(int i=0;i<n;i++)
        e[i]=rand()%(2*ze+1)-ze;

    typ* c= encryption(m,e,BZ,n);                   //szyfrowanie
    typ* dc= decryption(c,B,U,n);                  //deszyfrowanie
    cout<<"wektor m: ";
    printvek(m,n);
    cout<<"wektor c(zaszyfrowany wektor m): ";
    printvek(c,n);
    cout<<"zdeszyfrowany wektor c: ";
    printvek(dc,n);
    return 0;
}

void print(typ **a, int n)
{
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
            cout<<a[i][j]<<" ";
        cout<<endl;
    }
    cout<<endl;
}

void wyp(typ** mat, int n, bool pusta)
{
    if(pusta)
    {
        for(int i=0; i<n; i++)
        {
            for(int j=0; j<n; j++)
                mat[i][j]=0;
        }
    }
    else
    {
        for(int i=0; i<n; i++)
        {
            for(int j=0; j<n; j++)
            cin>>mat[i][j];
        }
    }
}

void wypLosowe(typ** mat, int n, int d)
{
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            mat[i][j]=rand()%((2*d)+1)-d;
        }
    }
    //print(mat,n);
}

void jednostkowa(typ **mat, int n)
{
    for(int i=0; i<n; i++)
        for(int j=0; j<n ;j++)
        {
            if(i==j)
                mat[i][j]=1;
            else
                mat[i][j]=0;
        }
}

void psujU(typ** mat, int n)
{
    for(int i=1; i<n;i++)
    {
        for(int j=0; j<i; j++)
            mat[i][j]=rand()%101-50;
    }
    //print(mat,n);
}

void printvek(typ* m, int n)
{
    for(int i=0; i<n; i++)
    {
        cout<<m[i]<<" ";
    }
    cout<<endl;
}

typ** mnozeniemac(typ** A, typ** B, int n)
{
    typ** C=dekTab(n);
    int i, j, k;
    for(i = 0; i < n; i++)
        for(j = 0; j < n; j++)
            C[i][j] = 0;
    for(i = 0; i < n; i++)
        for(j = 0; j < n; j++)
            for(k = 0; k < n; k++)
                C[i][j] = C[i][j] + A[i][k] * B[k][j];
    return C;
}

typ** dekTab(int n)
{
    typ** mat = new typ*[n];
    for(int i = 0; i < n; ++i)
        mat[i] = new typ[n];
    return mat;
}

typ chio(typ** a, int n)
{
    double p=1;
    typ** b = dekTab(n);
    for(int i =0; i<n; i++)
    {
        for(int j=0; j<n;j++)
            b[i][j]=a[i][j];
    }
    int z=1;
    while(n>2)
    {
        if(b[z-1][z-1]!=0)
        {
            for(int i=n+z-2; i>=z; i--)
                for(int j=n+z-2; j>=z; j--)
                {
                    b[i][j]=(b[i][j]*b[z-1][z-1])-(b[i][z-1]*b[z-1][j]);
                }
            p=p*pow(b[z-1][z-1],n-2);
            n--;
            z++;
        }
        else
        {
            int q=z-1;
            while(b[q][z-1]==0&&q<n+z-2)
            {
                q++;
            }
            if(b[q][z-1]!=0)
            {
                for(int i=n+z-2; i>=0;i--)
                {
                    swap(b[z-1][i],b[q][i]);
                }
                p=p*(-1);
            }
            else return 0;
        }
    }
    if(p!=0)
        p=(b[z+n-2][z+n-2]*b[z+n-3][z+n-3]-b[z+n-2][z+n-3]*b[z+n-3][z+n-2])*(1/p);
    for(int i=0;i<z+n-2;i++)
        delete[] b[i];
    delete[] b;
    return p;
    //print(b, n+z-1); //
}

typ** transponowanie(typ** a, int n)
{
    typ** at= new typ*[n];
    for(int i=0; i<n; i++)
        at[i]=new typ[n];

    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            at[i][j]=a[j][i];
    return at;
}

typ ilV(typ **a, int n)
{
    typ x,y=1;
    for(int i=0; i<n; i++)
    {
        x=0;
        for(int j=0;j<n;j++)
            x=x+pow(a[i][j],2);
        y=y*sqrt(x);
    }
    return y;
}

typ wspH(typ **B, int n)
{
    typ detB=chio(B,n);
    typ detL=sqrt(detB*detB);
    typ H=pow((detL/ilV(B,n)),(1.0/(double)n));
    //cout<<H<<"\n";
    return H;
}

typ** odwroc(typ** A, int n)
{
    int k,m,o,p;
    typ det=chio(A,n);
    typ** Ai =dekTab(n);
    typ** Amin=dekTab(n-1);
    for(int i=0; i<n; i++)
    {
        for(int j=0;j<n;j++)
        {
            for(k=0,o=0;k<n-1;k++,o++)
            {
                if(o==i)
                    o++;
                p=0;
                for(m=0,p=0;m<n-1;m++,p++)
                {
                    if(p==j)
                        p++;
                    Amin[k][m]=A[o][p];
                }
            }
            Ai[i][j]=chio(Amin,n-1);
            if((i+j)%2)
                Ai[i][j]=Ai[i][j]*(-1);
        }
    }
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
        {
           Ai[i][j]=Ai[i][j]/det;
        }
    return transponowanie(Ai,n);
}

typ* mnozeniemacvek(typ* A, typ** B, int n)
{
    typ* C=new typ[n];
    int i, k;
    for(i = 0; i < n; i++)
        C[i] = 0;
    for(i = 0; i < n; i++)
        for(k = 0; k < n; k++)
            C[i] = C[i] + A[k] * B[k][i];
    return C;
}

typ* encryption(typ* m, typ* e, typ** BZ, int n)
{
    typ* x=mnozeniemacvek(m,BZ,n);
    for(int i=0; i<n; i++)
        x[i]=x[i]+e[i];
    return x;
}

typ* decryption(typ* c, typ** B, typ** U, int n)
{
     typ* dc= mnozeniemacvek(c,odwroc(B,n),n);
     for(int i=0; i<n;i++)
         dc[i]=round(dc[i]);
     dc=mnozeniemacvek(dc,odwroc(U,n),n);
     for(int i=0; i<n;i++)
         dc[i]=round(dc[i]);
     return dc;
}

int test(int n, int d, int ze)
{
    typ* m=new typ[n];
    for(int i=0;i<n;i++)
    {
        m[i]=i+1;
    }
    typ HB=0;
    typ HBZ=1;

    typ** B = dekTab(n);
    typ** U = dekTab(n);
    typ** BZ= dekTab(n);
    while(HB<0.85)                                  //znajdowanie bazy o wsp H >= 0.85
    {
        wypLosowe(B,n,d);
        HB=wspH(B,n);
    }
    while(HBZ>0.1||HBZ==0)                          //znajdowanie bazy o wsp H <= 0.1
    {
        jednostkowa(U,n);
        psujU(U,n);
        BZ=mnozeniemac(U,B,n);
        HBZ=wspH(BZ,n);
    }
    typ* e= new typ[n];                             //definiowanie wektora e
    for(int i=0;i<n;i++)
        e[i]=rand()%(2*ze+1)-ze;
    typ* c= encryption(m,e,BZ,n);                   //szyfrowanie
    typ* dc= decryption(c,B,U,n);                  //deszyfrowanie
    if(dc[0]!=m[0])
        return 1;
    else
        return 0;

}

