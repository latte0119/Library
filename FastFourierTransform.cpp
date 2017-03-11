namespace FFT{
    typedef complex<double>C;
    const double PI=acos(-1);

    void dft(vector<C>&f,bool rev=false){
        int n=f.size();
        for(int i=0,j=1;j<n-1;j++){
            for(int k=n>>1;k>(i^=k);k/=2);
            if(i>j)swap(f[i],f[j]);
        }
        for(int m=2;m<=n;m*=2){
            C wr=polar(1.0,(rev?-1:1)*2.0*PI/m);
            for(int i=0;i<n;i+=m){
                C w(1,0);
                for(int j=0;j<m/2;j++){
                    C f0=f[i+j],f1=w*f[i+j+m/2];
                    f[i+j]=f0+f1;
                    f[i+j+m/2]=f0-f1;
                    w*=wr;
                }
            }
        }
        if(rev)for(int i=0;i<n;i++)f[i]*=1.0/n;
    }

    vector<int>multiply(vector<int>A,vector<int>B){
        int n=1;
        while(n<=A.size()+B.size())n<<=1;
        vector<C>g(n),h(n);
        for(int i=0;i<A.size();i++)g[i]=A[i];
        for(int i=0;i<B.size();i++)h[i]=B[i];

        dft(g);
        dft(h);
        for(int i=0;i<n;i++)g[i]*=h[i];
        dft(g,true);

        vector<int>C(A.size()+B.size()-1);
        for(int i=0;i<C.size();i++)C[i]=(int)(g[i].real()+0.5);
        return C;
    }
}
