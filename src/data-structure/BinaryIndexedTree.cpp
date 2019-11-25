/*
0-indexed
add(k,x): a[k]+=x
sum(k): sum(a[0,k])


space:O(N)
time:O(logN) per query
*/
template<class T>
struct  BinaryIndexedTree{
    int n;
    vector<T>dat;

    BinaryIndexedTree(int n=0):n(n),dat(n+1){}

    void add(int k,T x){
        for(k++;k<=n;k+=k&-k)dat[k]+=x;
    }
    T sum(int k){
        T ret{};
        for(k++;k;k-=k&-k)ret+=dat[k];
        return ret;
    }
};