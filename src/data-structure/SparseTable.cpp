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