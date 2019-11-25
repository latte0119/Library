namespace DSUOnTree{

	
	void dfs(int v,int p,bool keep){
		int hv=wt.heavy(v);
		for(auto &e:wt[v]){
			if(e.to!=p&&e.to!=hv)dfs(e.to,v,false);
		}

		if(hv!=-1)dfs(hv,v,true);
		add(v);
		for(auto &e:wt[v])if(e.to!=p&&e.to!=hv){
			for(int i=wt.tin(e.to);i<wt.tout(e.to);i++)add(wt.vs(i));
		}

		//calc
	
		if(!keep){
			for(int i=wt.tin(v);i<wt.tout(v);i++){
				int u=wt.vs(i);
                //delete
			}
		}
	}
	void solve(){
		dfs(0,-1,false);
	}
}


/*
https://codeforces.com/blog/entry/44351
*/