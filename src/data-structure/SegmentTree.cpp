template<class T,class F>
struct SegmentTree{
	F f;
	T ti;
	vector<T>dat;
	int sz;
	SegmentTree(const F &f,const T &ti):f(f),ti(ti){}
	void build(const vector<T>&v){
		assert(v.size());
		sz=1;
		while(sz<v.size())sz<<=1;
		dat.resize(sz<<1,ti);
		for(int i=0;i<v.size();i++)dat[sz-1+i]=v[i];
		for(int i=sz-2;i>=0;i--)dat[i]=f(dat[i*2+1],dat[i*2+2]);
	}

	inline void update(int k,T x){
		k+=sz-1;
		dat[k]=x;
		while(k){
			k=(k-1)/2;
			dat[k]=f(dat[k*2+1],dat[k*2+2]);
		}
	}

	inline void add(int k,int x){
		k+=sz-1;
		dat[k]=f(dat[k],x);
		while(k){
			k=(k-1)/2;
			dat[k]=f(dat[k*2+1],dat[k*2+2]);
		}
	}

	inline T query(int a,int b){
		return query(a,b,0,0,sz);
	}
	T query(int a,int b,int k,int l,int r){
		if(r<=a||b<=l)return ti;
		if(a<=l&&r<=b)return dat[k];
		return f(query(a,b,k*2+1,l,(l+r)/2),query(a,b,k*2+2,(l+r)/2,r));
	}
};
