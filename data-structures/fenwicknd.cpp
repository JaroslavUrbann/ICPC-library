// https://usaco.guide/plat/2DRQ?lang=cpp
// not tested
template<class T,int...Ns>
struct BIT{
	T val=0;
	void update(T v){val+=v;}
	T query(){return val;}
};

template<class T,int N,int...Ns>
struct BIT<T,N,Ns...>{
	BIT<T,Ns...>bit[N];
	template<typename...Args>
	void update(int x,Args...args){for(;x<N;x+=x&-x)bit[x].update(args...);}
	template<typename...Args>
	T query(int r,Args...args){
		T r=0;
		for(;r;r-=r&-r)r+=bit[r].query(args..);
		return r;
	}
	T query(int l,int r,Args...args){
		return query(r-1,args...)-query(l-1,args...);
	}
}

