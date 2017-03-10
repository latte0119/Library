
int par[SIZE],dep[SIZE],hev[SIZE],pos[SIZE],head[SIZE],sz[SIZE];
segtree seg;

void dfs(){
    vint vs={0};
    par[0]=-1;
    dep[0]=0;
    rep(i,N){
        int v=vs[i];
        for(auto u:G[v]){
            if(u==par[v])continue;
            par[u]=v;
            dep[u]=dep[v]+1;
            vs.pb(u);
        }
    }

    for(int i=vs.size()-1;i>=0;i--){
        int v=vs[i];
        sz[v]=1;
        hev[v]=-1;
        int ma=0;
        for(auto u:G[v]){
            if(u==par[v])continue;
            if(ma<sz[u]){
                ma=sz[u];
                hev[v]=u;
            }
            sz[v]+=sz[u];
        }
    }
}


void init(){
    dfs();
    int idx=0;
    rep(i,N){
        if(~par[i]&&hev[par[i]]==i)continue;
        for(int j=i;~j;j=hev[j]){
            head[j]=i;
            pos[j]=idx++;
        }
    }

    /*
        ここでseg木を更新
    */
}

//これはクエリ処理の例
void query1(int a,int b,int c){
    while(head[a]!=head[b]){
        if(dep[head[a]]<dep[head[b]])swap(a,b);
        seg.update(pos[head[a]],pos[a]+1,c);
        a=par[head[a]];
    }
    if(dep[a]>dep[b])swap(a,b);
    seg.update(pos[a],pos[b]+1,c);
}
