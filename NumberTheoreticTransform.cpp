const int mods[]={1012924417,998244353,897581057,645922817};
const int roots[]={5,3,3,3};
struct NumberTheoreticTransform{
	int mod;
    int root;
	NumberTheoreticTransform(int mod,int root):mod(mod),root(root){}

	int mul(int x,int y){
		return x*y%mod;
	}
	int add(int x,int y){
		return (x+=y)>=mod?x-mod:x;
	}

	int pow(int x,int y){
		int res=1;
		while(y){
			if(y&1)res=mul(res,x);
			x=mul(x,x);
			y>>=1;
		}
		return res;
	}

	int inv(int x){
		return pow(x,mod-2);
	}

	void ntt(vector<int>&f,bool rev=false){
		int n=f.size();
        for(int i=0,j=1;j<n-1;j++){
            for(int k=n>>1;k>(i^=k);k/=2);
            if(i>j)swap(f[i],f[j]);
        }

     	for(int m=2;m<=n;m*=2){
            int wr=pow(root,(mod-1)/m);
            if(rev)wr=inv(wr);
            for(int i=0;i<n;i+=m){
                int w=1;
                for(int j=0;j<m/2;j++){
                    int f0=f[i+j],f1=mul(w,f[i+j+m/2]);
                    f[i+j]=add(f0,f1);
                    f[i+j+m/2]=add(f0,mod-f1);
                    w=mul(w,wr);
                }
            }
        }
        if(rev){
        	int v=inv(n);
        	for(int i=0;i<n;i++)f[i]=mul(f[i],v);
		}
	}
	vector<int>multiply(vector<int>A,vector<int>B){
        int n=1;
        while(n<A.size()+B.size()-1)n<<=1;
        A.resize(n);B.resize(n);
        ntt(A);
        ntt(B);
        for(int i=0;i<n;i++)A[i]=mul(A[i],B[i]);
        ntt(A,true);
        A.resize(A.size()+B.size()-1);
        return A;
    }
};
