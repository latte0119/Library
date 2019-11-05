struct SuffixAutomaton{
	struct State{
		int len,link;
		map<char,int>nex;
		State(int len,int link):len(len),link(link){}
	};

	vector<State>st;
	int last;

	SuffixAutomaton():last(0){
		st.emplace_back(0,-1);
	}

	void process(char c){
		int cur=st.size();
		st.emplace_back(st[last].len+1,0);
		int p=last;
		while(p!=-1&&!st[p].nex.count(c)){
			st[p].nex[c]=cur;
			p=st[p].link;
		}
		if(p!=-1){
			int q=st[p].nex[c];
			if(st[p].len+1==st[q].len){
				st[cur].link=q;
			}
			else{
				int clone=st.size();
				st.push_back(st[q]);
				st[clone].len=st[p].len+1;
				
				st[q].link=st[cur].link=clone;

				while(p!=-1&&st[p].nex[c]==q){
					st[p].nex[c]=clone;
					p=st[p].link;
				}
			}
		}
		last=cur;
	}

	
	vector<int>ord;
	void calcTopologicalOrder(){
		ord.clear();
		vector<int>deg(st.size());
		for(int i=0;i<st.size();i++){
			for(auto &p:st[i].nex)deg[p.second]++;
		}
		queue<int>que;
		que.push(0);
		while(que.size()){
			int v=que.front();
			que.pop();
			ord.push_back(v);
			for(auto &p:st[v].nex){
				if(--deg[p.second]==0)que.push(p.second);
			}
		}
	}
	long long countDistinctSubstrings(){
		calcTopologicalOrder();
		vector<int>dp(st.size());dp[0]=1;
		for(auto id:ord){
			for(auto &p:st[id].nex)dp[p.se]+=dp[id];
		}
		return accumulate(all(dp),0ll)-1;
	}
};