namespace SCC{
    void visit(const vector<vector<int>>&G,vector<int>&vs,vector<int>&used,int v){
        used[v]=true;
        for(auto u:G[v]){
            if(!used[u])visit(G,vs,used,u);
        }
        vs.push_back(v);
    }

    void visit2(const vector<vector<int>>&T,vector<int>&used,vector<int>&comp,vector<int>&vec,int k,int v){
        comp[v]=k;
        used[v]=true;
        vec.push_back(v);

        for(auto u:T[v]){
            if(!used[u])visit2(T,used,comp,vec,k,u);
        }
    }

    //G:‹­˜AŒ‹¬•ª•ª‰ð‚µ‚½‚¢ƒOƒ‰ƒt
    //H:‹­˜AŒ‹¬•ª‚ð’×‚µ‚Ä1‚Â‚Ì’¸“_‚Ék–ñ‚µ‚½ƒOƒ‰ƒt
    //comp:G‚ÌŠe’¸“_‚ªA‚Ç‚ÌH‚Ì’¸“_‚É‘®‚µ‚Ä‚¢‚é‚©
    void decompose(const vector<vector<int>>&G,vector<vector<int>>&H,vector<int>&comp){
        vector<vector<int>>T(G.size());
        for(int i=0;i<G.size();i++){
            for(auto v:G[i]){
                T[v].push_back(i);
            }
        }
        comp.resize(G.size());

        vector<int>vs(G.size());
        vector<int>used(G.size());
        for(int i=0;i<G.size();i++){
            if(!used[i])visit(G,vs,used,i);
        }
        reverse(vs.begin(),vs.end());
        fill(used.begin(),used.end(),0);

        int K=0;
        vector<vector<int>>S;
        for(auto v:vs){
            if(!used[v]){
                S.push_back(vector<int>());
                visit2(T,used,comp,S.back(),K++,v);
            }
        }

        H.resize(K);
        fill(used.begin(),used.end(),0);
        for(int i=0;i<K;i++){
            for(auto v:S[i]){
                for(auto u:G[v]){
                    if(used[comp[u]]||comp[v]==comp[u])continue;
                    used[comp[u]]=true;
                    H[comp[v]].push_back(comp[u]);
                }
            }
            for(auto v:H[i])used[v]=false;
        }

    }
}
