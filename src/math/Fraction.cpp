/*
r in Q:
r=a/b & (a,b)=(1) & b>=0
*/
struct Fraction{
    int64_t gcd(int64_t a,int64_t b){
        return b?gcd(b,a%b):a;
    }
	int64_t a,b;
	Fraction():a(0),b(1){}
	Fraction(int64_t a):a(a),b(1){}
	Fraction(int64_t a,int64_t b):a(a),b(b){
		if(b<0)a*=-1,b*=-1;
        int64_t g=gcd((a>0?a:-a),b);
        a/=g;
        b/=g;
    }
	bool operator==(const Fraction& f)const{return a==f.a&&b==f.b;}
	bool operator!=(const Fraction& f)const{return a!=f.a||b!=f.b;}
	Fraction& operator+=(const Fraction& f){
		int64_t c=a*f.b+b*f.a;
		int64_t d=b*f.b;
		int64_t g=gcd((c>0?c:-c),d);
		a=c/g;
		b=d/g;
		return *this;
	}
	Fraction& operator-=(const Fraction& f){
		int64_t c=a*f.b-b*f.a;
		int64_t d=b*f.b;
		int64_t g=gcd((c>0?c:-c),d);
		a=c/g;
		b=d/g;
		return *this;
	}
	Fraction& operator*=(const Fraction& f){
		int64_t c=a*f.a;
		int64_t d=b*f.b;
		int64_t g=gcd((c>0?c:-c),d);
		a=c/g;
		b=d/g;
		return *this;
	}
	Fraction& operator/=(const Fraction& f){
		int64_t c=a*f.b;
		int64_t d=b*f.a;
		if(d<0)c*=-1,d*=-1;
		int64_t g=gcd((c>0?c:-c),d);
		a=c/g;
		b=d/g;
		return *this;
	}
	Fraction operator+(const Fraction& f)const{return Fraction(*this)+=f;}
	Fraction operator-(const Fraction& f)const{return Fraction(*this)-=f;}
	Fraction operator*(const Fraction& f)const{return Fraction(*this)*=f;}
	Fraction operator/(const Fraction& f)const{return Fraction(*this)/=f;}
	bool operator<(const Fraction& f)const{return (Fraction(*this)-f).a<0;}
	bool operator>(const Fraction& f)const{return (Fraction(*this)-f).a>0;}
	bool operator<=(const Fraction& f)const{return (Fraction(*this)-f).a<=0;}
	bool operator>=(const Fraction& f)const{return (Fraction(*this)-f).a>=0;}
	Fraction operator+()const{return Fraction(*this);}
	Fraction operator-()const{return Fraction()-Fraction(*this);}
};



/*
verification:
https://atcoder.jp/contests/cpsco2019-s3/submissions/7820631
*/
