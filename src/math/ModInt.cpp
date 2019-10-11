/*
GF(p)
inverse:O(log p) based on Fermat's little theorem (a^(p-1)=1 mod p)
*/

template<uint32_t mod>
struct ModInt{
	uint32_t a;
    ModInt(int64_t x=0):a((x%mod+mod)%mod){}

	ModInt& operator+=(const ModInt &x){
		a+=x.a;
		if(a>=mod)a-=mod;
		return *this;
	}
	ModInt& operator-=(const ModInt &x){
		if(a>=x.a)a-=x.a;
		else a+=mod-x.a;
		return *this;
	}
	ModInt& operator*=(const ModInt &x){
		a=(uint64_t)a*x.a%mod;
		return *this;
	}
	ModInt& operator/=(const ModInt &x){
		a=(uint64_t)a*x.inv().a%mod;
		return *this;
	}

	ModInt operator+(const ModInt x){return ModInt(*this)+=x;}
	ModInt operator-(const ModInt x){return ModInt(*this)-=x;}
	ModInt operator*(const ModInt x){return ModInt(*this)*=x;}
	ModInt operator/(const ModInt x){return ModInt(*this)/=x;}
	bool operator==(const ModInt &x){return a==x.a;}
	bool operator!=(const ModInt &x){return a!=x.a;}

	ModInt operator-(){return ModInt(0)-ModInt(*this);}
	inline ModInt pow(uint64_t ex)const{
		uint64_t x=a;
		uint64_t res=1;
		while(ex){
			if(ex&1)res=res*x%mod;
			x=x*x%mod;
			ex>>=1;
		}
		return ModInt(res);
	}

    inline ModInt inv()const{return pow(mod-2);}
};

template<uint32_t mod>
istream& operator>>(istream& in,ModInt<mod>& a){
	return (in>>a.a);
}
template<uint32_t mod>
ostream& operator<<(ostream& out,const ModInt<mod>& a){
	return (out<<a.a);
}
using mint=ModInt<998244353>;
