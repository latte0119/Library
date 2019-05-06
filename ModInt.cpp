template<int64_t mod>struct ModInt{
	int64_t a;
	inline int64_t normalize(int64_t x){
		x%=mod;
		if(x<0)x+=mod;
		return x;
	}
	ModInt(const int64_t a=0):a(normalize(a)){}

	ModInt& operator+=(const ModInt &x){
		a+=x.a;
		if(a>=mod)a-=mod;
		return *this;
	}
	ModInt& operator-=(const ModInt &x){
		a-=x.a;
		if(a<0)a+=mod;
		return *this;
	}
	ModInt& operator*=(const ModInt &x){
		a=a*x.a%mod;
		return *this;
	}
	ModInt& operator/=(const ModInt &x){
		*this*=x.inv();
		return *this;
	}

	ModInt operator+(const ModInt x){return ModInt(*this)+=x;}
	ModInt operator-(const ModInt x){return ModInt(*this)-=x;}
	ModInt operator*(const ModInt x){return ModInt(*this)*=x;}
	ModInt operator/(const ModInt x){return ModInt(*this)/=x;}
	bool operator==(const ModInt x){return a==x.a;}
	bool operator!=(const ModInt x){return a!=x.a;}

	ModInt operator-(){return ModInt(0)-ModInt(*this);}
	ModInt pow(int64_t ex)const{
		int64_t x=a;
		int64_t res=1;
		while(ex){
			if(ex&1)res=res*x%mod;
			x=x*x%mod;
			ex>>=1;
		}
		return ModInt(res);
	}
	ModInt inv()const{return pow(mod-2);}
};