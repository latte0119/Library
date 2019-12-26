template<class Mint>
struct Poly{
	using Convoluter=ArbitraryModConvolution15<Mint>;
	vector<Mint>v;
	template<class...Args>
	Poly(Args...args):v(args...){}

	Poly(const initializer_list<Mint>&in):v(in.begin(),in.end()){}

	int size()const{return v.size();}

	inline Mint coef(const int i)const{return (i<v.size())?v[i]:Mint(0);}

	Poly operator+(const Poly &x){
		int n=max(size(),x.size());
		vector<Mint>res(n);
		for(int i=0;i<n;i++)res[i]=coef(i)+x.coef(i);
		return res;
	}
	Poly operator-(const Poly &x){
		int n=max(size(),x.size());
		vector<Mint>res(n);
		for(int i=0;i<n;i++)res[i]=coef(i)-x.coef(i);
		return res;
	}
	Poly operator*(const Poly& x){
		return Convoluter::convolute(v,x.v);
	}
	Poly operator*(const Mint& x){
		int n=size();
		vector<Mint>res(n);
		for(int i=0;i<n;i++)res[i]=v[i]*x;
		return res;
	}
	Poly operator/(const Mint& x){
		return (*this)*x.inv();
	}

	Poly& operator+=(const Poly& x){return *this=(*this)+x;}
	Poly& operator-=(const Poly& x){return *this=(*this)-x;}
	Poly& operator*=(const Poly& x){return *this=(*this)*x;}
	Poly& operator*=(const Mint& x){return *this=(*this)*x;}
	Poly& operator/=(const Mint& x){return *this=(*this)/x;}

	Poly pre(int n)const{
		return {v.begin(),v.begin()+min(n,size())};
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
		vector<Mint>res(n);
		for(int i=1;i<size()&&i<=n;i++)res[i-1]=v[i]*i;
		return res;
	}
	Poly inte(int n)const{
		vector<Mint>res(n);
		for(int i=0;i<size()&&i+1<n;i++)res[i+1]=v[i]/(i+1);
		return res;
	}

	Poly inv(int m)const{
		Poly res{1};
		for(int i=1;i<m;i*=2){
			res=(res*Mint(2)-res*res*pre(2*i)).pre(2*i);
		}
		return res.pre(m);
	}
	Poly exp(int n){
		Poly f{1};
		for(int i=1;i<n;i*=2){
			f=(f*(pre(2*i)-f.log(2*i))+f).pre(2*i);
		}
		return f.pre(n);
	}

	Poly log(int n){
		return (diff(n-1)*inv(n-1)).inte(n);
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
