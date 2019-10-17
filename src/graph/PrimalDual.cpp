struct PrimalDual{
    using F=long long;
    const F INF=1ll<<50;
    
    struct Edge{
        int to;
        F cap,cost;
        int rev;
        Edge(int to,F cap,F cost,int rev):to(to),cap(cap),cost(cost),rev(rev){}
    };
    
    int n;
    vector<vector<Edge>>G;

    PrimalDual(int n):n(n),G(n){}

    void addEdge(int from,int to,F cap,F cost){
        G[from].push_back(Edge(to,cap,cost,G[to].size()));
        G[to].push_back(Edge(from,0,-cost,G[from].size()-1));
    }


    F minCostFlow(int s,int t,F f){
        F cur=0;

        vector<F>h(n);
        vector<int>prevv(n,-1),preve(n,-1);
        vector<F>dist(n);
        priority_queue<pair<F,int>,vector<pair<F,int>>,greater<pair<F,int>>>que;
            
        while(f>0){
            fill(dist.begin(),dist.end(),INF);
            dist[s]=0;
            que.emplace(0,s); 
            while(que.size()){
                F d;
                int v;
                tie(d,v)=que.top();
                que.pop();
                if(dist[v]<d)continue;
                for(int i=0;i<G[v].size();i++){
                    Edge &e=G[v][i];
                    F nd=dist[v]+e.cost+h[v]-h[e.to];
                    if(e.cap>0&&dist[e.to]>nd){
                        dist[e.to]=nd;
                        prevv[e.to]=v;preve[e.to]=i;
                        que.emplace(nd,e.to);
                    }
                }
            }
            if(dist[t]==INF)return -INF;
            for(int v=0;v<n;v++)h[v]+=dist[v];
            F nf=f;
            for(int v=t;v!=s;v=prevv[v]){
                nf=min(nf,G[prevv[v]][preve[v]].cap);
            }
            f-=nf;
            cur+=nf*h[t];
            for(int v=t;v!=s;v=prevv[v]){
                Edge &e=G[prevv[v]][preve[v]];
                e.cap-=nf;
                G[v][e.rev].cap+=nf;
            }
        }
        return cur;
    }
};

