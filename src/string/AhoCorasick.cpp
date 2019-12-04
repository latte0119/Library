template<class C>
struct AhoCorasick{
	struct Node{
		map<C,int>nex;
		int failink;
		int len;
		Node():failink(0),len(0){}
	};
	vector<Node>nds;
	AhoCorasick(){
		nds.emplace_back();
		nds[0].failink=-1;
	}

	int process(int k,const C &c){
        if(k==-1)return 0;
        if(nds[k].nex.find(c)!=nds[k].nex.end())return nds[k].nex[c];
		return nds[k].nex[c]=process(nds[k].failink,c);
	}

    inline int addChar(int k,const C &c){
        if(nds[k].nex.find(c)==nds[k].nex.end()){
            nds[k].nex[c]=nds.size();
            nds.emplace_back();
            nds.back().len=nds[k].len+1;
        }
        return nds[k].nex[c];
    }

    template<class T>
	int addString(const T &s){
		int k=0;
        for(const C& c:s)k=addChar(k,c);
        return k;
	}

	void build(){
		queue<int>que;
		for(auto &p:nds[0].nex)que.push(p.second);
		while(que.size()){
			int k=que.front();
			que.pop();
			for(auto &p:nds[k].nex){
				C c=p.first;
				int nx=p.second;
				nds[nx].failink=process(nds[k].failink,c);
				que.push(nx);
			}
		}
	}
};