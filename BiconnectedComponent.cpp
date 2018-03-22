struct BiconnectedComponent{
    int N;
    vector<vector<int>>G;
    vector<vector<pair<int,int>>>bc;
    vector<int>ord,low,used;
    stack<pair<int,int>>stk;

    BiconnectedComponent(const vector<vector<int>>&G):G(G){
        N=G.size();
        ord=vector<int>(N);
        low=vector<int>(N);
        used=vector<int>(N);
        int k=0;
        for(int i=0;i<N;i++){
            if(used[i])continue;
            dfs(i,-1,k);
        }
    }

    void dfs(int v,int p,int &k){
        ord[v]=k++;
        low[v]=ord[v];
        used[v]=true;

        for(auto u:G[v]){
            if(u==p)continue;
            if(ord[u]<=ord[v])stk.push({min(u,v),max(u,v)});
            if(!used[u]){
                dfs(u,v,k);
                low[v]=min(low[v],low[u]);
                if(ord[v]<=low[u]){
                    bc.push_back({});
                    while(true){
                        pair<int,int>e=stk.top();
                        stk.pop();
                        bc.back().push_back(e);
                        if(e.first==min(u,v)&&e.second==max(u,v))break;
                    }
                }
            }
            else{
                low[v]=min(low[v],ord[u]);
            }
        }
    }
};
