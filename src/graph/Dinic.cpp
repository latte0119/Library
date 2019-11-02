struct Dinic{
    using F=long long;
    static const F INF;

    struct Edge{
        int dst;
        F cap;
        int rev;
        Edge(int dst,F cap,int rev):dst(dst),cap(cap),rev(rev){}
    };

    int n;
    vector<vector<Edge>>G;
    vector<int>iter,level;
    Dinic(int n):n(n),G(n),iter(n),level(n){}
    inline void addEdge(int src,int dst,F cap){
        G[src].push_back(Edge(dst,cap,G[dst].size()));
        G[dst].push_back(Edge(src,0,G[src].size()-1));
    }
    inline void addUndirectedEdge(int src,int dst,F cap){
        G[src].push_back(Edge(dst,cap,G[dst].size()));
        G[dst].push_back(Edge(src,cap,G[src].size()-1));
    }

    void bfs(int s){
        level.assign(n,-1);
        queue<int>que;
        level[s]=0;
        que.push(s);
        while(que.size()){
            int u=que.front();
            que.pop();
            for(auto &e:G[u]){
                if(e.cap==0||level[e.dst]!=-1)continue;
                level[e.dst]=level[u]+1;
                que.push(e.dst);
            }
        }
    }

    F dfs(const int &s,const int &u,F cur){
        if(s==u)return cur;
        F sum=0;
        for(int &i=iter[u];i<G[u].size();i++){
            Edge &e=G[u][i],&ee=G[e.dst][e.rev];
            const int &v=e.dst;
            if(level[v]>=level[u]||ee.cap==0)continue;
            F f=dfs(s,v,min(cur-sum,ee.cap));
            if(f<=0)continue;
            ee.cap-=f;e.cap+=f;
            sum+=f;
            if(sum==cur)break;
        }
        return sum;
    }


    F maxFlow(int s,int t){
        F flow=0;
        while(true){
            bfs(s);
            if(level[t]==-1)return flow;
            iter.assign(n,0);
            flow+=dfs(s,t,INF);
        }
    }
};
const Dinic::F Dinic::INF=1ll<<50;

/*
http://topcoder.g.hatena.ne.jp/Mi_Sawa/20140311
*/