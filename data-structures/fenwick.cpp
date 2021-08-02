// always index from 1 to n & init with n+1
template<class T>
struct BIT{
	T n;vector<T>a;
	BIT(int n):n(n),a(n){}; 
	T query(int l,int r){return query(r-1)-query(l-1);}
	T query(int i){
		T r=0;
		for(;i;i-=i&-i)r+=a[i];
		return r;
	}
	void update(int i,T d){
		for(;i<n;i+=i&-i)a[i]+=d;
	}
};
