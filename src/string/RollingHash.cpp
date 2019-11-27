struct ModX{
	using ull=uint64_t;
	static const ull mod=(1ll<<61)-1;
	static const ull MASK30=(1ll<<30)-1;
	static const ull MASK31=(1ll<<31)-1;

	ull a;

	ModX& s(ull vv){
		a=vv<mod?vv:vv-mod;
		return *this;
	}
	ModX(ull a=0):a(a%mod){}
	
	ModX& operator+=(const ModX& x){return s(a+x.a);}
	ModX& operator-=(const ModX& x){return s(a+mod-x.a);}
	ModX& operator*=(const ModX& x){
		const ull au=a>>31;
		const ull ad=a&MASK31;
		const ull bu=x.a>>31;
		const ull bd=x.a&MASK31;
		const ull mid=ad*bu+au*bd;
		const ull midu=mid>>30;
		const ull midd=mid&MASK30;
		const ull z=au*bu*2+midu+(midd<<31)+ad*bd;
		return s((z&mod)+(z>>61));
	}

	ModX operator+(const ModX &x)const{return ModX(*this)+=x;}
	ModX operator-(const ModX &x)const{return ModX(*this)-=x;}
	ModX operator*(const ModX &x)const{return ModX(*this)*=x;}

	bool operator==(const ModX &x)const{return a==x.a;}
	bool operator!=(const ModX &x)const{return a!=x.a;}
	bool operator<(const ModX &x)const{return a<x.a;}

	ModX operator-()const{return ModX()-*this;}
};

istream& operator>>(istream& in,const ModX& a){
	return (in>>a.a);
}

ostream& operator<<(ostream& out,const ModX& a){
	return (out<<a.a);
}
using xint=ModX;
const xint base(119);
const int RHSIZE=1111111;
xint basepow[RHSIZE];
struct RHInit{
	RHInit(){
		basepow[0]=1;
		for(int i=1;i<RHSIZE;i++)basepow[i]=basepow[i-1]*base;
	}
}RHInitDummy;