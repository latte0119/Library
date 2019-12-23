template<class C>
struct AhoCorasick{
	struct Node{
		map<C,int>nex;
		int link;
		int len;
		int par;
		Node():link(0),len(0),par(0){}
	};
	vector<Node>nds;
	AhoCorasick(){
		nds.emplace_back();
		nds[0].link=-1;
		nds[0].par=-1;
	}

	int process(int k,const C &c){
		while(k!=-1&&nds[k].nex.find(c)==nds[k].nex.end())k=nds[k].link;
        if(k==-1)return 0;
        return nds[k].nex[c];
	}

    inline int addChar(int k,const C &c){
        if(nds[k].nex.find(c)==nds[k].nex.end()){
            nds[k].nex[c]=nds.size();
            nds.emplace_back();
            nds.back().len=nds[k].len+1;
			nds.back().par=k;
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
				nds[nx].link=process(nds[k].link,c);
				que.push(nx);
			}
		}
	}

	Node& operator[](int k){return nds[k];}
	inline int size(){return nds.size();}
};