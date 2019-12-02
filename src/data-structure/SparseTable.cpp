template<class T>
    struct sparse_table{
        vector<vector<T>>st;
        void init(const vector<T>&vec){
            int b;
            for(b=0;(1<<b)<=vec.size();b++);
            st.assign(b,vector<T>(1<<b));
            for(int i=0;i<vec.size();i++)st[0][i]=vec[i];

            for(int i=1;i<b;i++){
                for(int j=0;j+(1<<i)<=(1<<b);j++){
                    st[i][j]=min(st[i-1][j],st[i-1][j+(1<<(i-1))]);
                }
            }
        }
        T get_min(int l,int r){
            assert(l<r);
            int b=32-__builtin_clz(r-l)-1;
            return min(st[b][l],st[b][r-(1<<b)]);
        }
    };