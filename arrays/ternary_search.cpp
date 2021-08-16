// finds index of maximum, takes function <<<<mx>=>=>=
// to reverse leq, change < to <=
// not tested
template<class T,class F>
T ternSearch(T l,T r,F f){
	while(l+1<r){
		T m=l+(r-l)/2;
		if(f(m-1)<f(m))l=m; // c
		else r=m;
	}
	return l;
}

