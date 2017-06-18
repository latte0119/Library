struct EdmondsKarp{
    struct edge{
        int to,cap,rev;
        edge(int to,int cap,int rev):to(to),cap(cap),rev(rev){}
    };

    const int INF=1001001001;
    vector<vector<edge>>G;
    vector<int>used,prevv,preve;
    EdmondsKarp(int v):G(v),used(v),prevv(v),preve(v){}

    void addEdge(int from,int to,int cap){
        G[from].push_back(edge(to,cap,G[to].size()));
        G[to].push_back(edge(from,0,G[from].size()-1));
    }

    int maxFlow(int s,int t){
        int flow=0;
        while(true){
            fill(used.begin(),used.end(),0);

            queue<int>que;
            que.push(s);
            used[s]=true;

            while(que.size()){
                int v=que.front();
                que.pop();

                for(int i=0;i<G[v].size();i++){
                    edge &e=G[v][i];
                    if(used[e.to]||e.cap==0)continue;
                    used[e.to]=true;
                    prevv[e.to]=v;
                    preve[e.to]=i;
                    que.push(e.to);
                }
            }


            if(!used[t])return flow;
            int f=INF;

            for(int v=t;v!=s;v=prevv[v])f=min(f,G[prevv[v]][preve[v]].cap);

            flow+=f;
            for(int v=t;v!=s;v=prevv[v]){
                edge &e=G[prevv[v]][preve[v]];
                e.cap-=f;
                G[e.to][e.rev].cap+=f;
            }
        }
    }
};

