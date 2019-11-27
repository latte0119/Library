struct CentroidDecomposition{
	int N;
	vector<vector<int>>G;
	vector<vector<int>>T;
	vector<int>used,sz;
	int r;
	void set(int n){
		N=n;
		G.resize(N);
		T.resize(N);
	}
	void addEdge(int a,int b){
		G[a].push_back(b);
		G[b].push_back(a);
	}

	int calcSubtreeSize(int v,int p){
		sz[v]=1;
		for(auto u:G[v]){
			if(u==p||used[u])continue;
			sz[v]+=calcSubtreeSize(u,v);
		}
		return sz[v];
	}

	pair<int,int>findCentroid(int v,int p,int ov){
		pair<int,int>ret(N,-1);
		int mx=ov-sz[v];
		for(auto u:G[v]){
			if(u==p||used[u])continue;
			ret=min(ret,findCentroid(u,v,ov));
			mx=max(mx,sz[u]);
		}
		ret=min(ret,pair<int,int>(mx,v));
		return ret;
	}

	void dfs(int v,int p){
		calcSubtreeSize(v,-1);
		v=findCentroid(v,-1,sz[v]).second;
		used[v]=true;
		if(p==-1)r=v;
		else T[p].push_back(v);
		for(auto u:G[v])if(!used[u])dfs(u,v);
	}

	void decompose(){
		used.resize(N);
		sz.resize(N);
		dfs(0,-1);
	}

	inline int root()const{
		return r;
	}
	vector<int>&operator[](int i){
		return T[i];
	}
};
CentroidDecomposition ct;
