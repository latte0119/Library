struct GeneralMatching{
	int N;
	int cur;
	vector<int>t,p,used,base,match;
	queue<int>que;
	vector<vector<int>>G;

	GeneralMatching(int n):N(n),cur(0),t(n),p(n),used(n),base(n),match(n),G(n){}

	void addEdge(int v,int u){
		G[v].push_back(u);
		G[u].push_back(v);
	}

	int get(int v){
		return base[v]==v?v:base[v]=get(base[v]);
	}

	int getLCA(int v,int u){
		v=get(v);u=get(u);
		cur++;
		while(true){
			if(v!=-1){
				if(used[v]==cur)return v;
				used[v]=cur;
				v=match[v]==-1?-1:get(p[match[v]]);
			}
			swap(v,u);
		}
	}

	void blossom(int v,int u,int b){
		while(get(v)!=b){
			p[v]=u;
			u=match[v];
			if(t[u]==1){
				t[u]=0;
				que.push(u);
			}
			base[v]=b;
			base[u]=b;
			v=p[u];
		}
	}

	void augment(int u,int v){
		while(u!=-1){
			int nu=match[p[u]];
			match[u]=p[u];
			match[p[u]]=u;
			u=nu;
		}
	}

	bool bfs(int s){
		fill(p.begin(),p.end(),-1);
		fill(t.begin(),t.end(),-1);
		iota(base.begin(),base.end(),0);
		t[s]=0;
		que=queue<int>();
		que.push(s);
		while(que.size()){
			int v=que.front();que.pop();
			for(auto u:G[v]){
				if(t[u]==-1){
					t[u]=1;
					p[u]=v;
					if(match[u]==-1){
						augment(u,v);
						return true;
					}
					int w=match[u];
					t[w]=0;
					que.push(w);
				}
				else if(t[u]==0&&get(v)!=get(u)){
					int b=getLCA(v,u);
					blossom(v,u,b);
					blossom(u,v,b);
				}
			}
		}
		return false;
	}
	int solve(){
		fill(match.begin(),match.end(),-1);
		int res=0;
		for(int i=0;i<N;i++){
			if(match[i]==-1&&bfs(i))res++;
		}
		return res;
	}
};