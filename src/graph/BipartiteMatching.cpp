/*
O(V(V+E))
based on Ford-Fulkerson
*/
struct BipartiteMatching{
    int N;
    BipartiteMatching(int n):N(n),G(n),match(n),used(n){}

    vector<vector<int>>G;
    vector<int>match,used;

    void add_edge(int u,int v){
        G[u].push_back(v);
        G[v].push_back(u);
    }

    bool dfs(int v){
        used[v]=true;
        for(auto u:G[v]){
            int w=match[u];
            if(w<0||!used[w]&&dfs(w)){
                match[v]=u;
                match[u]=v;
                return true;
            }
        }
        return false;
    }

    int matching(){
        int res=0;
        fill(match.begin(),match.end(),-1);
        for(int v=0;v<N;v++){
            if(match[v]<0){
                fill(used.begin(),used.end(),0);
                if(dfs(v))res++;
            }
        }
        return res;
    }
};


/*
verified:
http://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=3904290#1
*/
