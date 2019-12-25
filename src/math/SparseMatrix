template<class K>
vector<K>berlekampMassey(const vector<K>&s){
	const int N=s.size();
	vector<K>b={K(1)},c={K(1)};
	K y=K(1);

	for(int ed=1;ed<=N;ed++){
		int l=c.size(),m=b.size();
		K x=0;
		for(int i=0;i<l;i++)x+=c[i]*s[ed-l+i];
		b.emplace_back(0);
		m++;
		if(x==K(0))continue;
		K freq=x/y;
		if(l<m){
			auto tmp=c;
			c.insert(c.begin(),m-l,K(0));
			for(int i=0;i<m;i++)c[m-1-i]-=freq*b[m-1-i];
			b=tmp;
			y=x;
		}
		else{
			for(int i=0;i<m;i++)c[l-1-i]-=freq*b[m-1-i];
		}
	}
	return c;
}

template<class Mint>
struct RandomNumberGenerator{
	mt19937 mt;
	uniform_int_distribution<int32_t>uid;
	RandomNumberGenerator():mt(119),uid(0,Mint(-1).a){}
	Mint operator()(){
		return uid(mt);
	}
};

template<class Mint>
vector<Mint>mul(const vector<tuple<int,int,Mint>>&S,int N,const vector<Mint>&b){
	vector<Mint>c(N);
	for(auto &t:S){
		c[get<0>(t)]+=get<2>(t)*b[get<1>(t)];
	}
	return c;
}

template<class Mint>
vector<Mint>minimalPolynomialForVector(const vector<vector<Mint>>&vs){
	int N=vs.size();
	int M=vs[0].size();

	RandomNumberGenerator<Mint>rng;
	vector<Mint>u(M);
	for(int i=0;i<M;i++)u[i]=rng();

	vector<Mint>f(N);
	for(int i=0;i<N;i++){
		for(int j=0;j<M;j++)f[i]+=u[j]*vs[i][j];
	}
	return berlekampMassey(f);
}

template<class Mint>
vector<Mint>minimalPolynomialForSparseMatrix(vector<tuple<int,int,Mint>>S,int N){
	vector<Mint>b(N);
	RandomNumberGenerator<Mint>rng;
	for(int i=0;i<N;i++)b[i]=rng();

	vector<vector<Mint>>vs;
	for(int i=0;i<2*N;i++){
		vs.push_back(b);
		b=mul(S,N,b);
	}
	return minimalPolynomialForVector(vs);
}

template<class Mint>
Mint determinamtOfSparseMatrix(vector<tuple<int,int,Mint>>S,int N){
	vector<mint>D(N);
	RandomNumberGenerator<Mint>rng;
	for(int i=0;i<N;i++)D[i]=rng();
	for(auto &t:S)get<2>(t)*=D[get<1>(t)];

	auto P=minimalPolynomialForSparseMatrix(S,N);
	Mint detSD=P[0];
	if(N&1)detSD*=Mint(-1);
	Mint detD=Mint(1);
	for(int i=0;i<N;i++)detD*=D[i];
	return detSD/detD;
}