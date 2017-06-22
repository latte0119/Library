
struct MinCostFlow{
    struct edge{
        int to,cap,cost,rev;
        edge(int to,int cap,int cost,int rev):to(to),cap(cap),cost(cost),rev(rev){}
    };

    const int INF=1001001001;
    int V;
    vector<vector<edge>>G;
    vector<int>dist,prevv,preve;

    MinCostFlow(int v):V(v),G(v),dist(v),prevv(v),preve(v){}

    void addEdge(int from,int to,int cap,int cost){
        G[from].pb(edge(to,cap,cost,G[to].size()));
        G[to].pb(edge(from,0,-cost,G[from].size()-1));
    }


    int minCostFlow(int s,int t,int f){
        int res=0;
        while(f>0){
            fill(dist.begin(),dist.end(),INF);
            dist[s]=0;
            bool update=true;
            while(update){
                update=false;
                for(int v=0;v<V;v++){
                    if(dist[v]==INF)continue;
                    for(int i=0;i<G[v].size();i++){
                        edge &e=G[v][i];
                        if(e.cap>0&&dist[e.to]>dist[v]+e.cost){
                            dist[e.to]=dist[v]+e.cost;
                            prevv[e.to]=v;
                            preve[e.to]=i;
                            update=true;
                        }
                    }
                }
            }
            if(dist[t]==INF)return -1;

            int d=f;
            for(int v=t;v!=s;v=prevv[v]){
                d=min(d,G[prevv[v]][preve[v]].cap);
            }
            f-=d;
            res+=d*dist[t];
            for(int v=t;v!=s;v=prevv[v]){
                edge &e=G[prevv[v]][preve[v]];
                e.cap-=d;
                G[v][e.rev].cap+=d;
            }
        }
        return res;
    }
};
