// quite slow
// inclusive, exclusive
struct iset{
	typedef int T;
	set<tuple<T,T,T>>longest; // len, l, r
	set<pair<T,T>>ints;
	set<pair<T,T>>::iterator insert(T l,T r){
		auto it=ints.lower_bound({l,INT_MIN});
		if(it!=ints.begin()){
			auto[lp,rp]=*prev(it);
			if(l<=rp){
				it=erase(prev(it));
				l=min(l,lp);
				r=max(r,rp);
			}
		}
		for(;it!=ints.end();it=erase(it)){
			auto[ln,rn]=*it;
			if(ln>r)break;
			r=max(r,rn);
		}
		longest.insert({r-l,l,r}); // m
		return ints.insert({l,r}).first;
	}
	// erases any segment, returns first segment after r
	set<pair<T,T>>::iterator erase(T l,T r){
		auto it=ints.lower_bound({l,INT_MIN});
		if(it!=ints.begin()){
			auto[lp,rp]=*prev(it);
			if(l<rp){
				erase(prev(it));
				it=next(insert(lp,l));
				if(r<rp)return insert(r,rp);
			}
		}
		while(it!=ints.end()){
			auto[ln,rn]=*it;
			if(r<=ln)break;
			it=erase(it);
			if(r<rn)return insert(r,rn);
		}
		return it;
	}
	set<pair<T,T>>::iterator erase(const set<pair<T,T>>::iterator&it){
		if(it==ints.end())return it;
		auto[l,r]=*it;
		longest.erase({r-l,l,r}); // m
		return ints.erase(it);
	}
	set<pair<T,T>>::iterator begin(){return ints.begin();}
	set<pair<T,T>>::iterator end(){return ints.end();}
	set<pair<T,T>>::iterator find(T l,T r){return ints.find({l,r});}
	T maxlen(){return longest.empty()?0:get<0>(*longest.rbegin());}
};

