struct LayeredRangeTree{
    LayeredRangeTree(){}
    LayeredRangeTree(vector<int>&a){init(a);}
    void init(vector<int>&a){
        Size=1;while(Size<a.size())Size*=2;
        data.resize(Size*2);
        toL.resize(Size*2);
        toR.resize(Size*2);


        for(int i=0;i<a.size();i++){
            data[i+Size-1].push_back(a[i]);
        }

        for(int i=Size-2;i>=0;i--){
            data[i].resize(data[i*2+1].size()+data[i*2+2].size());
            toL[i].resize(data[i].size()+1);
            toR[i].resize(data[i].size()+1);
            if(data[i].size()==0)continue;
            merge(data[i*2+1].begin(),data[i*2+1].end(),data[i*2+2].begin(),data[i*2+2].end(),data[i].begin());

            {
                int cur=0;
                for(int j=0;j<data[i].size();j++){
                    while(cur<data[i*2+1].size()&&data[i][j]>data[i*2+1][cur])cur++;
                    toL[i][j]=cur;
                }
                toL[i][data[i].size()]=data[i*2+1].size();
            }

            {
                int cur=0;
                for(int j=0;j<data[i].size();j++){
                    while(cur<data[i*2+2].size()&&data[i][j]>data[i*2+2][cur])cur++;
                    toR[i][j]=cur;
                }
                toR[i][data[i].size()]=data[i*2+2].size();
            }
        }
    }

    int query(int a,int b,int c,int d){
        c=lower_bound(data[0].begin(),data[0].end(),c)-data[0].begin();
        d=lower_bound(data[0].begin(),data[0].end(),d)-data[0].begin();
        return query(a,b,c,d,0,0,Size);
    }

    int query(int a,int b,int c,int d,int k,int l,int r){
        if(r<=a||b<=l)return 0;
        if(a<=l&&r<=b)return d-c;
        return query(a,b,toL[k][c],toL[k][d],k*2+1,l,(l+r)/2)+query(a,b,toR[k][c],toR[k][d],k*2+2,(l+r)/2,r);
    }

    vector<vector<int>>data,toL,toR;
    int Size;
};