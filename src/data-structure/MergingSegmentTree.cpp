struct MergingSegmentTree{
    static const int LG=18;
    static const int SEG=1<<LG;
    static const int OP=SEG;
    static const int SZ=OP*LG+1;

    int tail;
    vector<int>chl,chr,sz
    MergingSegmentTree():tail(1),chl(SZ),chr(SZ),sz(SZ){}

    int build(int val,int l=0,int r=SEG){
        int k=tail++;
        sz[k]=1;
        if(l+1==r)return k;

        int m=(l+r)>>1;
        if(val<m)chl[k]=build(val,l,m);
        else chr[k]=build(val,m,r);
        return k;
    }
    int split(int t1,int k){
        int t2=tail++;
        if(k>ls)chr[t2]=split(chr[t1],k-ls);
        else swap(chr[t1],chr[t2]);
        if(k<ls)chl[t2]=split(chl[t1],k);
        sz[t2]=sz[t1]-k;sz[t1]=k;
        return t2;
    }
    int merge(int t1,int t2,int l=0,int r=SEG){
        if(t1&&t2);else return t1^t2;
        sz[t1]+=sz[t2];
        if(l+1==r)return t1;
        
        int m=(l+r)>>1;
        
        chl[t1]=merge(chl[t1],chl[t2],l,m);
        chr[t1]=merge(chr[t1],chr[t2],m,r);
        return t1;
    }
};

/*
TLE's blog:
http://codeforces.com/blog/entry/49446
*/