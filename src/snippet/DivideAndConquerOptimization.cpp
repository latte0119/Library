namespace DCOpt{
using D=int;
const D INF=numeric_limits<D>::max()/10;
vector<D>dp,nex;

int L,R;
D val;
void ex_r(){
	//add

    R++;
}
void ex_l(){
    L--;

	//add
}

void sh_r(){
    R--;

	//del
}

void sh_l(){
	//del

    L++;
}

void solve(int l,int r,int opt_l,int opt_r){
	if(l==r)return;
	int m=(l+r)/2;

	while(m>R)ex_r();
	while(opt_l<L)ex_l();
	while(m<R)sh_r();
	while(opt_l>L)sh_l();

	pair<D,int>mi(INF,opt_l);
	while(L<m&&L<=opt_r){
		chmin(mi,pair<D,int>(dp[L]+val,L));
		sh_l();
	}
	nex[m]=mi.fi;
	if(l+1==r)return;
	solve(l,m,opt_l,mi.se);
	solve(m+1,r,mi.se,opt_r);
}

vector<D>calc(){
	dp=vector<D>(N+1,INF);
	dp[0]=0;

	for(int k=1;k<=K;k++){
		nex=vector<D>(N+1,INF);
		solve(1,N+1,0,N-1);
		swap(dp,nex);
	}
	return dp;
}
}

/*
https://paper.dropbox.com/doc/DivideAndConquerOptimization-aZu7wwzXNbLV32aG0EkHv

*/