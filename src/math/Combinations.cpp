template<class Mint>
struct Combinations{
	int N;
	vector<Mint>facts,finvs,invs;
	Combinations(int n):N(n),facts(n),finvs(n),invs(n){
		facts[0]=finvs[0]=1;
		for(int i=1;i<N;i++){
			facts[i]=facts[i-1]*i;
			invs[i]=Mint(i).inv();
			finvs[i]=finvs[i-1]*invs[i];
		}
	}
	inline Mint fact(int n){return facts[n];}
	inline Mint finv(int n){return finvs[n];}
	inline Mint inv(int n){return invs[n];}
	inline Mint binom(int n,int k){return facts[n]*finvs[k]*finvs[n-k];}
};
//Combinations<mint>C(111111);
