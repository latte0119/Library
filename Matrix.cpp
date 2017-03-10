/*
vector<vector<int>>‚Å•\Œ»‚·‚éƒo[ƒWƒ‡ƒ“
Še—v‘f‚ÍAmod=10^9+n‚Æ‚©‚ÅŒvŽZ‚·‚é
*/

const int mod=1000000007;
typedef vector<int>vec;
typedef vector<vec>mat;


int mod_pow(int n,int m){
    int ret=1;
    while(m){
        if(m&1)ret=ret*n%mod;
        n=n*n%mod;
        m>>=1;
    }
    return ret;
}

mat mul(const mat &A,const mat &B){
    mat C(A.size(),vec(B[0].size()));
    for(int i=0;i<A.size();i++){
        for(int j=0;j<B[0].size();j++){
            for(int k=0;k<A[0].size();k++){
                C[i][j]=(C[i][j]+A[i][k]*B[k][j])%mod;
            }
        }
    }
    return C;
}

mat mat_pow(mat A,int m){
    mat B(A.size(),vec(A.size()));
    for(int i=0;i<A.size();i++)B[i][i]=1;
    while(m){
        if(m&1)B=mul(B,A);
        A=mul(A,A);
        m>>=1;
    }
    return B;
}

//³•ûs—ñonly
int det(mat A){
    int ret=1;
    for(int i=0;i<A.size();i++){
        int idx=-1;
        for(int j=i;j<A.size();j++)if(A[j][i]!=0)idx=j;
        if(idx==-1)return 0;
        if(i!=idx){
            ret=(mod-ret)%mod;
            swap(A[i],A[idx]);
        }
        ret=ret*A[i][i]%mod;
        int inv=mod_pow(A[i][i],mod-2);
        for(int j=0;j<A.size();j++)A[i][j]=A[i][j]*inv%mod;
        for(int j=i+1;j<A.size();j++){
            int a=A[j][i];
            for(int k=0;k<A.size();k++)A[j][k]=(A[j][k]-A[i][k]*a%mod+mod)%mod;
        }
    }
    return ret;
}

int MatrixTreeTheorem(vector<int>vs,vector<int>A,vector<int>B){
    if(vs.size()<=1)return 1;
    sort(vs.begin(),vs.end());
    vs.erase(unique(vs.begin(),vs.end()),vs.end());
    for(int i=0;i<A.size();i++){
        A[i]=lower_bound(vs.begin(),vs.end(),A[i])-vs.begin();
        B[i]=lower_bound(vs.begin(),vs.end(),B[i])-vs.begin();
    }

    mat M(vs.size()-1,vec(vs.size()-1));
    for(int i=0;i<A.size();i++){
        if(A[i]+1!=vs.size())M[A[i]][A[i]]++;
        if(B[i]+1!=vs.size())M[B[i]][B[i]]++;
        if(A[i]+1!=vs.size()&&B[i]+1!=vs.size()){
            M[A[i]][B[i]]=mod-1;
            M[B[i]][A[i]]=mod-1;
        }
    }

    return det(M);
}
