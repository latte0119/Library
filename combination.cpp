const int mod=1000000007;
inline void add(int &a,int b){
    a+=b;
    if(a>=mod)a-=mod;
}
int mpow(int a,int b){
    int ret=1;
    while(b){
        if(b&1)ret=ret*a%mod;
        a=a*a%mod;
        b>>=1;
    }
    return ret;
}
const int FACTSIZE=1111111;
int fact[FACTSIZE];
int factinv[FACTSIZE];
class FactInit{
public:
    FactInit(){
        fact[0]=1;
        for(int i=1;i<FACTSIZE;i++)fact[i]=fact[i-1]*i%mod;
        factinv[FACTSIZE-1]=mpow(fact[FACTSIZE-1],mod-2);
        for(int i=FACTSIZE-2;i>=0;i--)factinv[i]=factinv[i+1]*(i+1)%mod;
    }
}factInit;


int binom(int n,int k){
    return fact[n]*factinv[n-k]%mod*factinv[k]%mod;
}

int perm(int n,int k){
    return fact[n]*factinv[n-k]%mod;
}