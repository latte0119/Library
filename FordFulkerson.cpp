struct FordFulkerson{
    struct edge{
        int to,cap,rev;
        edge(int to,int cap,int rev):to(to),cap(cap),rev(rev){}
    };
    const int INF=1001001001;
    vector<vector<edge>>G;
    vector<int>used;

    FordFulkerson(int v):G(v),used(v){}

    void addEdge(int from,int to,int cap){
        G[from].push_back(edge(to,cap,G[to].size()));
        G[to].push_back(edge(from,0,G[from].size()-1));
    }

    int dfs(int v,int t,int f){
        if(v==t)return f;
        used[v]=true;
        for(int i=0;i<G[v].size();i++){
            edge &e=G[v][i];
            if(used[e.to]||e.cap==0)continue;
            int d=dfs(e.to,t,min(f,e.cap));
            if(d==0)continue;
            e.cap-=d;
            G[e.to][e.rev].cap+=d;
            return d;
        }
        return 0;
    }

    int maxFlow(int s,int t){
        int flow=0;
        while(true){
            fill(used.begin(),used.end(),0);
            int f=dfs(s,t,INF);
            if(f==0)return flow;
            flow+=f;
        }
    }
};
