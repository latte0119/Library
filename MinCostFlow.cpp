
namespace LP{
using Num=double;
using Vec=vector<Num>;
using Mat=vector<Vec>;
const Num Inf=numeric_limits<Num>::infinity();
const Num NoSolution=numeric_limits<Num>::quiet_NaN();
Num EPS=1e-10;
/*
min c*x
s.t. A*x<=b
     x>=0
*/
Num simplex(const Mat &A,const Vec &b,const Vec &c){
    const int m=A.size(),n=A[0].size();

    Mat D(m+1,Vec(n+m+1));
    Vec id(m+n);
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++)D[i][j]=A[i][j];
        D[i][n+i]=1;
        D[i][n+m]=-b[i];
    }
    for(int i=0;i<n;i++)D[m][i]=c[i];

    for(int i=0;i<m;i++)id[i]=n+i;
    for(int i=0;i<n;i++)id[m+i]=i;

    while(true){
        int r=n;
        for(int i=n-1;i>=0;i--)if(D[m][id[m+i]]<-EPS)r=i;
        if(r==n)return D[m][n+m];
        int s=m;
        for(int i=0;i<m;i++)if(D[i][id[m+r]]>EPS){
            if(s==m||-D[s][n+m]/D[s][id[m+r]]>-D[i][n+m]/D[i][id[m+r]])s=i;
        }
        if(s==m)return Inf;//NoBound
        Num k=D[s][id[m+r]];
        for(int i=0;i<=n+m;i++)D[s][i]/=k;
        for(int i=0;i<=m;i++){
            if(i==s)continue;
            k=D[i][id[m+r]];
            for(int j=0;j<=n+m;j++)D[i][j]-=k*D[s][j];
        }
        swap(id[s],id[m+r]);
    }
}
}
