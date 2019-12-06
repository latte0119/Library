template<class T>
vector<T>FWHT(vector<T>f){
    for(int len=1;2*len<=f.size();len<<=1){
        for(int i=0;i<f.size();i+=2*len){
            for(int j=0;j<len;j++){
                T u=f[i+j];
                T v=f[i+j+len];
                f[i+j]=u+v;
                f[i+j+len]=u-v;
            }
        }
    }
    return f;
}