int quad(pint p){
	if(p.fi>0&&p.se>=0)return 0;
	if(p.se>0&&p.fi<=0)return 1;
	if(p.fi<0&&p.se<=0)return 2;
	return 3;
}
int dot(pint p,pint q){
	return p.fi*q.fi+p.se*q.se;
}
int cross(pint p,pint q){
	return p.fi*q.se-p.se*q.fi;
}
pint operator+(pint p,pint q){
	return pint(p.fi+q.fi,p.se+q.se);
}
pint operator-(pint p,pint q){
	return pint(p.fi-q.fi,p.se-q.se);
}
pint operator*(pint p,int k){
	return pint(p.fi*k,p.se*k);
}
pint operator/(pint p,int k){
	return pint(p.fi/k,p.se/k);
}