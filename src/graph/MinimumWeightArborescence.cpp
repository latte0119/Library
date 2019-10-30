struct MminimumWeightArborescence{
	using W=long long;
	using E=pair<W,int>;

	struct EHeap{
  		struct Node{
			E e; 
			W put;
			Node *l,*r;
			Node(E e):e(e),put(0),l(nullptr),r(nullptr){}
			Node* push(){
				e.first+=put;
				if(l)l->put+=put;
				if(r)r->put+=put;
				put=0;
				return this;
			}
		};
		Node* merge(Node *a,Node *b){
			if(!a)return b;
			if(!b)return a;
			a->push();b->push();
			if(a->e>b->e)swap(a,b);
			a->r=merge(a->r,b);
			swap(a->l,a->r);
			return a;
		}

		Node* root;
		EHeap():root(nullptr){}
		void pop(){
			root->push();
			root=merge(root->l,root->r);
		}
		void push(E e){
			Node *p=new Node(e);
			root=merge(root,p);
		}
		void add(W a){
			if(root)root->put+=a;
		}
		E top(){
			return root->push()->e;
		}
		void meld(EHeap &eh){
			root=merge(root,eh.root);
		}
	};

	int n;
	vector<vector<E>>G;
	MinimumWeightArborescence(int n):n(n),G(n){
	}

	void addEdge(int a,int b,W c){
		G[a].emplace_back(c,b);
	}

	W calc(int r){
		vector<int>par(n);iota(par.begin(),par.end(),0);
		function<int(int)>find=[&](int x){return x==par[x]?x:par[x]=find(par[x]);};
		
		vector<int>st(n);
		vector<EHeap>eh(n);
		
		for(int v=0;v<n;v++)for(auto &e:G[v])eh[e.second].push(E(e.first,v));
		
		st[r]=2;
		W ans=0;
		for(int i=0;i<n;i++){
			if(st[i])continue;
			int v=i;
			vector<E>es;
			
			while(st[v]!=2){
				st[v]=1;
				int u;W c;
				tie(c,u)=eh[v].top();eh[v].pop();
				u=find(u);
				if(u==v)continue;
				ans+=c;
				if(st[u]!=1){
					es.push_back(E(c,v));
					v=u;
					continue;
				}

				eh[v].add(-c);
				while(v!=u){
					int w;
					tie(c,w)=es.back();es.pop_back();
					eh[w].add(-c);
					eh[w].meld(eh[v]);	
					par[v]=u;
					v=w;
				}
			}
			for(auto &e:es)st[e.second]=2;
		}
		return ans;
	}
};