// seg tree for multiple operations / data
// not really tested / used
// not exactly fast so far
template<class T>
struct ST{
	int n;vector<T>t;
	ST(const vector<T>&a):n(1<<int(1+log2(a.size()))),t(2*n){
		copy(a.begin(),a.end(),t.begin()+n);
		for(int i=n-1;i>0;--i)t[i]=T::uni(t[2*i],t[2*i+1]);
	}
	T query(int l,int r){return query(l,r,0,n,1);}
	T query(int l,int r,int lb,int rb,int u){
		if(rb<=l||r<=lb)return T();
		if(l<=lb&&rb<=r)return T::rv(t[u],lb,rb);
		T::prop(t[u],t[2*u],t[2*u+1],lb,rb);
		int m=(lb+rb)/2;
		return T::uni(query(l,r,lb,m,2*u),query(l,r,m,rb,2*u+1));
	}
	T update(int l,int r,T x){return update(l,r,0,n,1,x);}
	T update(int l,int r,int lb,int rb,int u,T x){
		if(rb<=l||r<=lb)return T::rv(t[u],lb,rb);
		if(l<=lb&&rb<=r)return T::rv(T::upd(t[u],x,lb,rb),lb,rb);
		T::prop(t[u],t[2*u],t[2*u+1],lb,rb);
		int m=(lb+rb)/2;
		return t[u]=T::uni(update(l,r,lb,m,2*u,x),update(l,r,m,rb,2*u+1,x));
	}
};

// if you get undefined reference to DL, just also put this outside of the struct
// const int max_add::D,max_add::DL;
// default val should be for unused values, so don't forget to init your array
// min_add_cnt
struct mac{
	typedef int T;
	static const T D=numeric_limits<T>::max(),DL=0;
	T mn,lz,cnt;
	mac(T mn=D,T lz=DL,T cnt=0):mn(mn),lz(lz),cnt(cnt){}
	static mac uni(const mac&a,const mac&b){ // assumes no lazy
		return mac(min(a.mn,b.mn),DL,a.mn==b.mn?a.cnt+b.cnt:a.mn<b.mn?a.cnt:b.cnt);
	}
	static void prop(mac&p,mac&l,mac&r,int lb,int rb){
		if(p.lz!=DL){
			l.lz+=p.lz;
			r.lz+=p.lz;
			p.mn+=p.lz;
			p.lz=DL;
		}
	}
	static mac rv(const mac&u,int lb,int rb){return mac(u.mn+u.lz,DL,u.cnt);}
	// only used once each query
	static mac upd(mac&u,mac&v,int lb,int rb){ // returns u, v is probably bs
		return u=mac(u.mn,u.lz+v.lz,u.cnt); // update with lazy
	}
};

// slightly tested
// x=max(x,update) + keeps id of query
struct maxeq{
	typedef int T;
	static const T D=numeric_limits<T>::min(),DL=0;
	T mx,lz,id;
	maxeq(T mx=D,T lz=DL,T id=-1):mx(mx),lz(lz),id(id){}
	// children have no lazy
	static maxeq uni(const maxeq&a,const maxeq&b){
		return maxeq(max(a.mx,b.mx),DL,a.mx<b.mx?b.id:a.id);
	}
	static void prop(maxeq&p,maxeq&l,maxeq&r,int lb,int rb){
		if(p.lz!=DL){
			if(rv(l,lb,rb).mx<=p.lz)tie(l.lz,l.id)=tie(p.lz,p.id);
			if(rv(r,lb,rb).mx<=p.lz)tie(r.lz,r.id)=tie(p.lz,p.id);
			p.mx=p.lz;
			p.lz=DL;
		}
	}
	static maxeq rv(const maxeq&u,int lb,int rb){return maxeq(u.lz?u.lz:u.mx,DL,u.id);}
	// only used once per query
	static maxeq upd(maxeq&u,maxeq&v,int lb,int rb){
		return u=maxeq(u.mx,rv(u,lb,rb).mx<=v.lz?v.lz:u.lz,rv(u,lb,rb).mx<=v.lz?v.id:u.id);
	}
};
