template<class Mint,class Convoluter>
struct NTTFriendlyPoly{
	vector<Mint>v;
    inline void normalize(){
        while(v.size()&&v.back()==0)v.pop_back();
    }
	template<class...Args>
	NTTFriendlyPoly(Args...args):v(args...){}
 
	NTTFriendlyPoly(const initializer_list<Mint>&in):v(in.begin(),in.end()){}
 
	int size()const{return v.size();}
 
	inline Mint coef(const int i)const{return (i<v.size())?v[i]:Mint(0);}
 
	NTTFriendlyPoly operator+(const NTTFriendlyPoly &x){
		int n=max(size(),x.size());
		vector<Mint>res(n);
		for(int i=0;i<n;i++)res[i]=coef(i)+x.coef(i);
		return res;
	}
	NTTFriendlyPoly operator-(const NTTFriendlyPoly &x){
		int n=max(size(),x.size());
		vector<Mint>res(n);
		for(int i=0;i<n;i++)res[i]=coef(i)-x.coef(i);
		return res;
	}
	NTTFriendlyPoly operator*(const NTTFriendlyPoly& x){
		return Convoluter::convolute(v,x.v);
	}
	NTTFriendlyPoly operator*(const Mint& x){
		int n=size();
		vector<Mint>res(n);
		for(int i=0;i<n;i++)res[i]=v[i]*x;
		return res;
	}
	NTTFriendlyPoly operator/(const Mint& x){
		return (*this)*x.inv();
	}
 
	NTTFriendlyPoly& operator+=(const NTTFriendlyPoly& x){return *this=(*this)+x;}
	NTTFriendlyPoly& operator-=(const NTTFriendlyPoly& x){return *this=(*this)-x;}
	NTTFriendlyPoly& operator*=(const NTTFriendlyPoly& x){return *this=(*this)*x;}
	NTTFriendlyPoly& operator*=(const Mint& x){return *this=(*this)*x;}
	NTTFriendlyPoly& operator/=(const Mint& x){return *this=(*this)/x;}
 
    NTTFriendlyPoly pre(int n){
        return {v.begin(),v.begin()+min(n,size())};
    }
    NTTFriendlyPoly rev(){
        vector<Mint>res=v;
        reverse(res.begin(),res.end());
        return res;
    }
    NTTFriendlyPoly diff(int n){
        vector<Mint>res(n);
        for(int i=1;i<size()&&i<=n;i++)res[i-1]=coef(i)*i;
        return res;
    }
    NTTFriendlyPoly inte(int n){
        vector<Mint>res(n);
        for(int i=0;i<size()&&i+1<n;i++)res[i+1]=coef(i)/(i+1);
        return res;
    }

    NTTFriendlyPoly inv(int m){
        NTTFriendlyPoly res{coef(0).inv()};

        for(int d=1;d<m;d<<=1){
            vector<Mint>f(2*d),g(2*d);
            for(int j=0;j<2*d;j++)f[j]=coef(j);
            for(int j=0;j<d;j++)g[j]=res[j];
            
            Convoluter::ntt(f);Convoluter::ntt(g);
            for(int j=0;j<2*d;j++)f[j]*=g[j];
            Convoluter::intt(f);
            for(int j=0;j<d;j++){
                f[j]=0;
                f[j+d]=-f[j+d];
            }
            Convoluter::ntt(f);
            for(int j=0;j<2*d;j++)f[j]*=g[j];
            Convoluter::intt(f);
            for(int j=0;j<d;j++)f[j]=res[j];
            res=f;
        }
        return res.pre(m);
    }
    
    /*
    NTTFriendlyPoly inv2(int m){
        NTTFriendlyPoly res{coef(0).inv()};
        for(int i=1;i<m;i*=2){
            res=(res*Mint(2)-res*res*pre(2*i)).pre(2*i);
        }
        return res.pre(m);
    }
    */
    
    NTTFriendlyPoly exp(int n){
        NTTFriendlyPoly f{1};
        for(int i=1;i<n;i*=2){
            f=(f*(pre(2*i)-f.log(2*i))+f).pre(2*i);
        }
        return f.pre(n);
    }
 
    NTTFriendlyPoly log(int n){
        return (diff(n-1)*inv(n-1)).inte(n);
    }
 
    NTTFriendlyPoly pow(int n,mint k){
		auto res=log(n);
		res*=k;
		return res.exp(n);
	}
	Mint& operator[](const int i){return v[i];}
};
using poly=NTTFriendlyPoly<mint,NTT>;
 
template<class Mint,class Convoluter>
ostream& operator<<(ostream& ost,NTTFriendlyPoly<Mint,Convoluter>a){
    for(int i=0;i<a.size();i++){
        if(i)cout<<" ";
        cout<<a.v[i];
    }
    return ost;
}
