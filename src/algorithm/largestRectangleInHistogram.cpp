/*
max{min(H[l,r))*(r-l) | 0<=l<r<=N}

time,space:O(N)
*/
int64_t largestRectangleInHistogram(vector<int64_t>H){
    int32_t N=H.size(); 
    vector<int32_t>L(N),R(N);
    for(int32_t i=0;i<N;i++){
        L[i]=i-1;
        while(L[i]!=-1&&H[L[i]]>=H[i])L[i]=L[L[i]];
    } 
    for(int32_t i=N-1;i>=0;i--){
        R[i]=i+1;
        while(R[i]!=N&&H[R[i]]>=H[i])R[i]=R[R[i]];
    }

    int64_t ans=0;
    for(int32_t i=0;i<N;i++){
        ans=max(ans,H[i]*(R[i]-L[i]-1));
    }
    
    return ans;
}