struct NumberTheoreticTransformWithArbitraryMod{
int mods[3]={167772161,469762049,1224736769};
    int roots[3]={3,3,3};
    struct NumberTheoreticTransform{
        int mod;
        int root;
        NumberTheoreticTransform(int mod,int root):mod(mod),root(root){}

        int mul(int x,int y){
            return x*y%mod;
        }
        int add(int x,int y){
            return (x+=y)>=mod?x-mod:x;
        }

        int pow(int x,int y){
            int res=1;
            while(y){
                if(y&1)res=mul(res,x);
                x=mul(x,x);
                y>>=1;
            }
            return res;
        }

        int inv(int x){
            return pow(x,mod-2);
        }

        void ntt(vector<int>&f,bool rev=false){
            int n=f.size();
            for(int i=0,j=1;j<n-1;j++){
                for(int k=n>>1;k>(i^=k);k/=2);
                if(i>j)swap(f[i],f[j]);
            }

            for(int m=2;m<=n;m*=2){
                int wr=pow(root,(mod-1)/m);
                if(rev)wr=inv(wr);
                for(int i=0;i<n;i+=m){
                    int w=1;
                    for(int j=0;j<m/2;j++){
                        int f0=f[i+j],f1=mul(w,f[i+j+m/2]);
                        f[i+j]=add(f0,f1);
                        f[i+j+m/2]=add(f0,mod-f1);
                        w=mul(w,wr);
                    }
                }
            }
            if(rev){
                int v=inv(n);
                for(int i=0;i<n;i++)f[i]=mul(f[i],v);
            }
        }
        vector<int>multiply(vector<int>A,vector<int>B){
            rep(i,A.size())A[i]%=mod;
            rep(i,B.size())B[i]%=mod;
            int n=1;
            while(n<A.size()+B.size()-1)n<<=1;
            A.resize(n);B.resize(n);
            ntt(A);
            ntt(B);
            for(int i=0;i<n;i++)A[i]=mul(A[i],B[i]);
            ntt(A,true);
            A.resize(A.size()+B.size()-1);
            return A;
        }
    };
    struct garner{
        inline int extgcd(int a,int b,int& x,int& y){x=1,y=0;int g=a;if(b!=0) g=extgcd(b,a%b,y,x),y-=a/b*x;return g;}
        inline int mod_inv(int a,int mod){int x,y;extgcd(a,mod,x,y);return (x%mod+mod)%mod;}

        int solve(vector<pair<int,int>>mr,int mod){
            mr.push_back({mod,0});
            vector<int>coffs(mr.size(),1);
            vector<int>constants(mr.size(),0);

            for(int i=0;i<mr.size()-1;i++){
                int v=(mr[i].second-constants[i]+mr[i].first)*mod_inv(coffs[i],mr[i].first)%mr[i].first;
                if(v<0)v+=mr[i].first;
                for(int j=i+1;j<mr.size();j++){
                    (constants[j]+=coffs[j]*v)%=mr[j].first;
                    (coffs[j]*=mr[i].first)%=mr[j].first;
                }
            }

        return constants[mr.size()-1];
        }
    };
    vector<int>convolute(vector<int>a,vector<int>b){
        NumberTheoreticTransform ntt1(mods[0],roots[0]);
        NumberTheoreticTransform ntt2(mods[1],roots[1]);
        NumberTheoreticTransform ntt3(mods[2],roots[2]);

        vector<int>c1=ntt1.multiply(a,b);
        vector<int>c2=ntt2.multiply(a,b);
        vector<int>c3=ntt3.multiply(a,b);

        vector<int>ret(a.size()+b.size()-1);
        for(int i=0;i<ret.size();i++){
            vector<pair<int,int>>mr(3);
            mr[0]={mods[0],c1[i]};
            mr[1]={mods[1],c2[i]};
            mr[2]={mods[2],c3[i]};

            ret[i]=garner().solve(mr,mod);

        }
        return ret;
    }
}
