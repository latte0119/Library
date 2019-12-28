struct UnionFindTree{
    vector<int32_t>par,sz;
    UnionFindTree(int32_t n=0):par(n),sz(n){
        for(int32_t i=0;i<n;i++){
            par[i]=i;
            sz[i]=1;
        }
    }
    int32_t find(int32_t x){
        return x==par[x]?x:par[x]=find(par[x]);
    }
    void unite(int32_t x,int32_t y){
        x=find(x);y=find(y);
        if(x==y)return;
        if(sz[x]<sz[y])swap(x,y);
        sz[x]+=sz[y];
        par[y]=x;
    }
    bool same(int32_t x,int32_t y){
        return find(x)==find(y);
    }
    int32_t size(int32_t x){
        return sz[find(x)];
    }
};