// \sum{i=0}^{\infty} Bi/i! x^i
// \Sk(n)=sum{i=0}^{n-1} i^k = 1/(k+1) \sum{i=0}^{k} binom(k+1,i)Bi n^{k-i+1}
poly BernoulliEGF(int n){
	poly A(n);
	A[0]=1;
	for(int i=1;i<n;i++)A[i]=A[i-1]/(i+1);
	return A.inv(n);
}

/*
verified:
https://www.codechef.com/viewsolution/26916572
*/




poly PartitionGF(int n){
	poly A(n);
	A[0]=1;
	for(int k=1;k<n;k++){
		if((long long)k*(3*k+1)/2<=n)A[k*(3*k+1)/2]+=k%2?-1:1;
		if((long long)k*(3*k-1)/2<=n)A[k*(3*k-1)/2]+=k%2?-1:1;
	}
	return A.inv(n);
}

/*
verified:
https://judge.yosupo.jp/submission/477
*/