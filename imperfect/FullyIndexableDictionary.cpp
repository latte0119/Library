template<int N>class FullyIndexableDictionary{
    static const int bucket=512,block=16;
    static char popcount[];
    int n,B[N/bucket+10];
    unsigned short bs[N/block+10],b[N/block+10];

public:
    FullyIndexableDictionary(){}
    FullyIndexableDictionary(int n,bool s[]):n(n){
        if(!popcount[1])for(int i=0;i<1<<block;i++)popcount[i]=__builtin_popcount(i);

        bs[0]=B[0]=b[0]=0;
        for(int i=0;i<n;i++){
            if(i%block==0){
                bs[i/block+1]=0;
                if(i%bucket==0){
                    B[i/bucket+1]=B[i/bucket];
                    b[i/block+1]=b[i/block]=0;
                }
                else b[i/block+1]=b[i/block];
            }
            bs[i/block]|=short(s[i])<<(i%block);
            b[i/block+1]+=s[i];
            B[i/bucket+1]+=s[i];
        }
        if(n%bucket==0)b[n/block]=0;
    }

    inline int count(bool val,int r){return val?B[r/bucket]+b[r/block]+popcount[bs[r/block]&((1<<(r%block))-1)]:r-count(1,r);}
    inline int count(bool val,int l,int r){return count(val,r)-count(val,l);}

    int select(bool val,int i){
        if(i<0||count(val,n)<i+1)return -1;
        i++;
        int lb=0,ub=n,mid;
        while(ub-lb>1){
            mid=(ub+lb)>>1;
            if(count(val,mid)>=i)ub=mid;
            else lb=mid;
        }
        return lb;
    }
    bool operator[](int i){return bs[i/block]>>(i%block)&1;}
};
template<int N>char FullyIndexableDictionary<N>::popcount[1<<FullyIndexableDictionary<N>::block];
