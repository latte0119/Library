struct MergingSegmentTree{
    static const int LG=18;
    static const int SEG=1<<LG;
    static const int OP=SEG;
    static const int SZ=OP*LG+1;

    int tail;
    int ch[SZ][2];
    int sz[SZ];
    
    MergingSegmentTree():tail(1){
		memset(ch,0,sizeof(ch));
		memset(sz,0,sizeof(sz));
	}

    int build(int val,int l=0,int r=SEG){
        int k=tail++;
        sz[k]=1;

        if(l+1==r)return k;

        int m=(l+r)>>1;
        if(val<m){
            ch[k][0]=bulid(val,l,m);
        }
        else{
            ch[k][1]=build(val,m,r);
        }
        return k;
    }
    int split(int t1,int k){
        int t2=tail++;
        if(k>ls)ch[t2][1]=split(ch[t1][1],k-ls);
        else swap(ch[t1][1],ch[t2][1]);
        if(k<ls)ch[t2][0]=split(ch[t1][0],k);
        sz[t2]=sz[t1]-k;sz[t1]=k;
        return t2;
    }
    int merge(int t1,int t2){
        if(t1&&t2);else return t1^t2;
        ch[t1][0]=merge(ch[t1][0],ch[t2][0]);
        ch[t1][1]=merge(ch[t1][1],ch[t2][1]);
        sz[t1]+=sz[t2];
        return t1;
    }
}

/*
TLE's blog:
http://codeforces.com/blog/entry/49446
*/