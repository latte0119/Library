namespace MWA{
struct Edge{
    int from,to,cost;
    Edge *prevEdge;
    //Edge(int from,int to,int cost):from(from),to(to),cost(cost),prevEdge(NULL){}
    Edge(int from,int to,int cost,Edge *prevEdge=NULL):from(from),to(to),cost(cost),prevEdge(prevEdge){}
};

typedef vector<vector<Edge>>Graph;
struct UnionFindTree{
    vector<int>par,sz;
    UnionFindTree(int n){
        par.resize(n);
        sz.resize(n);
        for(int i=0;i<n;i++){
            par[i]=i;
            sz[i]=1;
        }
    }
    int find(int x){
        return x==par[x]?x:par[x]=find(par[x]);
    }
    void unite(int x,int y){
        x=find(x);y=find(y);
        if(x==y)return;
        if(sz[x]<sz[y])swap(x,y);
        sz[x]+=sz[y];par[y]=x;
    }
    bool areSame(int x,int y){
        return find(x)==find(y);
    }
    int size(int x){
        return sz[find(x)];
    }
};

Graph maximumWeightBranching(Graph G){
    int N=G.size();

    vector<Edge>maxEdge(N,Edge(-1,-1,0));

    for(int v=0;v<N;v++)for(auto &e:G[v])if(maxEdge[e.to].cost<e.cost)maxEdge[e.to]=e;

    UnionFindTree uf(N);
    vector<int>isInC(N);
    for(int i=0;i<N;i++){
        if(maxEdge[i].from==-1)continue;
        if(uf.areSame(maxEdge[i].from,i)){
            int v=i;
            while(!isInC[v]){
                isInC[v]=1;
                v=maxEdge[v].from;
            }
            break;
        }
        else{
            uf.unite(maxEdge[i].from,i);
        }
    }

    if(find(isInC.begin(),isInC.end(),1)==isInC.end()){
        Graph ret(N);
        for(int i=0;i<N;i++)if(maxEdge[i].from!=-1)ret[maxEdge[i].from].push_back(maxEdge[i]);
        return ret;
    }

    vector<int>newIndex(N);
    for(int i=0;i<N;i++)newIndex[i]=(i?newIndex[i-1]:-1)+(isInC[i]==0);
    int n=newIndex[N-1]+2;
    Graph g(n);
    Edge minC(-1,-1,LLONG_MAX);
    for(int i=0;i<N;i++){
        if(isInC[i]){
            if(minC.cost>maxEdge[i].cost)minC=maxEdge[i];
            newIndex[i]=n-1;
        }
    }
    for(int v=0;v<N;v++)for(auto &e:G[v]){
        int u=e.to;
        if(isInC[v]&&isInC[u])continue;
        if(!isInC[v]&&isInC[u]){
            g[newIndex[v]].push_back(Edge(newIndex[v],newIndex[u],e.cost+minC.cost-maxEdge[u].cost,&e));
        }
        else{
            g[newIndex[v]].push_back(Edge(newIndex[v],newIndex[u],e.cost,&e));
        }
    }
    g=maximumWeightBranching(g);
    if(g.size()==0)return Graph();

    Graph ret(N);
    for(int v=0;v<n;v++){
        for(auto &e:g[v]){
            if(v!=n-1&&e.to==n-1)minC=maxEdge[e.prevEdge->to];
            ret[e.prevEdge->from].push_back(*e.prevEdge);
        }
    }

    for(int i=0;i<N;i++)if(isInC[i]&&maxEdge[i].to!=minC.to)ret[maxEdge[i].from].push_back(maxEdge[i]);
    return ret;
}

int maximumWeightBranching(vector<int>x,vector<int>y,vector<int>z){
    int n=max(*max_element(x.begin(),x.end()),*max_element(y.begin(),y.end()))+1;
    Graph g(n);
    for(int i=0;i<x.size();i++)g[x[i]].push_back(Edge(x[i],y[i],z[i]));
    g=maximumWeightBranching(g);
    if(g.size()==0)return -1;
    int ret=0;
    for(int i=0;i<n;i++)for(auto &e:g[i])ret+=e.cost;
    return ret;
}

int minimumWeightArborescence(vector<int>x,vector<int>y,vector<int>z){
    int n=max(*max_element(x.begin(),x.end()),*max_element(y.begin(),y.end()))+1;

    int k=0;
    for(int i=0;i<z.size();i++)k+=abs(z[i]);
    k=2*k+1;

    for(int i=0;i<z.size();i++)z[i]=k-z[i];
    int ret=maximumWeightBranching(x,y,z);
    if(ret==-1)return -1;
    return k*(n-1)-ret;
}

int minimumWeightRootedArborescence(vector<int>x,vector<int>y,vector<int>z,int r){
    int s=max(*max_element(x.begin(),x.end()),*max_element(y.begin(),y.end()))+1;
    x.push_back(s);y.push_back(r);z.push_back(0);
    return minimumWeightArborescence(x,y,z);
}
}