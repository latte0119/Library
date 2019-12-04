struct FastLCA{
    template<class T>
    struct SparseTable{
        vector<vector<T>>st;
        void init(const vector<T>&vec){
            int32_t b;
            for(b=0;(1<<b)<=vec.size();b++);
            st.assign(b,vector<T>(1<<b));
            for(int32_t i=0;i<vec.size();i++)st[0][i]=vec[i];

            for(int32_t i=1;i<b;i++){
                for(int32_t j=0;j+(1<<i)<=(1<<b);j++){
                    st[i][j]=min(st[i-1][j],st[i-1][j+(1<<(i-1))]);
                }
            }
        }
        T getMin(int32_t l,int32_t r){
            assert(l<r);
            int32_t b=32-__builtin_clz(r-l)-1;
            return min(st[b][l],st[b][r-(1<<b)]);
        }
    };
    SparseTable<pair<int32_t,int32_t>>st;

    vector<vector<int32_t>>G;
    int32_t V;
    int32_t root;
    vector<int32_t>ord;
    FastLCA(int32_t v=0,int32_t r=0):V(v),root(r),G(v),ord(v){}

    void set(int32_t v){
        *this=FastLCA(v);
    }

    void addEdge(int32_t a,int32_t b){
        G[a].push_back(b);
        G[b].push_back(a);
    }

    void dfs(int32_t v,int32_t p,int32_t d,vector<pair<int32_t,int32_t>>&vs){
        ord[v]=vs.size();
        vs.emplace_back(d,v);

        for(auto u:G[v]){
            if(u==p)continue;
            dfs(u,v,d+1,vs);
            vs.emplace_back(d,v);
        }
    }

    void init(){
        vector<pair<int32_t,int32_t>>vs;
        dfs(root,-1,0,vs);
        st.init(vs);
    }

    inline int32_t operator()(int32_t a,int32_t b){
        if(ord[a]>ord[b])swap(a,b);
        return st.getMin(ord[a],ord[b]+1).second;
    }
};