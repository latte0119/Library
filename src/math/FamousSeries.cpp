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




poly Partition(int n){
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



/*
https://ja.wikipedia.org/wiki/%E3%82%B9%E3%82%BF%E3%83%BC%E3%83%AA%E3%83%B3%E3%82%B0%E6%95%B0
*/

/*
calc [n,k] (0<=k<=n)
O(nlogn)
*/
poly Stirling1th(int n){
	if(n==0){
		return {1};
	}
	int m=n/2;
	poly A=Stirling1th(m);
 
	poly B;
	if(n%2==0){
		B=A;
	}
	else{
		B=poly(m+2);
		B[m+1]=1;
		for(int i=1;i<m+1;i++){
			B[i]=A[i-1]+A[i]*m;
		}
	}
 
	poly C(n-m+1);
	mint f=1;
	for(int i=0;i<=n-m;i++){
		C[n-m-i]=mint(m).pow(i)/f;
		B[i]*=f;
		f*=(i+1);
	}
	C*=B;
	f=1;
	for(int i=0;i<=n-m;i++){
		B[i]=C[n-m+i]/f;
		f*=(i+1);
	}
	return A*B;
}

/*
calc {n,k} (0<=k<=n)
O(nlogn)
*/
poly Stirling2th(int n){
	poly A(n+1),B(n+1);
	mint f=1;
	for(int i=0;i<=n;i++){
		A[i]=mint(i).pow(n)/f;
		B[i]=mint(1)/f;
		if(i&1)B[i]*=-1;
		f*=i+1;
	}
	return (A*B).pre(n+1);
}



/*
Eulerian Number <n,k> is the number of permutations with k "ascents"
https://en.wikipedia.org/wiki/Eulerian_number
*/
poly EulerianNumber(int n){
	vector<mint>fact(n+2);
	fact[0]=1;
	for(int i=1;i<=n+1;i++)fact[i]=fact[i-1]*i;

	poly A(n+1),B(n+1);
	for(int i=0;i<=n;i++){
		A[i]=fact[n+1]/fact[i]/fact[n+1-i];
		if(i&1)A[i]*=-1;

		B[i]=mint(i+1).pow(n);
	}

	return (A*B).pre(n+1);
}
/*
verified:
https://atcoder.jp/contests/joisc2018/submissions/7837609
*/