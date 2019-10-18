template<typename I,bool isMin>
struct ConvexHullTrick{
#define a first
#define b second
 
	using Line=pair<I,I>;
	deque<Line>lines;
 
	//l.a>=m.a>=r.a
	inline bool notNecessary(const Line &l,const Line &m,const Line &r){
		return (m.a-l.a)*(r.b-m.b)>=(m.b-l.b)*(r.a-m.a);
	}
	void addLine(I a,I b){
		if(!isMin)a*=-1,b*=-1;
		Line l(a,b);
		if(lines.empty())lines.push_back(l);
		else if(lines.front().a<=a){
			if(lines.front().a==a){
				if(lines.front().b<=b)return;
				lines.pop_front();
			}
			while(lines.size()>=2&&notNecessary(l,lines[0],lines[1]))lines.pop_front();
			lines.push_front(l);
		}
		else{
			if(lines.back().a==a){
				if(lines.back().b<=b)return;
				lines.pop_back();
			}
			while(lines.size()>=2&&notNecessary(lines[lines.size()-2],lines[lines.size()-1],l))lines.pop_back();
			lines.push_back(l);
		}
	}
 
	inline I eval(const Line &l,I x){
		return l.a*x+l.b;
	}
 
	I query(I x){
		int lb=-1,ub=lines.size()-1;
		while(ub-lb>1){
			int mid=(ub+lb)/2;
			if(eval(lines[mid],x)<=eval(lines[mid+1],x))ub=mid;
			else lb=mid;
		}
		if(isMin)return eval(lines[ub],x);
		return -eval(lines[ub],x);
	}
 
	I queryMonotoneInc(I x){
		while(lines.size()>=2&&eval(lines[0],x)>=eval(lines[1],x))lines.pop_front();
		if(isMin)return eval(lines[0],x);
		return -eval(lines[0],x);
	}
	I queryMonotoneDec(I x){
		while(lines.size()>=2&&eval(lines[lines.size()-1],x)>=eval(lines[lines.size()-2],x))lines.pop_back();
		if(isMin)return eval(lines.back(),x);
		return -eval(lines.back(),x);
	}
#undef a
#undef b
};