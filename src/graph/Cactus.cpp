/*
c.size()==2 -> bridge
c.size()>2 -> cycle
*/
struct Cactus{
    vector<vector<int>>cs;

    
    vector<vector<int>>G;
    vector<int>vis,par,dep,mark;
    void dfs(int v){
        vis[v]=1;
        for(auto u:G[v]){
            if(!vis[u]){
                par[u]=v;
                dep[u]=dep[v]+1;
                dfs(u);
            }
            else if(dep[u]<dep[v]-1){
                int w=v;
                vector<int>c{w};
                while(true){
					mark[w]=true;
                    w=par[w];
                    c.push_back(w);
                    if(w==u)break;
                }
                cs.push_back(c);
            }
        }
    }

    vector<vector<int>>decompose(const vector<vector<int>>&G_){
		G=G_;
        vis.resize(G.size());
        par.resize(G.size());
        dep.resize(G.size());
		mark.resize(G.size());
        dfs(0);
		for(int i=1;i<G.size();i++)if(!mark[i]){
			vector<int>tmp={i,par[i]};
			cs.push_back(tmp);
		}
		return cs;
    }
	Cactus(){}
};