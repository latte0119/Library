/*
C[g]=sum{A[i]*B[j] | gcd(i,j)=g}
time:O(NloglogN)
space:O(N)
*/
template<class M>
vector<M>GCDConvolution(vector<M>A,vector<M>B){
	int m=max(A.size(),B.size());
	A.resize(m);
	B.resize(m);
	
	vector<int>isprime(m,1);
	for(int i=2;i<m;i++){
		if(!isprime[i])continue;
		for(int k=m/i;k>=1;k--){
			isprime[k*i]=false;
			A[k]+=A[k*i];
			B[k]+=B[k*i];
		}
	}
	for(int i=1;i<m;i++){
		A[i]+=A[0];
		B[i]+=B[0];
	}

	for(int i=0;i<m;i++)A[i]*=B[i];

	isprime=vector<int>(m,1);
	for(int i=2;i<m;i++){
		if(!isprime[i])continue;
		for(int k=1;k*i<m;k++){
			isprime[k*i]=false;
			A[k]-=A[k*i];
		}
	}
	for(int i=1;i<m;i++)A[i]-=A[0];
	return A;
}

