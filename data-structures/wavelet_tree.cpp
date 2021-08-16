// CHANGE ACCORDINGLY
static char buf[450<<20];
void*operator new(size_t s){
	static size_t i=sizeof(buf);
	assert(s<=i);
	return (void*)&buf[i-=s];
}
void operator delete(void*){}
 
// 32 bit ptr for saving memory
template<class T>
struct P{
	unsigned i;
	P(T*p=0):i(p?unsigned((char*)p-buf):0){}
	T&operator*()const{return*(T*)(buf+i);}
	T*operator->()const{return&**this;}
	T&operator[](int a)const{return(&**this)[a];}
	explicit operator bool()const{return i;};
};

 
struct Wave{
	typedef int T;
	static const T L=-1e9,R=1e9+1;
	vector<int>ni={0},oi={0};
	P<Wave>c[2]={0,0};
	Wave(int n=0){oi.resize(n+1);iota(oi.begin(),oi.end(),0);}
	// you can change ptr to iterator, but this is slightly faster
	// building is the slowest part
	void build(int*l,int*r,T lb=L,T rb=R){
		if(lb+1==rb||l>=r)return;
		for(int i=0;i<2;++i)c[i]=new Wave();
		T m=lb+(rb-lb)/2;
		ni.reserve(r-l+1);
		for(auto i=l;i!=r;++i){
			c[*i>=m]->oi.push_back(ni.size());
			ni.push_back(ni.back()+(*i<m));
		}
		auto mid=stable_partition(l,r,[&](int d){return d<m;});
		c[0]->build(l,mid,lb,m),c[1]->build(mid,r,m,rb);
	}
	// value of kth biggest element in range [l,r)
	T kth(int l,int r,int k,T lb=L,T rb=R){
		if(lb+1==rb)return lb;
		T m=lb+(rb-lb)/2;
		int onLeft=ni[r]-ni[l];
		return onLeft>=k?c[0]->kth(ni[l],ni[r],k,lb,m):
		                 c[1]->kth(l-ni[l],r-ni[r],k-onLeft,m,rb);
	}
	// 1-index of kth element of value v in range [l,r) or 0 if k is too big
	T vth(int l,int r,int k,T v,T lb=L,T rb=R){
		if(lb+1==rb)return oi[(l+k<=r)*(l+k)];
		T m=lb+(rb-lb)/2;
		if(!bool(c[v>=m]))return 0;
		return oi[v<m?c[0]->vth(ni[l],ni[r],k,v,lb,m):c[1]->vth(l-ni[l],r-ni[r],k,v,m,rb)];
	}
	void swp(int i,T lb=L,T rb=R){ // not compiled, swap(a[i],a[i+1]), 1-indexed
		if(lb+1==rb)return; // same value
		T m=lb+(rb-lb)/2;
		int&x=ni[i-1],&y=ni[i],&z=ni[i+1];
		if(x<y&&y<z)swp(y,lb,m); // both smaller
		else if(x==y&&y==z)return swp(i-y,m,rb); // both bigger
		else --c[x<y]->oi[z],++c[y<z]->oi[y],y=x+(y<z); // lmao
	}
	void add(T v,int o,T lb=L,T rb=R){ // not compiled, adds element to the back of the array o == new size of array
		oi.push_back(o);
		if(lb+1==rb)return;
		T m=lb+(rb-lb)/2;
		if(!bool(c[v>=m]))c[v>=m]=new Wave();
		c[v>=m]->add(v,ni.size(),v>=m?m:lb,v>=m?rb:m);
		ni.push_back((v<m)+ni.back());
	}
	void del(T lb=L,T rb=R){ // not compiled, deletes from the back of the array
		oi.pop_back();
		if(lb+1==rb)return;
		T m=lb+(rb-lb)/2,prv=ni.back();ni.pop_back();
		ni.back()<prv?del(lb,m):del(m,rb);
	}
};
