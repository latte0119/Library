template<class T>
vector<int>mp(T &s){
	vector<int>a(s.size()+1);
	a[0]=-1;
	int j=-1;
	for(int i=0;i<s.size();i++){
		while(j>=0&&s[i]!=s[j])j=a[j];
		j++;
		a[i+1]=j;
	}
	return a;
}


/*
TODO:verify  
*/