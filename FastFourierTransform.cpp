using Cd = complex<double>;
namespace std {
  template<>
  Cd& Cd::operator*=(const Cd& y) {
    double a = this->real();
    double b = this->imag();
    double c = y.real();
    double d = y.imag();
    return *this=Cd(a*c-b*d, a*d+b*c);
  }
}

template<class C>
struct FFT{
    const double PI=acos(-1);

	vector<vector<C>>w;
	FFT():w(30){w[0]=vector<C>(1,C(1.0,0.0));}


	void init(int s){
		for(int i=1;i<=s;i++){
			if(w[i].size())continue;
			w[i]=vector<C>(1<<i);
			const double t=2*PI/(1<<i);
			for(int j=0;j<(1<<i);j++){
				w[i][j]=j&1?polar(1.0,j*t):w[i-1][j>>1];
			}
		}
	}

    void dft(vector<C>&f){
        int n=f.size();
		int s=__lg(n);

		init(s);

        for(int i=0,j=1;j<n-1;j++){
            for(int k=n>>1;k>(i^=k);k>>=1);
            if(i>j)swap(f[i],f[j]);
        }

		for(int m=1;m<=s;m++){
			for(int i=0;i<n;i+=1<<m){
				for(int j=0;j<1<<m-1;j++){
					C f0=f[i+j],f1=w[m][j]*f[i+j+(1<<m-1)];
					f[i+j]=f0+f1;
					f[i+j+(1<<m-1)]=f0-f1;
				}
			}
		}
	}
	void idft(vector<C>&f){
		dft(f);
		reverse(f.begin()+1,f.end());
		double in=1.0/f.size();
		for(int i=0;i<f.size();i++)f[i]*=in;
	}

    vector<long long>convolute(vector<long long>A,vector<long long>B){
        int n=1<<__lg(A.size()+B.size()-2)+1;
        vector<C>g(n),h(n);
        for(int i=0;i<A.size();i++)g[i]=A[i];
        for(int i=0;i<B.size();i++)h[i]=B[i];

        dft(g);
        dft(h);
        for(int i=0;i<n;i++)g[i]*=h[i];
        idft(g);

        vector<long long>AB(A.size()+B.size()-1);
        for(int i=0;i<AB.size();i++)AB[i]=g[i].real()+0.5;
        return AB;
    }

	vector<long long>arbitraryModConvolute(vector<long long>A,vector<long long>B,long long mod){
		int n=1<<__lg(A.size()+B.size()-2)+1;
        vector<C>g(n),h(n);
		for(int i=0;i<A.size();i++)g[i]=C(A[i]&~(~0<<15),A[i]>>15);
		for(int i=0;i<B.size();i++)h[i]=C(B[i]&~(~0<<15),B[i]>>15);
		
		dft(g);
		dft(h);

		vector<C>gc=g;
		reverse(gc.begin()+1,gc.end());
		
		C I(0,1);
		for(int i=0;i<n;i++){
			gc[i]=conj(gc[i]);

			C a=(g[i]+gc[i])*h[i]*0.5;
			C b=(g[i]-gc[i])*h[i]*I*(-0.5);
			g[i]=a;h[i]=b;
		}

		idft(g);
		idft(h);
		vector<long long>AB(A.size()+B.size()-1);
		for(int i=0;i<AB.size();i++){
			long long ll=g[i].real()+0.5;
			long long lh=g[i].imag()+0.5;
			long long hl=h[i].real()+0.5;
			long long hh=h[i].imag()+0.5;
			ll%=mod;lh%=mod;hl%=mod;hh%=mod;
			AB[i]=(((hh<<15)+lh+hl<<15)+ll)%mod;
		}
		return AB;
	}
};