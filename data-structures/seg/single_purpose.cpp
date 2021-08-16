// seg tree for one operation
template<class O>
struct ST{
	using T=typename O::T;
	int n;vector<T>tr,lz;
	ST(vector<T>a):n(1<<int(1+log2(a.size()))),tr(2*n,O::D),lz(2*n,O::DL){
		copy(a.begin(),a.end(),tr.begin()+n);
		for(int i=n-1;i>0;--i)tr[i]=O::uni(tr[2*i],tr[2*i+1]);
	}
	void applylazy(int u,int lb,int rb){
		if(lz[u]!=O::DL){
			tr[u]=O::rv(tr[u],lz[u],lb,rb);
			O::upd(lz[2*u],lz[u]);
			O::upd(lz[2*u+1],lz[u]);
			lz[u]=O::DL;
		}
	}
	T query(int l,int r){return query(l,r,0,n,1);}
	T query(int l,int r,int lb,int rb,int u){
		if(rb<=l||r<=lb)return O::D;
		if(l<=lb&&rb<=r)return O::rv(tr[u],lz[u],lb,rb);
		applylazy(u,lb,rb);
		int m=(lb+rb)/2;
		return O::uni(query(l,r,lb,m,2*u),query(l,r,m,rb,2*u+1));
	}
	T update(int l,int r,T x){return update(l,r,0,n,1,x);}
	T update(int l,int r,int lb,int rb,int u,T x){
		if(rb<=l||r<=lb)return O::rv(tr[u],lz[u],lb,rb);
		if(l<=lb&&rb<=r)return O::rv(tr[u],O::upd(lz[u],x),lb,rb);
		applylazy(u,lb,rb);
		int m=(lb+rb)/2;
		return tr[u]=O::uni(update(l,r,lb,m,2*u,x),update(l,r,m,rb,2*u+1,x));
	}
};

// if you get undefined reference to DL, just also put this outside of the struct
// const int max_add::D,max_add::DL;
struct max_add{
	typedef int T;
	static const T D=numeric_limits<T>::min(),DL=0;
	static T rv(T val,T lz,int lb,int rb){return val+lz;}
	static T upd(T&a,T b){return a+=b;}
	static T uni(T a,T b){return max(a,b);}
};

struct min_add{
	typedef int T;
	static const T D=numeric_limits<T>::max(),DL=0;
	static T rv(T val,T lz,int lb,int rb){return val+lz;}
	static T upd(T&a,T b){return a+=b;}
	static T uni(T a,T b){return min(a,b);}
};

struct min_set{
	typedef int T;
	static const T D=numeric_limits<T>::max(),DL=0;
	static T rv(T val,T lz,int lb,int rb){return lz?lz:val;}
	static T upd(T&a,T b){return a=b;}
	static T uni(T a,T b){return min(a,b);}
};

// keeps additional information (eg. query id)
struct max_set{
	typedef pair<int,int> T;
	static constexpr T D=make_pair(INT_MIN,INT_MIN),DL=make_pair(0,0);
	static T rv(T val,T lz,int lb,int rb){return lz.first?lz:val;}
	static T upd(T&a,T b){return a=b;}
	static T uni(T a,T b){return max(a,b);}
};

