template<typename O>
struct ST{
	using T=typename O::T;
	int n;vector<T>t;
	ST(vector<T>a):n(1<<int(log2(a.size())+1)),t(2*n,D){
		copy(a.begin(),a.end(),t.begin()+n);
		for(int i=n-1;i>0;--i)t[i]=O::uni(t[2*i],t[2*i+1]);
	}
	T query(int l,int r){
		T res=D;
		for(l+=n,r+=n;l<r;l/=2,r/=2){
			if(l&1)res=O::uni(res,t[l++]);
			if(r&1)res=O::uni(res,t[--r]);
		}
		return res;
	}
	void update(int p,T v){
		for(O::upd(t[p+=n],v);p/=2;)t[p]=O::uni(t[2*p],t[2*p+1]);
	}
};
