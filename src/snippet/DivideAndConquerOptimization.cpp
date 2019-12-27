//Upper Triangular Matrix
namespace DCOptUTM{
using D=int;
const D INF=numeric_limits<D>::max()/10;
vector<D>dp,nex;


int cur_l,cur_r;

inline D f(int l,int r){
}

void ex_r(){
	//add

	cur_r++;
}
void ex_l(){
    cur_l--;

	//add
}

void sh_r(){
    cur_r--;
	//del
}

void sh_l(){
	//del

    cur_l++;
}

// nex : [l,r)    cand : [opt_l,opt_r]
void solve(int l,int r,int opt_l,int opt_r){
	if(l==r)return;
	int m=(l+r)/2;

	while(m>cur_r)ex_r();
	while(opt_l<cur_l)ex_l();
	while(m<cur_r)sh_r();
	while(opt_l>cur_l)sh_l();

	//cur_l==opt_l
	//cur_r==m

	pair<D,int>mi(INF,opt_l);
	while(cur_l<m&&cur_l<=opt_r){
		chmin(mi,pair<D,int>(dp[cur_l]+f(cur_l,cur_r),cur_l));
		sh_l();
	}
	nex[m]=mi.fi;
	if(l+1==r)return;
	solve(l,m,opt_l,mi.se);
	solve(m+1,r,mi.se,opt_r);
}

vector<D>convolute(const vector<D>&ini){
	dp=ini;
	nex.resize(ini.size());
	solve(0,dp.size(),0,dp.size());
	return nex;
}

vector<D>monotoneMinima(int N){
	return convolute(vector<D>(N+1,0));
}


//dp[k][i]=min{dp[k-1][j]+f(j,i)  | j<i};
vector<D>calcDP(int N,int K){
	vector<D>cur(N+1,INF);
	cur[0]=0;
	for(int k=0;k<K;k++){
		cur=convolute(cur);
	}
	return cur;
}

}
/*
https://paper.dropbox.com/doc/DivideAndConquerOptimization-aZu7wwzXNbLV32aG0EkHv

*/