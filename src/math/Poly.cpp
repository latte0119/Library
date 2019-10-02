/*
each operation:O(n) or O(nlogn) 
*/
 
template<class Mint,class Convoluter>
struct Poly{
	vector<Mint>v;
    inline void normalize(){
        while(v.size()&&v.back()==0)v.pop_back();
    }
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
 
    Poly pre(int n){
        return {v.begin(),v.begin()+min(n,size())};
    }
    Poly rev(){
        vector<Mint>res=v;
        res.normalize();
        reverse(res.begin(),res.end());
        return res;
    }
    Poly diff(int n){
        vector<Mint>res(n);
        for(int i=1;i<size()&&i<=n;i++)res[i-1]=coef(i)*i;
        return res;
    }
    Poly inte(int n){
        vector<Mint>res(n);
        for(int i=0;i<size()&&i+1<n;i++)res[i+1]=coef(i)/(i+1);
        return res;
    }
 
    Poly inv(int m){
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
 
 
	Mint& operator[](const int i){return v[i];}
};
//using poly=Poly<mint,NTT>;
 
template<class Mint,class Convoluter>
ostream& operator<<(ostream& ost,Poly<Mint,Convoluter>a){
    for(int i=0;i<a.size();i++){
        if(i)cout<<" ";
        cout<<a.v[i];
    }
    return ost;
}

/*
verified:
https://atc001.contest.atcoder.jp/submissions/7826645
yosupo judge
*/