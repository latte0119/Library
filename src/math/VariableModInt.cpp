struct ModA{
	static uint32_t mod; 
	uint32_t a;
	ModA& s(uint32_t vv){
		a=vv<mod?vv:vv-mod;
		return *this;
	}

	ModA(int64_t x=0){s(x%mod+mod);}

	ModA& operator+=(const ModA &x){return s(a+x.a);}
	ModA& operator-=(const ModA &x){return s(a+mod-x.a);}
	ModA& operator*=(const ModA &x){
		a=uint64_t(a)*x.a%mod;
		return *this;
	}
	ModA& operator/=(const ModA &x){
		*this*=x.inv();
		return *this;
	}

	ModA operator+(const ModA &x)const{return ModA(*this)+=x;}
	ModA operator-(const ModA &x)const{return ModA(*this)-=x;}
	ModA operator*(const ModA &x)const{return ModA(*this)*=x;}
	ModA operator/(const ModA &x)const{return ModA(*this)/=x;}
	bool operator==(const ModA &x)const{return a==x.a;}
	bool operator!=(const ModA &x)const{return a!=x.a;}
	bool operator<(const ModA &x)const{return a<x.a;}

	ModA operator-()const{return ModA()-*this;}
	ModA pow(int64_t n)const{
		ModA res(1),x(*this);
		while(n){
			if(n&1)res*=x;
			x*=x;
			n>>=1;
		}
		return res;
	}

	int64_t extgcd(int64_t p,int64_t q,int64_t &x,int64_t &y)const{
		if(q==0){
			x=1;
			y=0;
			return p;
		}
		int64_t g=extgcd(q,p%q,y,x);
		y-=(p/q)*x;
		return g;
	}

	ModA inv()const{
		int64_t x,y;
		assert(extgcd(a,mod,x,y)==1);
		return ModA(x);
	}
};
using aint=ModA;
uint32_t aint::mod=1000000007;
istream& operator>>(istream& in,const ModA& a){
	return (in>>a.a);
}
ostream& operator<<(ostream& out,const ModA& a){
	return (out<<a.a);
}