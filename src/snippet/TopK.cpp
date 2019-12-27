struct TopK{
	int K;
	multiset<int>S,T;
	int sum;
	TopK(int K=0):K(K),sum(0){}

	void add(int x){
		S.insert(x);
		sum+=x;
		if(S.size()>K){
			T.insert(*S.begin());
			sum-=*S.begin();
			S.erase(S.begin());
		}
	}	
	void del(int x){
		assert(S.size()>0);
		if(x>=*S.begin()){
			sum-=x;
			S.erase(S.find(x));
		}
		else{
			T.erase(T.find(x));
		}

		if(S.size()<K&&T.size()){
			S.insert(*T.rbegin());
			sum+=*T.rbegin();
			T.erase(--T.end());
		}
	}
};