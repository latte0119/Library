template<class T,class F>
struct SegmentTree{
    const F f;
    const T ti;
    vector<T>dat;
    int32_t sz;
    SegmentTree(const T &ti,const F &f):ti(ti),f(f){}
    void build(const vector<T>&v){
        assert(v.size());
        sz=1;
        while(sz<v.size())sz<<=1;
        dat.resize(sz<<1,ti);
        for(int32_t i=0;i<v.size();i++)dat[sz-1+i]=v[i];
        for(int32_t i=sz-2;i>=0;i--)dat[i]=f(dat[i*2+1],dat[i*2+2]);
    }

    inline void update(int32_t k,const T &x){
        k+=sz-1;
        dat[k]=x;
        while(k){
            k=(k-1)>>1;
            dat[k]=f(dat[k*2+1],dat[k*2+2]);
        }
    }

    inline void add(int32_t k,const T &x){
        k+=sz-1;
        dat[k]=f(dat[k],x);
        while(k){
            k=(k-1)>>1;
            dat[k]=f(dat[k*2+1],dat[k*2+2]);
        }
    }

    inline T query(int32_t a,int32_t b){
        return query(a,b,0,0,sz);
    }
    T query(int32_t a,int32_t b,int32_t k,int32_t l,int32_t r){
        if(r<=a||b<=l)return ti;
        if(a<=l&&r<=b)return dat[k];
        return f(query(a,b,k*2+1,l,(l+r)>>1),query(a,b,k*2+2,(l+r)>>1,r));
    }
};