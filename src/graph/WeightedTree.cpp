template<class W>
struct WeightedTree{
	struct Edge{
		int to;
		W cost;
		Edge(int to,W cost):to(to),cost(cost){}
	};

	int V;
	int root;
	int E;
	vector<vector<Edge>>G;

	vector<int>par_,dep_,sz_,head_;
	vector<int>tin_,tout_,vs_;
	vector<W>dist_;
	WeightedTree(int V=0,int root=0):V(V),root(root),G(V),par_(V),sz_(V),dep_(V),head_(V),dist_(V),tin_(V),tout_(V),vs_(V),E(0){}
	void set(int v){
		*this=WeightedTree(v);
	}

	void addEdge(int a,int b,W c=W(1)){
		assert(a<V&&b<V);
		assert(E+1<V);
		G[a].push_back(Edge(b,c));
		G[b].push_back(Edge(a,c));
		E++;
	}

	void dfs(int v,int p,int d,W c){
		par_[v]=p;
		dep_[v]=d;
		sz_[v]=1;
		dist_[v]=c;

		for(auto &e:G[v]){
			if(e.to==p)continue;
			dfs(e.to,v,d+1,c+e.cost);
			sz_[v]+=sz_[e.to];
			if(G[v][0].to==p||sz_[e.to]>sz_[G[v][0].to])swap(G[v][0],e);
		}
	}

	void dfs_hld(int v,int &tt){
		vs_[tt]=v;
		tin_[v]=tt++;
		for(auto &e:G[v]){
			if(e.to==par_[v])continue;
			head_[e.to]=(e.to==G[v][0].to)?head_[v]:e.to;
			dfs_hld(e.to,tt);
		}
		tout_[v]=tt;
	}
	void init(){
		dfs(root,-1,0,W(0));
		int tt=0;
		dfs_hld(root,tt);
	}

	inline int lca(int u,int v)const{
		while(head_[u]!=head_[v]){
			if(dep_[head_[u]]<dep_[head_[v]])swap(u,v);
			u=par_[head_[u]];
		}
		return dep_[u]<dep_[v]?u:v;
	}

	
	inline int ancestor(int v,int k){
		while(v!=-1){
			if(dep_[v]-dep_[head_[v]]<k){
				k-=dep_[v]-dep_[head_[v]]+1;
				v=par_[head_[v]];
				continue;
			}
			return vs_[tin_[v]-k];
		}
		return -1;
	}
	

	inline int par(int v)const{
		return par_[v];
	}

	inline int size(int v)const{
		return sz_[v];
	}
	inline int len(int a,int b=0)const{
		int l=lca(a,b);
		return dep_[a]+dep_[b]-2*dep_[l];
	}
	inline W dist(int a,int b)const{
		int l=lca(a,b);
		return dist_[a]+dist_[b]-2*dist_[l];
	}

	inline W dist(int a)const{
		return dist_[a];
	}

	inline int dep(int v)const{
		return dep_[v];
	}
	inline int tin(int v)const{
		return tin_[v];
	}
	inline int tout(int v)const{
		return tout_[v];
	}

	inline int vs(int k)const{
		return vs_[k];
	}
	inline int heavy(int v)const{
		if(G[v].size()==0||G[v][0].to==par_[v])return -1;
		return G[v][0].to;
	}

	vector<Edge>& operator[](int i){
		return G[i];
	}
};