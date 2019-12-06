template<class Mint,int root,int lg>
struct NumberTheoreticTransform{
    using Array=array<Mint,1<<lg>;
	static void ntt(Array &f,int n){
        int s=__lg(n);

        for(int i=0,j=1;j<n-1;j++){
            for(int k=n>>1;k>(i^=k);k>>=1);
            if(i>j)swap(f[i],f[j]);
        }

        for(int m=1;m<=s;m++){
            Mint wr=Mint(root).pow(Mint(-1).a>>m);
            for(int i=0;i<n;i+=1<<m){
                Mint w=1;
                for(int j=0;j<1<<m-1;j++){
                    Mint f0=f[i+j],f1=w*f[i+j+(1<<m-1)];
                    f[i+j]=f0+f1;
                    f[i+j+(1<<m-1)]=f0-f1;
                    w*=wr;
                }
            }
        }
	}

    static void intt(Array &f,int n){
        reverse(f.begin()+1,f.begin()+n);
        ntt(f,n);
        Mint in=Mint(n).inv();
        for(int i=0;i<n;i++)f[i]*=in;
    }

	static vector<Mint>convolute(const vector<Mint>&A,const vector<Mint>&B){
        int n=1<<__lg(A.size()+B.size()-2)+1;
        
        static Array g,h;
        for(int i=0;i<n;i++)g[i]=h[i]=0;
        ntt(g,n);
        ntt(h,n);
        for(int i=0;i<n;i++)g[i]*=h[i];
        intt(g,n);
        
        vector<Mint>AB(A.size()+B.size()-1);
        for(int i=0;i<AB.size();i++)AB[i]=g[i];
        return AB;
    }
};
using NTT=NumberTheoreticTransform<mint,3,18>;
