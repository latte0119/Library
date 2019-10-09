/*
g(T)=\sum_{S \subset T}f(S)
*/
template<class T>
inline void FastZetaTransformSubset(vector<T>&f,function<T(T,T)>add){
    int n=__lg(f.size());
    for(int i=0;i<n;i++){
        for(int j=0;j<1<<n;j++){
            if(~j>>i&1)f[j|1<<i]=add(f[j|1<<i],f[j]);
        }
    }
}


/*
g(S)=\sum_{T \supset S}f(T)
*/
template<class T>
inline void FastZetaTransformSuperset(vector<T>&f,function<T(T,T)>add){
    int n=__lg(f.size());
    for(int i=0;i<n;i++){
        for(int j=0;j<1<<n;j++){
            if(~j>>i&1)f[j]=add(f[j],f[j|1<<i]);
        }
    }
}


/*
g(T)=\sum_{S \subset T}(-1)^{|T\S|}f(S)
*/
template<class T>
inline void FastMoebiusTransformSubset(vector<T>&f,function<T(T,T)>sub){
    int n=__lg(f.size());
    for(int i=0;i<n;i++){
        for(int j=0;j<1<<n;j++){
            if(~j>>i&1)f[j|1<<i]=sub(f[j|1<<i],f[j]);
        }
    }
}


/*
g(S)=\sum_{T \superset S}(-1)^{|T\S|}f(T)
*/
template<class T>
inline void FastMoebiusTransformSuperset(vector<T>&f,function<T(T,T)>sub){
    int n=__lg(f.size());
    for(int i=0;i<n;i++){
        for(int j=0;j<1<<n;j++){
            if(~j>>i&1)f[j]=sub(f[j],f[j|1<<i]);
        }
    }
}

/*
verified:

FZTSubset:
https://codeforces.com/contest/1221/submission/62173329

FZTSuperset:
https://codeforces.com/contest/1221/submission/62173744

FMTSubset:

FMTSuperset:
*/
