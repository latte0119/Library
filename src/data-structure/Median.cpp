/*
lo.size()<=hi.size();
*lo.rbegin()<=*hi.begin();
*/
struct Median{
	multiset<int>lo,hi;
	int sumlo,sumhi;


	Median():sumlo(0),sumhi(0){}

	void adjust(){
		while(lo.size()>hi.size()){
			int tmp=*lo.rbegin();
			lo.erase(lo.find(tmp));
			sumlo-=tmp;
			hi.insert(tmp);
			sumhi+=tmp;
		}

		while(hi.size()>lo.size()+1){
			int tmp=*hi.begin();
			hi.erase(hi.find(tmp));
			sumhi-=tmp;
			lo.insert(tmp);
			sumlo+=tmp;
		}
	}

	void add(int x){
		if(hi.size()==0||*hi.begin()<=x){
			hi.insert(x);
			sumhi+=x;
		}
		else{
			lo.insert(x);
			sumlo+=x;
		}
		adjust();
	}
	void del(int x){
		if(*hi.begin()<=x){
			hi.erase(hi.find(x));
			sumhi-=x;
		}
		else{
			lo.erase(lo.find(x));
			sumlo-=x;
		}
		adjust();
	}

	int getMedian(){
		return *hi.begin();
	}
	int calcDistSum(){
		int m=getMedian();
		return (sumhi-m*(int)hi.size())+(m*(int)lo.size()-sumlo);
	}
};