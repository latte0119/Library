template<int lg>
struct LazySegmentTree{
	using T=int;
	inline T op(const T &a,const T &b){
		return max(a,b);
	}
	const T E=-1001001001;

	vector<T>dat,put;
	LazySegmentTree():dat(1<<lg+1),put(1<<lg+1){}
	inline void push(int k,int l,int r){
		dat[k]+=put[k];
		if(k<(1<<lg)-1){
			put[k*2+1]+=put[k];
			put[k*2+2]+=put[k];
		}
		put[k]=0;
	}


	void update(int a,int b,T x,int k=0,int l=0,int r=1<<lg){
		push(k,l,r);
		if(r<=a||b<=l)return;
		if(a<=l&&r<=b){
			put[k]=x;
			push(k,l,r);
			return;
		}
		update(a,b,x,k*2+1,l,(l+r)/2);
		update(a,b,x,k*2+2,(l+r)/2,r);
		dat[k]=op(dat[k*2+1],dat[k*2+2]);
	}
	T query(int a,int b,int k=0,int l=0,int r=1<<lg){
		push(k,l,r);
		if(r<=a||b<=l)return E;
		if(a<=l&&r<=b)return dat[k];
		return op(query(a,b,k*2+1,l,(l+r)/2),query(a,b,k*2+2,(l+r)/2,r));
	}
};
