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

void makeFF(int p,int q,vector<int>&fact,vector<int>&ifact){
    int P=1;
    for(int i=0;i<q;i++)P*=p;

    fact=vector<int>(P+1);
    ifact=vector<int>(P+1);

    fact[0]=1;
    for(int i = 1;i <= P;i++){
		if(i % p == 0){
		fact[i] = fact[i-1];
		}else{
			fact[i] = fact[i-1] * i % P;
		}
	}
	for(int i = 0;i <= P;i++){
		int ret = 1;
		int mul = fact[i];
		for(int n = P/p*(p-1)-1;n > 0;n >>= 1){
			if(n&1){
				ret = (ret * mul) % P;
			}
			mul = (mul * mul) % P;
		}
		ifact[i] = (int)ret;
	}
}

int C(int n,int r,int p,int q){
    if(n<0||r<0||r>n)return 0;

    vector<int>fact,ifact;
    makeFF(p,q,fact,ifact);

    int P=1;
    for(int i=0;i<q;i++)P*=p;

    int z=n-r;
    int e0=0;

	for(int u = n/p;u > 0;u /= p)e0 += u;
	for(int u = r/p;u > 0;u /= p)e0 -= u;
	for(int u = z/p;u > 0;u /= p)e0 -= u;

	int em = 0;
	for(int u = n/P;u > 0;u /= p)em += u;
	for(int u = r/P;u > 0;u /= p)em -= u;
	for(int u = z/P;u > 0;u /= p)em -= u;

	int ret=1;

	while(n > 0){
		ret = ret * fact[n%P] % P * ifact[r%P] % P * ifact[z%P] % P;
		n /= p; r /= p; z /= p;
	}
	for(int i = 0;i < e0;i++)ret = ret * p % P;
	if(!(p == 2 && q >= 3) && (em&1)==1)ret = (P-ret) % P;
	return ret;
}
