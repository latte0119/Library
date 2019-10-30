template<class W>
struct WeightedTree{
	struct Edge{
		int to;
		W cost;
		Edge(int to,W cost):to(to),cost(cost){}
	};

	int V;
	int root;
	vector<vector<Edge>>G;

	vector<int>par,dep,sz,head;
	vector<int>tin,tout;
	vector<W>dist;
	WeightedTree(int V=0,int root=0):V(V),root(root),G(V),par(V),sz(V),dep(V),head(V),dist(V),tin(V),tout(V){}

	void addEdge(int a,int b,W c=W(1)){
		G[a].push_back(Edge(b,c));
		G[b].push_back(Edge(a,c));
	}

	void dfs(int v,int p,int d,W c){
		par[v]=p;
		dep[v]=d;
		sz[v]=1;
		dist[v]=c;

		for(auto &e:G[v]){
			if(e.to==p)continue;
			dfs(e.to,v,d+1,c+e.cost);
			sz[v]+=sz[e.to];
			if(G[v][0].to==p||sz[e.to]>sz[G[v][0].to])swap(G[v][0],e);
		}
	}

	void dfs_hld(int v,int &tt){
		tin[v]=tt++;
		for(auto &e:G[v]){
			if(e.to==par[v])continue;
			head[e.to]=(e.to==G[v][0].to)?head[v]:e.to;
			dfs_hld(e.to,tt);
		}
		tout[v]=tt;
	}
	void init(){
		dfs(root,-1,0,W(0));
		int tt=0;
		dfs_hld(root,tt);
	}

	// 1<<lg >=N-1!!!!!
	int getLCA(int u,int v){
		while(head[u]!=head[v]){
			if(dep[head[u]]<dep[head[v]])swap(u,v);
			u=par[head[u]];
		}
		return dep[u]<dep[v]?u:v;
	}

	int getLength(int a,int b=0){
		int l=getLCA(a,b);
		return dep[a]+dep[b]-2*dep[l];
	}
	W getDistance(int a,int b=0){
		int l=getLCA(a,b);
		return dist[a]+dist[b]-2*dist[l];
	}
	int getDepth(int v){
		return dep[v];
	}
	int getIn(int v){
		return tin[v];
	}
	int getOut(int v){
		return tout[v];
	}
};