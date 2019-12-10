namespace NTTFriendlyPoly{
	
	const uint32_t mod=998244353;
	const uint32_t prim_root=3;
 
	using Mint=ModInt<mod>;
 
    
	const int LG=20;
	Mint invs[1<<LG];
	Mint roots[1<<LG+1],iroots[1<<LG+1];
	struct InitTable{
		InitTable(){
			invs[1]=1;
			for(int i=2;i<1<<LG;i++)invs[i]=invs[mod%i]*(mod-mod/i);
            
			rep(w,LG+1){
				const int s=(1<<w)-1;
				const Mint g=Mint(prim_root).pow((mod-1)>>w),ig=g.inv();
				Mint p=1,ip=1;
				rep(i,1<<w){
					roots[s+i]=p;p*=g;
					iroots[s+i]=ip;ip*=ig;
				}
			}
            
		}
	}InitTableDummy;
    

	void ntt(vector<Mint>&f){
		const int n=f.size();
		for(int b=n/2;b>=1;b/=2){
			for(int i=0;i<n;i+=b*2){
				rep(j,b){
					const Mint tmp=f[i+j]-f[i+j+b];
					f[i+j]+=f[i+j+b];
					f[i+j+b]=tmp*roots[b*2-1+j];
				}
			}
		}
	}
 
	void intt(vector<Mint>&f){
		const int n=f.size();
		for(int b=1;b<=n/2;b*=2){
			for(int i=0;i<n;i+=b*2){
				rep(j,b){
					f[i+j+b]*=iroots[b*2-1+j];
					const Mint tmp=f[i+j]-f[i+j+b];
					f[i+j]+=f[i+j+b];
					f[i+j+b]=tmp;
				}
			}
        }
		const Mint in=Mint(n).inv();
		rep(i,n)f[i]*=in;
	}
 
	vector<Mint> multiply(vector<Mint> x,vector<Mint> y){
		int n=x.size()+y.size()-1;
		int s=1<<__lg(n-1)+1;
		x.resize(s);
		y.resize(s);
		ntt(x);ntt(y);
		rep(i,s)
			x[i]*=y[i];
		intt(x);x.resize(n);
		return x;
	}
 
	template<class Mint>
	struct Poly{
		vector<Mint>v;
		template<class...Args>
		Poly(Args...args):v(args...){}
		Poly(const initializer_list<Mint>&in):v(in.begin(),in.end()){}
	
 
		inline int size()const{return v.size();}
	
		inline Mint coef(const int i)const{return (i<v.size())?v[i]:Mint(0);}
	
		Poly operator+(const Poly &x)const{
			int n=max(size(),x.size());
			Poly<Mint>res(n);
			for(int i=0;i<n;i++)res[i]=coef(i)+x.coef(i);
			return res;
		}
		Poly operator-(const Poly &x)const{
			int n=max(size(),x.size());
			Poly<Mint>res(n);
			for(int i=0;i<n;i++)res[i]=coef(i)-x.coef(i);
			return res;
		}
		Poly operator*(const Poly& x)const{
			return multiply(v,x.v);
		}
		Poly operator*(const Mint& x)const{
			int n=size();
			vector<Mint>res(n);
			for(int i=0;i<n;i++)res[i]=v[i]*x;
			return res;
		}

        
		Poly operator/(const Mint& x)const{
			return (*this)*x.inv();
		}
	
		Poly& operator+=(const Poly& x){return *this=(*this)+x;}
		Poly& operator-=(const Poly& x){return *this=(*this)-x;}
		Poly& operator*=(const Poly& x){return *this=(*this)*x;}
		Poly& operator*=(const Mint& x){return *this=(*this)*x;}
		Poly& operator/=(const Mint& x){return *this=(*this)/x;}
		Poly operator-(){return Poly()-*this;}
	
		Poly pre(int n)const{
			Poly<Mint>res(n);
			for(int i=0;i<n&&i<size();i++)res[i]=v[i];
			return res;
		}
        Poly normalize()const{
            vector<Mint>res=v;
            while(res.size()&&res.back()==0)res.pop_back();
            return res;
        }
		Poly rev()const{
            vector<Mint>res=v;
			reverse(res.begin(),res.end());
			return res;
		}
		Poly diff(int n)const{
			Poly<Mint>res(n);
			for(int i=1;i<size()&&i<=n;i++)res[i-1]=v[i]*i;
			return res;
		}
		Poly inte(int n)const{
			Poly<Mint>res(n);
			for(int i=0;i<size()&&i+1<n;i++)res[i+1]=v[i]*invs[i+1];
			return res;
		}
 
		Poly inv(int n)const{
			vector<Mint>res{v[0].inv()};

			for(int d=1;d<n;d<<=1){
				vector<Mint>f(2*d),g(2*d);
				for(int j=0;j<2*d;j++)f[j]=coef(j);
				for(int j=0;j<d;j++)g[j]=res[j];
				
				ntt(f);ntt(g);
				for(int j=0;j<2*d;j++)f[j]*=g[j];
				intt(f);
				for(int j=0;j<d;j++){
					f[j]=0;
					f[j+d]=-f[j+d];
				}
				ntt(f);
				for(int j=0;j<2*d;j++)f[j]*=g[j];
				intt(f);
                for(int j=0;j<d;j++)f[j]=res[j];
				res=f;
			}
			return Poly(res).pre(n);
		}
		
		
		Poly inv2(int n){
			Poly res{coef(0).inv()};
			for(int i=1;i<n;i*=2){
				res=(res*Mint(2)-res*res*pre(2*i)).pre(2*i);
			}
			return res.pre(n);
		}
		
		
 
		Poly exp(int n){
			Poly f0{1},g0{1};
			vector<Mint>F0{1};
			for(int d=1;d<n;d<<=1){
				vector<Mint>G0=g0.v;
				ntt(G0);
				vector<Mint>Delta(d);
				for(int j=0;j<d;j++)Delta[j]=F0[j]*G0[j];
				intt(Delta);
				Delta[0]-=1;
				Poly delta(2*d);
				for(int j=0;j<d;j++)delta[d+j]=Delta[j];		
				
				Poly epsilon(2*d);
				
			
				
				vector<Mint>DF0=f0.diff(d-1).v;DF0.push_back(0);
				ntt(DF0);
				for(int j=0;j<d;j++)DF0[j]*=G0[j];
				intt(DF0);
				for(int j=0;j<d-1;j++){
					epsilon[j]+=coef(j+1)*(j+1);
					epsilon[j+d]+=DF0[j]-coef(j+1)*(j+1);
				}
				epsilon[d-1]+=DF0[d-1];
 
 
				Delta=delta.v;
				ntt(Delta);
				vector<Mint>DH0=diff(d-1).v;DH0.resize(2*d);
				ntt(DH0);
				for(int j=0;j<2*d;j++)Delta[j]*=DH0[j];
				intt(Delta);
				for(int j=0;j<d;j++)epsilon[j+d]-=Delta[j+d];
			
 
				epsilon=epsilon.inte(2*d)-pre(2*d);
				
				vector<Mint>Epsilon=epsilon.v;
				ntt(Epsilon);
				rep(j,d)DH0[j]=f0[j],DH0[j+d]=0;
				ntt(DH0);
				rep(j,2*d)Epsilon[j]*=DH0[j];
				intt(Epsilon);
				f0.v.resize(2*d);
				rep(j,d)f0[j+d]-=Epsilon[j+d];
				//f0=(f0-epsilon*f0).pre(2*d);
 
				if(2*d>=n)break;
				
				G0.resize(2*d);
				rep(j,d)G0[j]=g0[j];
				ntt(G0);
				F0=f0.v; 
				ntt(F0);
				vector<Mint>T(2*d);rep(j,2*d)T[j]=F0[j]*G0[j];
				intt(T);
				rep(j,d){
					T[j]=0;
					T[j+d]=-T[j+d];
				}
				ntt(T);
				rep(j,2*d)T[j]*=G0[j];
				intt(T);
				rep(j,d)T[j]=g0[j];
				g0=T;
			}
			return f0.pre(n);
		}
 
		Poly exp2(int n){
			Poly f{1};
			for(int i=1;i<n;i*=2){
				f=(f*(pre(2*i)-f.log(2*i))+f).pre(2*i);
			}
			return f.pre(n);
		}
 
		Poly exp3(int n){
			Poly f{1},g{1};
			for(int d=1;d<n;d<<=1){
				g=g*Mint(2)-(g*g*f).pre(d);
 
				Poly q=diff(d-1);
				q=q+g*(f.diff(d-1)-f*q).pre(2*d-1);
				f=f+(f*(pre(2*d)-q.inte(2*d))).pre(2*d);
			}
			return f.pre(n);
		}
 
 
	
		Poly log(int n){
			return (diff(n-1)*inv(n-1)).inte(n);
		}
	
		Poly pow(int n,Mint k){
			auto res=log(n);
			res*=k;
			return res.exp(n);
        }

        Poly operator/(const Poly &x){
            auto a=normalize().rev();
            auto b=x.normalize().rev();
            if(a.size()<b.size())return {};
            int m=a.size()-b.size();
            return (a*b.inv(m+1)).pre(m+1).rev();
        }
		Poly operator%(const Poly &x){
			return (*this-(*this/x)*x).normalize();
		}

		Poly& operator/=(const Poly &x){
			return *this=*this/x;
		}
		Poly& operator%=(const Poly &x){
			return *this=*this%x;
		}

		Mint& operator[](const int i){return v[i];}
	};
	
	template<class Mint>
	ostream& operator<<(ostream& ost,Poly<Mint>a){
		for(int i=0;i<a.size();i++){
			if(i)cout<<" ";
			cout<<a.v[i];
		}
		return ost;
	}
	using poly=Poly<Mint>;


	map<pair<int,int>,poly>mem;

	void preCalc(const vector<Mint>&c,int l,int r){
		if(l+1==r){
			mem[{l,r}]={-c[l],Mint(1)};
			return;
		}
		int m=(l+r)>>1;
		preCalc(c,l,m);
		preCalc(c,m,r);
		mem[{l,r}]=mem[{l,m}]*mem[{m,r}];
	}
	void preCalc(const vector<Mint>&c){
		mem.clear();
		preCalc(c,0,c.size());
	}

	void multiEval(poly P,const vector<Mint>&c,vector<Mint>&ans,int l,int r){
		if(l+1==r){
			P%=mem[{l,r}];
			ans[l]=P[0];
			return;
		}
		int m=(l+r)>>1;
		multiEval(P%mem[{l,m}],c,ans,l,m);
		multiEval(P%mem[{m,r}],c,ans,m,r);
	}
	vector<Mint>multiEval(const poly &P,const vector<Mint>&c){
		preCalc(c);
		vector<Mint>ans(c.size());
		multiEval(P,c,ans,0,c.size());
		return ans;
	}

	poly interpolate(const vector<Mint>&x,const vector<Mint>&w,int l,int r){
		if(l+1==r){
			return {w[l]};
		}
		int m=(l+r)>>1;
		return interpolate(x,w,l,m)*mem[{m,r}]+interpolate(x,w,m,r)*mem[{l,m}];
	}
	poly interpolate(const vector<Mint>&x,const vector<Mint>&y){
		preCalc(x);
		auto L=mem[{0,x.size()}];
		vector<Mint>w(x.size());
		multiEval(L.diff(x.size()),x,w,0,x.size());
		for(int i=0;i<x.size();i++)w[i]=y[i]/w[i];
		return interpolate(x,w,0,x.size());
	}
};
 
using NTTFriendlyPoly::poly;
