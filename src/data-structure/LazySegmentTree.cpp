template<class T,class E,class F,class G,class H>
struct LazySegmentTree{
	F f;
	G g;
	H h;

	T ti;
	E ei;

	vector<T>dat;
	vector<E>put;
	int sz;
	LazySegmentTree(const T &ti,const E &ei,const F &f,const G &g,const H &h):ti(ti),ei(ei),f(f),g(g),h(h){}

	void build(const vector<T>&v){
		assert(v.size());
		sz=1;
		while(sz<v.size())sz<<=1;
		dat.resize(sz<<1,ti);
		put.resize(sz<<1,ei);
		for(int i=0;i<v.size();i++)dat[sz-1+i]=v[i];
		for(int i=sz-2;i>=0;i--)dat[i]=f(dat[i*2+1],dat[i*2+2]);
	}
	inline void push(int k,int l,int r){
		dat[k]=g(dat[k],put[k],r-l);
		if(k<sz-1){
			put[k*2+1]=h(put[k*2+1],put[k]);
			put[k*2+2]=h(put[k*2+2],put[k]);
		}
		put[k]=ei;
	}

	void modify(int a,int b,E x,int k,int l,int r){
		push(k,l,r);
		if(r<=a||b<=l)return;
		if(a<=l&&r<=b){
			put[k]=x;
			push(k,l,r);
			return;
		}
		modify(a,b,x,k*2+1,l,(l+r)/2);
		modify(a,b,x,k*2+2,(l+r)/2,r);
		dat[k]=f(dat[k*2+1],dat[k*2+2]);
	}

	inline void modify(int a,int b,E x){
		return modify(a,b,x,0,0,sz);
	}
	T query(int a,int b,int k,int l,int r){
		push(k,l,r);
		if(r<=a||b<=l)return ti;
		if(a<=l&&r<=b)return dat[k];
		return f(query(a,b,k*2+1,l,(l+r)/2),query(a,b,k*2+2,(l+r)/2,r));
	}
	inline T query(int a,int b){
		return query(a,b,0,0,sz);
	}
};