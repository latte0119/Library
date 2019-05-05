struct fraction{
    int64_t gcd(int64_t a,int64_t b){
        return b?gcd(b,a%b):a;
    }
	int64_t a,b;
	fraction():a(0),b(1){}
	fraction(int64_t a):a(a),b(1){}
	fraction(int64_t a,int64_t b):a(a),b(b){
        int64_t g=gcd(a,b);
        a/=g;
        b/=g;
    }
	bool operator==(const fraction& f){return a==f.a&&b==f.b;}
	bool operator!=(const fraction& f){return a!=f.a||b!=f.b;}
	fraction& operator+=(const fraction& f){
		int64_t c=a*f.b+b*f.a;
		int64_t d=b*f.b;
		int64_t g=gcd((c>0?c:-c),d);
		a=c/g;
		b=d/g;
		return *this;
	}
	fraction& operator-=(const fraction& f){
		int64_t c=a*f.b-b*f.a;
		int64_t d=b*f.b;
		int64_t g=gcd((c>0?c:-c),d);
		a=c/g;
		b=d/g;
		return *this;
	}
	fraction& operator*=(const fraction& f){
		int64_t c=a*f.a;
		int64_t d=b*f.b;
		int64_t g=gcd((c>0?c:-c),d);
		a=c/g;
		b=d/g;
		return *this;
	}
	fraction& operator/=(const fraction& f){
		int64_t c=a*f.b;
		int64_t d=b*f.a;
		if(d<0)c*=-1,d*=-1;
		int64_t g=gcd((c>0?c:-c),d);
		a=c/g;
		b=d/g;
		return *this;
	}
	fraction operator+(const fraction& f)const{return fraction(*this)+=f;}
	fraction operator-(const fraction& f)const{return fraction(*this)-=f;}
	fraction operator*(const fraction& f)const{return fraction(*this)*=f;}
	fraction operator/(const fraction& f)const{return fraction(*this)/=f;}
	bool operator<(const fraction& f)const{return (fraction(*this)-f).a<0;}
	bool operator>(const fraction& f)const{return (fraction(*this)-f).a>0;}
	bool operator<=(const fraction& f)const{return (fraction(*this)-f).a<=0;}
	bool operator>=(const fraction& f)const{return (fraction(*this)-f).a>=0;}
	fraction operator+()const{return fraction(*this);}
	fraction operator-()const{return fraction()-fraction(*this);}
};