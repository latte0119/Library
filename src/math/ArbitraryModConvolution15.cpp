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

template<class Mint,class C>
struct ArbitraryModConvolution15{
    static constexpr double PI=acos(-1);

    static void dft(vector<C>&f){
        int n=f.size();
		int s=__lg(n);

		static vector<vector<C>>w(30);
		w[0]=vector<C>(1,C(1.0,0.0));
		for(int i=1;i<=s;i++){
			if(w[i].size())continue;
			w[i]=vector<C>(1<<i);
			const double t=2*PI/(1<<i);
			for(int j=0;j<1<<i;j++)w[i][j]=(j&1)?polar(1.0,j*t):w[i-1][j>>1];
		}
		

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
	static void idft(vector<C>&f){
		dft(f);
		reverse(f.begin()+1,f.end());
		double in=1.0/f.size();
		for(int i=0;i<f.size();i++)f[i]*=in;
	}

	static vector<Mint>convolute(vector<Mint>A,vector<Mint>B){
		int n=1<<__lg(A.size()+B.size()-2)+1;
        vector<C>g(n),h(n);
		for(int i=0;i<A.size();i++)g[i]=C(A[i].a&~(~0<<15),A[i].a>>15);
		for(int i=0;i<B.size();i++)h[i]=C(B[i].a&~(~0<<15),B[i].a>>15);
		
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
		vector<Mint>AB(A.size()+B.size()-1);
		for(int i=0;i<AB.size();i++){
			Mint ll=g[i].real()+0.5;
			Mint lh=g[i].imag()+0.5;
			Mint hl=h[i].real()+0.5;
			Mint hh=h[i].imag()+0.5;
			AB[i]=(hh*(1<<15)+(lh+hl))*(1<<15)+ll;
		}
		return AB;
	}
};
//using FFT=ArbitraryModConvolution15<mint,complex<double>>;

/*
verified:

*/