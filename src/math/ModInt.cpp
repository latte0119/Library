template<uint32_t mod>
struct ModInt{
	uint32_t a;
	ModInt& s(uint32_t vv){
		a=vv<mod?vv:vv-mod;
		return *this;
	}

    ModInt(int64_t x=0){s(x%mod+mod);}

	ModInt& operator+=(const ModInt &x){return s(a+x.a);}
	ModInt& operator-=(const ModInt &x){return s(a+mod-x.a);}
	ModInt& operator*=(const ModInt &x){
		a=uint64_t(a)*x.a%mod;
		return *this;
	}
	ModInt& operator/=(const ModInt &x){
		*this*=x.inv();
		return *this;
	}

	ModInt operator+(const ModInt &x)const{return ModInt(*this)+=x;}
	ModInt operator-(const ModInt &x)const{return ModInt(*this)-=x;}
	ModInt operator*(const ModInt &x)const{return ModInt(*this)*=x;}
	ModInt operator/(const ModInt &x)const{return ModInt(*this)/=x;}
	bool operator==(const ModInt &x)const{return a==x.a;}
	bool operator!=(const ModInt &x)const{return a!=x.a;}
	bool operator<(const ModInt &x)const{return a<x.a;}

	ModInt operator-()const{return ModInt()-*this;}
	ModInt pow(int64_t n)const{
		ModInt res(1),x(*this);
		while(n){
			if(n&1)res*=x;
			x*=x;
			n>>=1;
		}
		return res;
	}

    ModInt inv()const{return pow(mod-2);}
};

template<uint32_t mod>
istream& operator>>(istream& in,ModInt<mod>& a){
	return (in>>a.a);
}
template<uint32_t mod>
ostream& operator<<(ostream& out,const ModInt<mod>& a){
	return (out<<a.a);
}
using mint=ModInt<1000000007>;
//using mint=ModInt<998244353>;