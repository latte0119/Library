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

	int process(char c,int cur=-1){
		if(cur==-1){
			cur=last;
		}

		if(st[cur].nex.count(c)){
			int q=st[cur].nex[c];
			if(st[q].len==st[cur].len+1){
				return last=q;
			}
			int clone=st.size();
			st.push_back(st[q]);
			st[clone].len=st[q].len+1;
			st[q].link=clone;
			while(cur!=-1&&st[cur].nex[c]==q){
				st[cur].nex[c]=clone;
				cur=st[cur].link;
			}
			return last=clone;
		}

		int nex=st.size();
		st.emplace_back(st[cur].len+1,0);
		int p=cur;
		while(p!=-1&&!st[p].nex.count(c)){
			st[p].nex[c]=nex;
			p=st[p].link;
		}
		if(p==-1){
			return last=nex;
		}

		int q=st[p].nex[c];
		if(st[p].len+1==st[q].len){
			st[nex].link=q;	
		}
		else{
			int clone=st.size();
			st.push_back(st[q]);
			st[clone].len=st[p].len+1;

			st[q].link=st[nex].link=clone;
			while(p!=-1&&st[p].nex[c]==q){
				st[p].nex[c]=clone;
				p=st[p].link;
			}
		}
		return last=nex;
	}

	
	vector<int>calcTopologicalOrder(){
		vector<int>ord;
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
		return ord;
	}

	vector<int>calcTreeOrder(){
		vector<int>ord;

		vector<vector<int>>G(st.size());
		for(int i=1;i<st.size();i++)G[st[i].link].push_back(i);
		queue<int>que;
		que.push(0);
		while(que.size()){
			int v=que.front();
			que.pop();
			ord.push_back(v);
			for(auto u:G[v])que.push(u);
		}
		return ord;
	}
	/*
	long long countDistinctSubstrings(){
		auto ord=calcTopologicalOrder();
		vector<int>dp(st.size());dp[0]=1;
		for(auto id:ord){
			for(auto &p:st[id].nex)dp[p.se]+=dp[id];
		}
		return accumulate(all(dp),0ll)-1;
	}
	*/
};
