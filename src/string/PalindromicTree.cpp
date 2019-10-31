/*
p->xpx  :  node(p).nex[x]=node_id(xpx)        (enlarge link)
aabaa->aa :  node(aabaa).suflink=node_id(aa)    (suffix link)
sufs[i] : node_id(longest suffix-palindrome of s[0,i])
*/
struct PalindromicTree{
    struct Node{
    	map<char,int>nex;
        int len,suflink,cnt;
		Node(int len,int suflink,int cnt)
			:len(len),suflink(suflink),cnt(cnt){}
    };

    string s;
    vector<Node>v;
	vector<int>sufs;
	int pos,suf;

	PalindromicTree():pos(0),suf(1){
		v.emplace_back(-1,0,0);
		v.emplace_back(0,0,0);
    }

	void add(const string &t){
		s+=t;
	}

    void uku(){
		assert(pos<s.size());
        char ch=s[pos];
        int cur=suf;
        while(true){
            if(pos-1-v[cur].len>=0&&s[pos-1-v[cur].len]==ch)break;
            cur=v[cur].suflink;
        }

        if(v[cur].nex.count(ch)){
            suf=v[cur].nex[ch];
            v[suf].cnt++;
		    return;
        }

        suf=v.size();
		v.emplace_back(v[cur].len+2,-1,1);
        v[cur].nex[ch]=suf;

        if(v[suf].len==1){
            v[suf].suflink=1;
            return;
        }

        while(true){
            cur=v[cur].suflink;
            if(pos-1-v[cur].len>=0&&s[pos-1-v[cur].len]==ch){
                v[suf].suflink=v[cur].nex[ch];
				return;
            }
        }
    }

	void process(){
		uku();
		pos++;
		sufs.push_back(suf);
	}
};