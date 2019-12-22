/*
c.size()==2 -> edge
c.size()>2 -> cycle
*/
struct Cactus{
    vector<vector<int>>cs;

    
    vector<vector<int>>G;
    vector<int>vis,par,dep;
    void dfs(int v){
        vis[v]=1;
        for(auto u:G[v]){
            if(!vis[u]){
                par[u]=v;
                dep[u]=dep[v]+1;
                dfs(u);
            }
            else if(dep[u]<dep[v]){
                int w=v;
                vector<int>c{w};
                while(true){
                    w=par[w];
                    c.push_back(w);
                    if(w==u)break;
                }
                cs.push_back(c);
            }
        }
    }
    Cactus(const vector<vector<int>>&G):G(G){
        vis.resize(G.size());
        par.resize(G.size());
        dep.resize(G.size());
        dfs(0);
    }
};