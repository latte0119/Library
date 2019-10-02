/*
based on Cooley-Tukey
O(nlogn)
*/

template<class Mint,int32_t root>
struct NumberTheoreticTransform{
	static void ntt(vector<Mint>&f){
		int n=f.size();
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

    static void intt(vector<Mint>&f){
        reverse(f.begin()+1,f.end());
        ntt(f);
        Mint in=Mint(f.size()).inv();
        for(int i=0;i<f.size();i++)f[i]*=in;
    }

	static vector<Mint>convolute(const vector<Mint>&A,const vector<Mint>&B){
        int n=1<<__lg(A.size()+B.size()-2)+1;
        
        vector<Mint>a=A,b=B;
        a.resize(n);b.resize(n);
        ntt(a);
        ntt(b);
        for(int i=0;i<n;i++)a[i]*=b[i];
        intt(a);
        a.resize(A.size()+B.size()-1);
        return a;
    }
};
//using NTT=NumberTheoreticTransform<mint,3>;



/*
verified:
https://atc001.contest.atcoder.jp/submissions/7826555
*/
