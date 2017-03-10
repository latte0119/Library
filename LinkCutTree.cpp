
/*
’¸“_‚ÉŽ‚½‚¹‚éî•ñ‚ÆA’x‰„XV‚Æ‚©‚Ì•”•ª‚ð–ˆ‰ñ‘‚«Š·‚¦‚é
*/

struct LinkCutTree{;
    struct Node{
        Node *lp,*rp,*pp;
        int cnt;
        bool rev;
        int val,put,agg;//‘‚«Š·‚¦‚é
        Node():lp(0),rp(0),pp(0),rev(0),cnt(1),put(0){}
        bool isRoot(){
            return !pp||(pp->lp!=this&&pp->rp!=this);
        }

        void push(){
            if(rev){
                swap(lp,rp);
                if(lp)lp->rev^=1;
                if(rp)rp->rev^=1;
                rev=0;
            }

            //‘‚«Š·‚¦‚é
            if(put){
                val=agg=0;
                if(lp)lp->put=1;
                if(rp)rp->put=1;
                put=0;
            }
        }

        //•K—vˆÈã‚Épush‚µ‚Ä‚é‚©‚à
        void pushAll(){
            if(!isRoot())pp->pushAll();
            push();
            if(lp)lp->push();
            if(rp)rp->push();
        }

        void update(){
            cnt=(lp?lp->cnt:0)+1+(rp?rp->cnt:0);

            //‘‚«Š·‚¦‚é
            agg=val;
            if(lp)agg+=lp->agg;
            if(rp)agg+=rp->agg;
        }

        void rotR(){
            Node *q=pp,*r=q->pp;
            if((q->lp=rp))rp->pp=q;
            rp=q;q->pp=this;
            if((pp=r)){
                if(r->lp==q)r->lp=this;
                if(r->rp==q)r->rp=this;
            }
            q->update();
            update();
        }

        void rotL(){
            Node *q=pp,*r=q->pp;
            if((q->rp=lp))lp->pp=q;
            lp=q;q->pp=this;
            if((pp=r)){
                if(r->lp==q)r->lp=this;
                if(r->rp==q)r->rp=this;
            }
            q->update();
            update();
        }


        void splay(){
            pushAll();
            while(!isRoot()){
                Node *q=pp;
                if(q->isRoot()){
                    if(q->lp==this)rotR();
                    else rotL();
                }
                else{
                    Node *r=q->pp;
                    if(r->lp==q){
                        if(q->lp==this){q->rotR();rotR();}
                        else {rotL();rotR();}
                    }
                    else{
                        if(q->rp==this){q->rotL();rotL();}
                        else{rotR();rotL();}
                    }
                }
            }
        }

        void expose(){
            Node *rp=NULL;
            for(Node *p=this;p;p=p->pp){
                p->splay();
                p->rp=rp;
                rp=p;
                p->update();
            }
            splay();
        }
    };

    Node *nodes;
    LinkCutTree(int n){nodes=new Node[n];}

    //•Ó(v->v‚Ìe)‚ðíœ
    void cut(int v){
        nodes[v].expose();
        Node *p=nodes[v].lp;
        nodes[v].lp=NULL;
        p->pp=NULL;
        nodes[v].update();
    }

    //•Ó(v->u)‚ð’Ç‰Á
    void link(int v,int u){
        nodes[v].expose();
        nodes[u].expose();
        nodes[v].pp=&nodes[u];
        nodes[u].rp=&nodes[v];
        nodes[u].update();
    }

    void addEdge(int v,int u){
        assert(!same(v,u));
        evert(v);
        link(v,u);
    }

    int lca(int a,int b){
        nodes[a].expose();
        nodes[b].expose();

        bool sameTree=false;
        Node *ret=&nodes[a];
        for(Node *x=&nodes[a];x;x=x->pp){
            if(x->pp&&x->isRoot())ret=x->pp;
            if(x==&nodes[b])sameTree=true;
        }
        return sameTree?(ret-nodes):-1;
    }

    void evert(int v){
        nodes[v].expose();
        nodes[v].rev^=1;
    }

    int findRoot(int v){
        Node *p=&nodes[v];
        p->expose();
        while(p->lp)p=p->lp;
        p->splay();
        return p-nodes;
    }

    bool areSame(int v,int u){
        return findRoot(v)==findRoot(u);
    }
};
