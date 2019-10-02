/*
based on Cooley-Cukey
O(nlogn)
*/

template<class Mint>
struct NumberTheoreticTransform{
    Mint root;
	NumberTheoreticTransform(Mint root):root(root){}
	void ntt(vector<Mint>&f){
		int n=f.size();
        for(int i=0,j=1;j<n-1;j++){
            for(int k=n>>1;k>(i^=k);k>>=1);
            if(i>j)swap(f[i],f[j]);
        }

        int s=__lg(n);

        for(int m=1;m<=s;m++){
            Mint wr=root.pow(Mint(-1).a/(1<<m));
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

    void intt(vector<Mint>&f){
        reverse(f.begin()+1,f.end());
        ntt(f);
        Mint in=Mint(f.size()).inv();
        for(int i=0;i<f.size();i++)f[i]*=in;
    }

	vector<Mint>convolute(vector<Mint>A,vector<Mint>B){
        int m=A.size()+B.size()-1;
        int n=1<<__lg(m-1)+1;
        A.resize(n);B.resize(n);
        ntt(A);
        ntt(B);
        for(int i=0;i<n;i++)A[i]*=B[i];
        intt(A);
        A.resize(m);
        return A;
    }
};


/*
verified:
https://atc001.contest.atcoder.jp/submissions/7823077
*/
