
struct PalindromicTree{
    struct node{
    map<char,int>nex;
        int len,suflink,height,firapp;
        //length,suffix link,height,first appearance
    };

    string s;
    vector<node>v;
    vector<int>ord;
    int n,suf;

    bool add(int pos){
        char ch=s[pos];
        int cur=suf;
        while(true){
            if(pos-1-v[cur].len>=0&&s[pos-1-v[cur].len]==ch)break;
            cur=v[cur].suflink;
        }

        if(v[cur].nex.count(ch)){
            suf=v[cur].nex[ch];
            return false;
        }

        suf=n++;

        v[suf].len=v[cur].len+2;
        v[suf].firapp=pos;
        v[cur].nex[ch]=suf;

        if(v[suf].len==1){
            v[suf].suflink=1;
            v[suf].height=1;
            return true;
        }

        while(true){
            cur=v[cur].suflink;
            if(pos-1-v[cur].len>=0&&s[pos-1-v[cur].len]==ch){
                v[suf].suflink=v[cur].nex[ch];
                break;
            }
        }
        v[suf].height=1+v[v[suf].suflink].height;
        return true;
    }

    void init(const string &s){
        this->s=s;
        v.clear();
        v.resize(s.size()+10);

        n=2;
        suf=1;
        v[0].firapp=v[1].firapp=-1;
        v[0].len=-1;
        v[1].len=0;
        v[0].suflink=v[1].suflink=0;
        v[0].height=v[1].height=0;
    }

    void calcOrd(){
        ord={0,1};
        for(int i=0;i<ord.size();i++){
            for(auto &p:v[ord[i]].nex)ord.pb(p.se);
        }
    }

	int calcCnt(){
	    assert(ord.size());
	    for(int i=ord.size()-1;i>=0;i--){
            v[v[ord[i]].suflink].cnt+=v[ord[i]].cnt;
	    }
	    v[0].cnt=v[1].cnt=0;
	}
};
