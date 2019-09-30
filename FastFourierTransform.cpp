using C = complex<double>;
namespace std {
  template<>
  C& C::operator*=(const C& y) {
    double a = this->real();
    double b = this->imag();
    double c = y.real();
    double d = y.imag();
    return *this=C(a*c-b*d, a*d+b*c);
  }
}

struct FFT{
    using C=complex<double>;
    const double PI=acos(-1);

	int lg;
	vector<C>w;
	FFT(int lg):lg(lg){
		w.resize((1<<lg));
		for(int i=0;i<w.size();i++){
			w[i]=polar(1.0,2.0*PI*i/(1<<lg));
		}
	}

    void dft(vector<C>&f,bool rev=false){
        int n=f.size();
        for(int i=0,j=1;j<n-1;j++){
            for(int k=n>>1;k>(i^=k);k>>=1);
            if(i>j)swap(f[i],f[j]);
        }
        for(int m=2;m<=n;m<<=1){
            for(int i=0;i<n;i+=m){
				int b=(1<<lg)/m;;
                for(int j=0;j<m/2;j++){
                    C f0=f[i+j],f1=w[((1<<lg)+(rev?-1:1)*b*j)&~(~0<<lg)]*f[i+j+m/2];
                    f[i+j]=f0+f1;
                    f[i+j+m/2]=f0-f1;                    
                }
            }
        }
        if(rev){
			double in=1.0/n;
			for(int i=0;i<n;i++)f[i]*=in;
		}
	}

    vector<long long>multiply(vector<long long>A,vector<long long>B){
        int n=1;
        while(n+1<A.size()+B.size())n<<=1;
        vector<C>g(n),h(n);
        for(int i=0;i<A.size();i++)g[i]=A[i];
        for(int i=0;i<B.size();i++)h[i]=B[i];

        dft(g);
        dft(h);
        for(int i=0;i<n;i++)g[i]*=h[i];
        dft(g,true);

        vector<long long>AB(A.size()+B.size()-1);
        for(int i=0;i<AB.size();i++)AB[i]=g[i].real()+0.5;
        return AB;
    }

	vector<long long>multiply2(vector<int>A,vector<int>B,int mod){
		int n=1;
        while(n+1<A.size()+B.size())n<<=1;
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

			C a=(g[i]+gc[i])*h[i]/2.0;
			C b=-(g[i]-gc[i])*h[i]*I/2.0;
			g[i]=a;h[i]=b;
		}

		dft(g,true);
		dft(h,true);
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