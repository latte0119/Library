template<class Mint,class Convoluter>
struct NTTFriendlyPoly{
	vector<Mint>v;
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
	NTTFriendlyPoly operator-(){return NTTFriendlyPoly()-*this;}
 
    NTTFriendlyPoly pre(int n){
        vector<Mint>res(n);
		for(int i=0;i<n&&i<size();i++)res[i]=v[i];
		return res;
    }
    NTTFriendlyPoly rev(){
        vector<Mint>res=v;
		while(res.size()&&res.back()==0)res.pop_back();
        reverse(res.begin(),res.end());
        return res;
    }
    NTTFriendlyPoly diff(int n){
        vector<Mint>res(n);
        for(int i=1;i<size()&&i<=n;i++)res[i-1]=v[i]*i;
        return res;
    }
    NTTFriendlyPoly inte(int n){
        vector<Mint>res(n);
        for(int i=0;i<size()&&i+1<n;i++)res[i+1]=v[i]*mtable.inv(i+1);
        return res;
    }

    NTTFriendlyPoly inv(int n){
        NTTFriendlyPoly res{coef(0).inv()};

        for(int d=1;d<n;d<<=1){
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
        return res.pre(n);
    }
    
    
    NTTFriendlyPoly inv2(int n){
        NTTFriendlyPoly res{coef(0).inv()};
        for(int i=1;i<n;i*=2){
            res=(res*Mint(2)-res*res*pre(2*i)).pre(2*i);
        }
        return res.pre(n);
    }
    
    

	NTTFriendlyPoly exp(int n){
		NTTFriendlyPoly f0{1},g0{1};
		vector<Mint>F0{1};
		for(int d=1;d<n;d<<=1){
			vector<Mint>G0=g0.v;
			Convoluter::ntt(G0);
			vector<Mint>Delta(d);
			for(int j=0;j<d;j++)Delta[j]=F0[j]*G0[j];
			Convoluter::intt(Delta);
			Delta[0]-=1;
			NTTFriendlyPoly delta(2*d);
			for(int j=0;j<d;j++)delta[d+j]=Delta[j];		
			
			NTTFriendlyPoly epsilon(2*d);
			
		
			
			vector<Mint>DF0=f0.diff(d-1).v;DF0.push_back(0);
			Convoluter::ntt(DF0);
			for(int j=0;j<d;j++)DF0[j]*=G0[j];
			Convoluter::intt(DF0);
			for(int j=0;j<d-1;j++){
				epsilon[j]+=coef(j+1)*(j+1);
				epsilon[j+d]+=DF0[j]-coef(j+1)*(j+1);
			}
			epsilon[d-1]+=DF0[d-1];


			Delta=delta.v;
			Convoluter::ntt(Delta);
			vector<Mint>DH0=diff(d-1).v;DH0.resize(2*d);
			Convoluter::ntt(DH0);
			for(int j=0;j<2*d;j++)Delta[j]*=DH0[j];
			Convoluter::intt(Delta);
			for(int j=0;j<d;j++)epsilon[j+d]-=Delta[j+d];
		

			epsilon=epsilon.inte(2*d)-pre(2*d);
			
			vector<Mint>Epsilon=epsilon.v;
			Convoluter::ntt(Epsilon);
			rep(j,d)DH0[j]=f0[j],DH0[j+d]=0;
			Convoluter::ntt(DH0);
			rep(j,2*d)Epsilon[j]*=DH0[j];
			Convoluter::intt(Epsilon);
			f0.v.resize(2*d);
			rep(j,d)f0[j+d]-=Epsilon[j+d];
			//f0=(f0-epsilon*f0).pre(2*d);
			
			G0.resize(2*d);
			rep(j,d)G0[j]=g0[j];
			Convoluter::ntt(G0);
			F0=f0.v; 
			Convoluter::ntt(F0);
			vector<Mint>T(2*d);rep(j,2*d)T[j]=F0[j]*G0[j];
			Convoluter::intt(T);
			rep(j,d){
				T[j]=0;
				T[j+d]=-T[j+d];
			}
			Convoluter::ntt(T);
			rep(j,2*d)T[j]*=G0[j];
			Convoluter::intt(T);
			rep(j,d)T[j]=g0[j];
			g0=T;
		}
		return f0.pre(n);
	}

    NTTFriendlyPoly exp2(int n){
        NTTFriendlyPoly f{1};
        for(int i=1;i<n;i*=2){
            f=(f*(pre(2*i)-f.log(2*i))+f).pre(2*i);
        }
        return f.pre(n);
    }

	NTTFriendlyPoly exp3(int n){
		NTTFriendlyPoly f{1},g{1};
		for(int d=1;d<n;d<<=1){
			g=g*Mint(2)-(g*g*f).pre(d);

			NTTFriendlyPoly q=diff(d-1);
			q=q+g*(f.diff(d-1)-f*q).pre(2*d-1);
			f=f+(f*(pre(2*d)-q.inte(2*d))).pre(2*d);
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
