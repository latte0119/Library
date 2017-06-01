struct CHT{
    deque<pair<int,int>>ls;
    inline bool check(const pair<int,int>&a,const pair<int,int>&b,const pair<int,int>&c){
        return (b.fi-a.fi)*(c.se-b.se)>=(b.se-a.se)*(c.fi-b.fi);
    }
    void add(int a,int b){
        pair<int,int>l(a,b);
        while(ls.size()>=2&&check(ls[ls.size()-2],ls[ls.size()-1],l))ls.pop_back();
        ls.push_back(l);
    }
    int query(int x){
        assert(ls.size());
        while(ls.size()>1&&ls[0].fi*x+ls[0].se>=ls[1].fi*x+ls[1].se)ls.pop_front();
        return ls[0].fi*x+ls[0].se;
    }
};
