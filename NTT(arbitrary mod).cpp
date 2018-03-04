
struct NumberTheoreticTransformWithArbitraryMod{
    static constexpr int mod=1000000007;
    static constexpr int mod0=167772161;
    static constexpr int mod1=469762049;
    static constexpr int mod2=1224736769;
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
    inline int mod_inv0(int a){
        int m=mod0-2;
        int ret=1;
        while(m){
            if(m&1)ret=ret*a%mod0;
            a=a*a%mod0;
            m>>=1;
        }
        return ret;
    }
    inline int mod_inv1(int a){
        int m=mod1-2;
        int ret=1;
        while(m){
            if(m&1)ret=ret*a%mod1;
            a=a*a%mod1;
            m>>=1;
        }
        return ret;
    }
    inline int mod_inv2(int a){
        int m=mod2-2;
        int ret=1;
        while(m){
            if(m&1)ret=ret*a%mod2;
            a=a*a%mod2;
            m>>=1;
        }
        return ret;
    }
    inline int mod_inv(int a){
        int m=mod-2;
        int ret=1;
        while(m){
            if(m&1)ret=ret*a%mod;
            a=a*a%mod;
            m>>=1;
        }
        return ret;
    }
    inline int garner(vector<int>mr){
        mr.pb(0);
        vector<int>coffs(mr.size(),1);
        vector<int>constants(mr.size(),0);

        int v;

        v=(mr[0]-constants[0]+mod0)*mod_inv0(coffs[0])%mod0;
        if(v<0)v+=mod0;
        (constants[1]+=coffs[1]*v)%=mod1;
        (coffs[1]*=mod0)%=mod1;

        (constants[2]+=coffs[2]*v)%=mod2;
        (coffs[2]*=mod0)%=mod2;

        (constants[3]+=coffs[3]*v)%=mod;
        (coffs[3]*=mod0)%=mod;




        v=(mr[1]-constants[1]+mod1)*mod_inv1(coffs[1])%mod1;
        if(v<0)v+=mod1;

        (constants[2]+=coffs[2]*v)%=mod2;
        (coffs[2]*=mod1)%=mod2;

        (constants[3]+=coffs[3]*v)%=mod;
        (coffs[3]*=mod1)%=mod;


        v=(mr[2]-constants[2]+mod2)*mod_inv2(coffs[2])%mod2;
        if(v<0)v+=mod2;

        (constants[3]+=coffs[3]*v)%=mod;
        (coffs[3]*=mod2)%=mod;

        return constants[mr.size()-1];
    }

    vector<int>convolute(vector<int>a,vector<int>b){
        NumberTheoreticTransform ntt1(167772161,3);
        NumberTheoreticTransform ntt2(469762049,3);
        NumberTheoreticTransform ntt3(1224736769,3);

        vector<int>c1=ntt1.multiply(a,b);
        vector<int>c2=ntt2.multiply(a,b);
        vector<int>c3=ntt3.multiply(a,b);


        vector<int>mr(3);
        for(int i=0;i<c1.size();i++){
            mr[0]=c1[i];
            mr[1]=c2[i];
            mr[2]=c3[i];

            c1[i]=garner(mr);

        }
        return c1;
    }
};
