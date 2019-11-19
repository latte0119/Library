struct AhoCorasick{
	struct Node{
		map<char,int>nex;
		int failink;
		vector<int>suflist;
		bool match;
		int len;
		Node():failink(0),match(0),len(0){}
	};
	vector<Node>nds;
	AhoCorasick(){
		nds.emplace_back();
		nds[0].failink=-1;
	}

	int process(int k,int c){
		while(k!=-1&&nds[k].nex.find(c)==nds[k].nex.end())k=nds[k].failink;
		if(k==-1)return 0;
		return nds[k].nex[c];
	}

	void add(const string &s,int id){
		int k=0;
		for(auto c:s){
			if(nds[k].nex.find(c)==nds[k].nex.end()){
				nds[k].nex[c]=nds.size();
				nds.emplace_back();
				nds.back().len=nds[k].len+1;
			}
			k=nds[k].nex[c];
		}
		nds[k].suflist.push_back(id);
		nds[k].match=true;
	}

	void build(){
		queue<int>que;
		for(auto &p:nds[0].nex)que.push(p.second);
		while(que.size()){
			int k=que.front();
			que.pop();
			for(auto &p:nds[k].nex){
				char c=p.first;
				int nx=p.second;
				nds[nx].failink=process(nds[k].failink,c);

				vector<int>&curlist=nds[nds[nx].failink].suflist;
				vector<int>&nexlist=nds[nx].suflist;

				nexlist.insert(nexlist.end(),curlist.begin(),curlist.end());
				que.push(nx);
			}
		}
	}
};