template<class Mint>
struct Matrix{
	vector<vector<Mint>>a;

	template<class... Args>
	Matrix(Args... args):a(args...){}

	Matrix(const initializer_list<vector<Mint>>&in):a(in.begin(),in.end()){}

	const vector<Mint>& operator[](int i)const{return a[i];}
	vector<Mint>& operator[](int i){return a[i];}
	inline int size()const{return a.size();}

	Matrix& operator+=(const Matrix &A){
		for(int i=0;i<a.size();i++){
			for(int j=0;j<a[0].size();j++){
				a[i][j]+=A[i][j];
			}
		}
		return *this;
	}
	Matrix& operator-=(const Matrix &A){
		for(int i=0;i<a.size();i++){
			for(int j=0;j<a[0].size();j++){
				a[i][j]-=A[i][j];
			}
		}
	}
	Matrix& operator*=(const Matrix &A){
		Matrix C(a.size(),vector<Mint>(A.a[0].size()));
		for(int i=0;i<a.size();i++){
			for(int j=0;j<A[0].size();j++){
				for(int k=0;k<a[0].size();k++)C[i][j]+=a[i][k]*A[k][j];
			}
		}
		return *this=C;
	}

	static Matrix identity(int n){
		Matrix I(n,vector<Mint>(n));
		for(int i=0;i<n;i++)I[i][i]=1;
		return I;
	}

	Matrix operator+(const Matrix &A)const{return Matrix(*this)+=A;}
	Matrix operator-(const Matrix &A)const{return Matrix(*this)-=A;}
	Matrix operator*(const Matrix &A)const{return Matrix(*this)*=A;}
	

	Matrix pow(int n){
		Matrix res=identity(size());
		Matrix x=*this;

		while(n){
			if(n&1)res*=x;
			x*=x;
			n>>=1;
		}
		return res;
	}

	Matrix transpose(){
		Matrix T(a[0].size(),vector<Mint>(a.size()));
		for(int i=0;i<a.size();i++){
			for(int j=0;j<a[0].size();j++)T[j][i]=a[i][j];
		}
		return T;
	}

	bool operator==(const Matrix &A)const{
		return a==A.a;
	}
	bool operator!=(const Matrix &A)const{
		return a!=A.a;
	}
	bool operator<(const Matrix &A)const{
		return a<A.a;
	}
	bool operator>(const Matrix &A)const{
		return a>A.a;
	}


	Mint det(){
		Mint ret=1;
		vector<vector<Mint>>m=a;

		for(int i=0;i<a.size();i++){
			if(m[i][i]==0){
				for(int j=i+1;j<a.size();j++)if(m[j][i]!=0){
					swap(a[i],a[j]);
					ret=-ret;
					break;
				}
			}
			if(m[i][i]==0)return 0;
			ret*=m[i][i];

			Mint in=m[i][i].inv();
			for(int j=0;j<a.size();j++)m[i][j]*=in;
			for(int j=i+1;j<a.size();j++){
				Mint coef=m[j][i];
				for(int k=0;k<a.size();k++)m[j][k]-=m[i][k]*coef;
			}
		}
		return ret;
	}
};
using mat=Matrix<mint>;
template<class Mint>
ostream& operator<<(ostream& ost,const Matrix<Mint>&A){
	for(int i=0;i<A.size();i++){
		ost<<"{";
		const vector<Mint>&a=A[i];
		for(int j=0;j<a.size();j++){
			if(j)ost<<",";
			ost<<a[j];
		}ost<<"}\n";
	}
	return ost;
}
