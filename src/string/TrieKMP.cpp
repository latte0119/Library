/*
mp: s[0:i+1]
kmp: s[0:i]
*/
template<class C>
struct TrieKMP{
	struct Node{
		map<C,int>nex;
		int len,par,mp,kmp;
		Node():len(0),par(-1),mp(-1),kmp(-1){}
	};

	vector<Node>nds;
	TrieKMP(){
		nds.emplace_back();
	}
	inline int addChar(int k,C c){
		if(nds[k].nex.find(c)==nds[k].nex.end()){
			nds[k].nex[c]=nds.size();
			nds.emplace_back();
			nds.back().len=nds[k].len+1;
			nds.back().par=k;
		}
		return nds[k].nex[c];
	}

	template<class T>
	int add(int k,const T &S){
		int cur=0;
		for(C &c:S)cur=addChar(cur,c);
		return cur;
	}

	void build(){
		vector<int>vs;
		vector<C>S;
		dfs(0,vs,S);
	}

	void dfs(int v,vector<int>&vs,vector<C>&S){
		for(auto &e:nds[v].nex) {
			int u=e.second;
			C c=e.first;
			vs.push_back(u);
			S.push_back(c);
			
			//mp O(logN) step
			int j=nds[v].mp;
			while(j!=-1&&S.back()!=S[j])j=nds[vs[j]].kmp;
			nds[u].mp = j+1;
			
			//kmp
			j=nds[v].mp;
			if(j!=-1&&S.back()==S[j])nds[u].kmp=nds[vs[j]].kmp;
			else nds[u].kmp=j;

			dfs(u,vs,S);
			vs.pop_back(); 
			S.pop_back();
		}
	}

	int size(){return nds.size();}
	Node& operator[](int k){return nds[k];}
};