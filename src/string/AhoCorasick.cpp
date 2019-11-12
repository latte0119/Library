/*
symbol : !"#$%&'()*+,-./
digit : 0~9
symbol2 : :;<=>?@
upper : A~Z
symbol3 : [\]^_`
lower : a~z	
synbol4 : {|}~

don't forget!!!!  :  build  
*/
struct AhoCorasick{
	//  c \in [OFF,OFF+LEN)
	static const int OFF=(int)('a');
	static const int SUP=(int)('z');
	static const int LEN=SUP-OFF+1;
	
	struct Node{
		int nex[LEN];
		int failink;
		vector<int>suflist;
		Node():failink(0){memset(nex,-1,sizeof(nex));}
	};
	vector<Node>nds;

	AhoCorasick():nds(1){}

	int process(int k,int c){
		c-=OFF;
		while(nds[k].nex[c]==-1)k=nds[k].failink;
		return nds[k].nex[c];
	}

	void add(const string &s,int id){
		int k=0;
		for(auto c:s){
			c-=OFF;
			if(nds[k].nex[c]==-1){
				nds[k].nex[c]=nds.size();
				nds.emplace_back();
			}
			k=nds[k].nex[c];
		}
		nds[k].suflist.push_back(id);
	}

	void build(){
		queue<int>que;
		for(int i=0;i<LEN;i++){
			if(nds[0].nex[i]==-1)nds[0].nex[i]=0;
			else que.push(nds[0].nex[i]);
		}
		while(que.size()){
			int k=que.front();
			que.pop();
			for(int i=0;i<LEN;i++){
				if(nds[k].nex[i]==-1)continue;
				int nx=nds[k].nex[i];
				nds[nx].failink=process(nds[k].failink,i+OFF);

				vector<int>&curlist=nds[nds[nx].failink].suflist;
				vector<int>&nexlist=nds[nx].suflist;

				nexlist.insert(nexlist.end(),curlist.begin(),curlist.end());
				que.push(nx);
			}
		}
	}
};