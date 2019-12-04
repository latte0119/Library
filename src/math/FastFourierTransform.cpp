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
 
template<int lg>
struct FastFourierTransform{
    using D=double;
    using C=complex<D>;
    using Array=array<C,1<<lg>;

    static constexpr D PI=acos(-1);
 
    static void dft(Array &f,int n){
		int s=__lg(n);
	
		static vector<vector<C>>w(30);
		w[0].assign(1,1.0);
		for(int i=1;i<=s;i++){
			if(w[i].size())continue;
			w[i].resize(1<<i);
			const D t=2*PI/(1<<i);
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
	static void idft(Array &f,int n){
		dft(f,n);
		reverse(f.begin()+1,f.begin()+n);
		D in=1.0/n;
		for(int i=0;i<n;i++)f[i]*=in;
	}
 
    static vector<D>convolute(const vector<D>&A,const vector<D>&B){
        int n=1<<__lg(A.size()+B.size()-2)+1;
        static Array g,h;
        for(int i=0;i<n;i++)g[i]=h[i]=0;
        for(int i=0;i<A.size();i++)g[i]=A[i];
        for(int i=0;i<B.size();i++)h[i]=B[i];
 
        dft(g,n);
        dft(h,n);
        for(int i=0;i<n;i++)g[i]*=h[i];
        idft(g,n);
 
        vector<D>AB(A.size()+B.size()-1);
        for(int i=0;i<AB.size();i++)AB[i]=g[i].real();
        return AB;
    }
};
//using FFT=FastFourierTransform<18>;