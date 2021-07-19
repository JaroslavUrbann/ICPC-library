template<typename T>
struct SegmentTree{
	const int D=INT_MIN; // default value for tree / query answer
	void u(T&a,T b){a=b;} // update op
	T q(T a,T b){return max(a,b);} // query op
	int n;vector<T>t;
	SegmentTree(vector<T>a):n(pow(2,ceil(log2(a.size())))),t(2*n,D){
		copy(a.begin(),a.end(),t.begin()+n);
		for(int i=n-1;i>0;--i)t[i]=q(t[2*i],t[2*i+1]);
	}
	T query(int l,int r){
		T res=D;
		for(l+=n,r+=n;l<r;l/=2,r/=2){
			if(l&1)res=q(res,t[l++]);
			if(r&1)res=q(res,t[--r]);
		}
		return res;
	}
	void update(int p,T v){
		for(u(t[p+=n],v);p/=2;)t[p]=q(t[2*p],t[2*p+1]);
	}
};
