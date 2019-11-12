struct EdgeColoringOfBipartiteGraph{
	int N;
	vector<int>X,Y;
	
	int M;
	EdgeColoringOfBipartiteGraph(int n,vector<int>&x,vector<int>&y):N(n),X(x),Y(y){}

	void swapColor(int v,int cx,int cy,vector<vector<int>>&col){
		if(col[v][cx]!=-1){
			swapColor(col[v][cx],cy,cx,col);
		}
		swap(col[v][cx],col[v][cy]);
	}
	vector<int>coloring(){
		int M=X.size();
		vector<int>deg(N);
		for(int i=0;i<M;i++){
			deg[X[i]]++;
			deg[Y[i]]++;
		}
		int D=*max_element(deg.begin(),deg.end());
		vector<vector<int>>col(N,vector<int>(D,-1));

		for(int e=0;e<M;e++){
			int x=X[e];
			int y=Y[e];

			bool ok=false;
			for(int i=0;i<D;i++){
				if(col[x][i]==-1&&col[y][i]==-1){
					ok=true;
					col[x][i]=y;
					col[y][i]=x;
					break;
				}
			}
			if(ok)continue;

			int cx,cy;
			rep(i,D){
				if(col[y][i]==-1)cx=i;
				if(col[x][i]==-1)cy=i;
			}
			swapColor(x,cx,cy,col);
			col[x][cx]=y;
			col[y][cx]=x;
		}

		vector<int>ans(M);
		for(int i=0;i<M;i++){
			for(int j=0;j<D;j++)if(col[X[i]][j]==Y[i])ans[i]=j;
		}
		return ans;
	}
};


/*
https://codeforces.com/contest/600/problem/F

*/