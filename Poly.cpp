template<class Mint>
struct Poly{
	vector<Mint>v;

	template<class...Args>
	Poly(Args...args):v(args...){}

	Poly(const initializer_list<Mint>&in):v(in.begin(),in.end()){}


	int size(){return v.size();}

	Mint coef(const int i)const{return (i<v.size())?v[i]:Mint(0);}

	Poly operator+(const Poly &x)const{
		int n=max(v.size(),x.size());
		vector<Mint>res(n);
		for(int i=0;i<n;i++)res[i]=coef(i)+x.coef(i);
		return res;
	}
	Poly operator-(const Poly &x)const{
		int n=max(v.size(),x.size());
		vector<Mint>res(n);
		for(int i=0;i<n;i++)res[i]=coef(i)-x.coef(i);
		return res;
	}
	Poly operator*(const Poly& x)const{
		return convolute(v,x.v);
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

	vector<Mint>convolute(const vector<Mint>&a,const vector<Mint>&b)const{return a;}

	Mint& operator[](const int i){return v[i];}
};