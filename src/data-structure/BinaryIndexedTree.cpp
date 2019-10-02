/*
0-indexed
add(k,x): a[k]+=x
sum(k): sum(a[0,k])


space:O(N)
time:O(logN) per query
*/
struct BinaryIndexedTree{
	int n;
	vector<int>dat;
	BinaryIndexedTree(int n=0):n(n){
		dat.resize(n+1);
	}
	void add(int k,int x){
		for(k++;k<=n;k+=k&-k)dat[k]+=x;
	}
	int sum(int k){
		int ret=0;
		for(k++;k;k-=k&-k)ret+=dat[k];
		return ret;
	}
};
