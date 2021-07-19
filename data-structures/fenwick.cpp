// always index from 1 to n
// if I added vector init, it wouldn't be clear if prefix or not
// call update for each item after init to init
// update: add d to a[i] (and update the prefix sum)
// query: if i has first 1 at pos x, then it keeps the sum of the next 2^x numbers, so we add that sum and jump by 2^x
template<class T>
struct Fenwick{
	T n;vector<T>a;
	Fenwick(int n):n(n),a(n){}; 
	T query(int i){
		T r=0;
		for(;i;i-=i&-i)r+=a[i];
		return r;
	}
	void update(int i,T d){
		for(;i<n;i+=i&-i)a[i]+=d;
	}
};
