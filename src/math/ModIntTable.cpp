template<class Mint,int32_t lg>
struct ModIntTable{
	int N;
	vector<Mint>facts,finvs,invs;
	ModIntTable():N(1<<lg),facts(N),finvs(N),invs(N){
		const uint32_t mod=Mint(-1).a+1;
		invs[1]=1;
		for(int i=2;i<N;i++)invs[i]=invs[mod%i]*(mod-mod/i);

		facts[0]=1;
		finvs[0]=1;
		for(int i=1;i<N;i++){
			facts[i]=facts[i-1]*i;
			finvs[i]=finvs[i-1]*invs[i];
		}
	}
	inline Mint fact(int n)const{return facts[n];}
	inline Mint finv(int n)const{return finvs[n];}
	inline Mint inv(int n)const{return invs[n];}
	inline Mint binom(int n,int k)const{return facts[n]*finvs[k]*finvs[n-k];}
    inline Mint perm(int n,int k)const{return facts[n]*finvs[n-k];} 
};
ModIntTable<mint,19>mtable;