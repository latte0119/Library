template<class T>
class fullyPersistentArray{
public:
    fullyPersistentArray(int n=0){
        h=0;
        for(int i=1;i<n;i*=16)h+=4;
    }

    T const &get(int k){
        return immutableGet(k,root,0,h)->value;
    }

    T &set(int k){
        auto p=mutableGet(k,root,0,h);
        root=p.first;
        return p.second->value;
    }

private:
    struct node{
        node *ch[16]={};
        T value;

        node(){}
        node(T value):value(value){}
    };

    int h;
    node *root=nullptr;

    node *immutableGet(int a,node *x,int l,int d){
        if(d==0)return x;
        int id=(a-l)>>(d-4);
        return immutableGet(a,x->ch[id],l+(id<<(d-4)),d-4);
    }

    pair<node *,node *>mutableGet(int a,node *x,int l,int d){
        x=x!=nullptr?new node(*x):new node();
        if(d==0)return {x,x};
        int id=(a-l)>>(d-4);
        auto p=mutableGet(a,x->ch[id],l+(id<<(d-4)),d-4);
        x->ch[id]=p.first;
        return {x,p.second};
    }
};

