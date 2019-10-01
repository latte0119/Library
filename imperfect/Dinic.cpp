struct Dinic{
    struct edge{
        int to,cap,rev;
        edge(int to,int cap,int rev):to(to),cap(cap),rev(rev){}
    };

    const int INF=1001001001;
    vector<vector<edge>>G;
    vector<int>level,iter;
    Dinic(int v):G(v),level(v),iter(v){}

    void addEdge(int from,int to,int cap){
        G[from].push_back(edge(to,cap,G[to].size()));
        G[to].push_back(edge(from,0,G[from].size()-1));
    }

    void bfs(int s){
        fill(level.begin(),level.end(),-1);
        queue<int>que;
        level[s]=0;
        que.push(s);
        while(que.size()){
            int v=que.front();
            que.pop();
            for(auto &e:G[v]){
                if(e.cap&&level[e.to]==-1){
                    level[e.to]=level[v]+1;
                    que.push(e.to);
                }
            }
        }
    }

    int dfs(int v,int t,int f){
        if(v==t)return f;
        for(int &i=iter[v];i<G[v].size();i++){
            edge &e=G[v][i];
            if(e.cap>0&&level[v]<level[e.to]){
                int d=dfs(e.to,t,min(f,e.cap));
                if(d>0){
                    e.cap-=d;
                    G[e.to][e.rev].cap+=d;
                    return d;
                }
            }
        }
        return 0;
    }

    int maxFlow(int s,int t){
        int flow=0;
        while(true){
            bfs(s);
            if(level[t]<0)return flow;
            fill(iter.begin(),iter.end(),0);
            int f;
            while((f=dfs(s,t,INF))>0)flow+=f;
        }
    }
};
