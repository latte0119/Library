inline int extgcd(int a,int b,int& x,int& y){x=1,y=0;int g=a;if(b!=0) g=extgcd(b,a%b,y,x),y-=a/b*x;return g;}
inline int INV(int a,int mod){int x,y;extgcd(a,mod,x,y);return (x%mod+mod)%mod;}
int chineneRemainder(const vector<int>b,const vector<int>m){
    int n=b.size();
    vector<int>constant(n),coef(n,1),v(n);
    for(int i=0;i<n;i++){
        v[i]=(b[i]%m[i]-constant[i]%m[i]+m[i])%m[i];
        v[i]=v[i]%m[i]*INV(coef[i],m[i])%m[i];
        for(int j=i+1;j<n;j++){
            constant[j]=(constant[j]+v[i]*coef[j])%m[j];
            coef[j]=coef[j]*m[i]%m[j];
        }
    }
    int res=0;
    for(int i=n-1;i>=0;i--)res=res*m[i]+v[i];
    return res;
}
