// (t,l,r)  r-l>=2*t
template<class T>
struct EnumerateRuns{
	vector<int>zalgo(const T &s){
		vector<int>z(s.size());
		z[0]=s.size();
		int i=1,j=0;
		while(i<s.size()){
			while(i+j<s.size()&&s[j]==s[i+j])j++;
			z[i]=j;
			if(j==0){i++;continue;}
			int k=1;
			while(i+k<s.size()&&k+z[k]<j)z[i+k]=z[k],k++;
			i+=k;j-=k;
		}
		return z;
	}
	
	T S;
	EnumerateRuns(const T &s):S(s){}

	T substr(int l,int r){return {S.begin()+l,S.begin()+r};}
	T rev(T s){reverse(s.begin(),s.end());return s;}
	T concat(T a,T b){a.insert(a.end(),b.begin(),b.end());return a;}

	map<pair<int,int>,int>mp;
	void solve(int l,int r,int f){
		if(r-l==1)return;
		int m=(l+r+f)/2;
		solve(l,m,f);solve(m,r,f);
		
		auto zl=zalgo(rev(substr(l,m)));
		auto zr=zalgo(concat(substr(m,r),substr(l,r)));
		for(int p=1;p<=m-l;p++){
			int lenl=(p<m-l?zl[p]:0);
			int lenr=zr[r-l-p];
			int ll=m-p-lenl;
			int rr=min(m+lenr,r);
			if(rr-ll<2*p)continue;
			if(ll&&S[ll-1+p]==S[ll-1])continue;
			if(rr<S.size()&&S[rr]==S[rr-p])continue;
			if(f)tie(ll,rr)=pint(S.size()-rr,S.size()-ll);
			pint I(ll,rr);
			if(!mp.count(I)||mp[I]>p)mp[I]=p;
		}
	}

	vector<tuple<int,int,int>>calc(){
		for(int i=0;i<2;i++){
			solve(0,S.size(),i);
			reverse(S.begin(),S.end());
		}

		vector<tuple<int,int,int>>runs;
		for(auto &p:mp){
			int t=p.second;
			int l,r;tie(l,r)=p.first;
			runs.emplace_back(t,l,r);
		}
		return runs;
	}
};