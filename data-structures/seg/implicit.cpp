// not compiled

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

typedef int T; // data
typedef int B; // boundry
static const B inf=numeric_limits<T>::max()>>1;
struct ST;
typedef P<ST> ptr;

struct ST{
	array<ptr,2>c;int sz=0;
	B lb=-inf,rb=inf;
	T val=-inf,madd=0,mset=inf;
};

ST real(ptr u){
	if(!u)return ST();
	ST res(*u);
	res.madd=0,mset=inf;
	return res;
}

// assumes no lazy on both
ST uni(ST a,ST b){
	ST res;
	res.val=max(a.val,b.val);
	res.sz=a.val+b.val;
	return res;
}

void push(ptr u){
	if(!u)return;
	for(ptr c:u->c)if(c){
		if(mset!=inf)set(c,mset);
		else add(c,madd);
	}
	mset=inf,madd=0;
}

// assumes no lazy on u
ptr pull(ptr u){
	if(!u)return u;
	auto a=real(u->c[0]),b=real(u->c[1]);
	u->val=max(a.val,b.val);
	u->sz=a.sz+b.sz;
	return u;
}

PT query(ptr u,B l,B r){
	if(!u||r<=lb||rb<=l)return PT();
	if(l<=lb&&rb<=r)return real(u);
	push(u);ST res;
	for(ptr c:u->c)res=uni(res,query(c,l,r));
	return res;
}

void update(ptr u,B l,B r,T x,bool add){
	if(!u||r<=lb||rb<=l)return; // if !u => create node
	if(l<=lb&&rb<=r){
		if(add){
			u->madd=0,u->mset=u->val=x;
		else{
			if(mset!=inf)mset+=x;
			else madd+=x;
			val+=x;
		}
	}else{
		for(ptr c:u->c)add(c,l,r,x,add);
		pull(u);
	}
}

// you can merge & split segtrees in amortized log(n)
// it's useful: https://codeforces.com/blog/entry/49446

// merges 2 segtrees
ptr merge(ptr u,ptr v){
	if(!u)return v;
	if(!v)return u;
	push(u),push(v);
	for(int i=0;i<2;++i)u->c[i]=merge(u->c[i],v->c[i]);
	return pull(u);
}

// splits segtree into 2 trees, first one with the first k nodes
// returns root of new tree
void split(ptr&u,ptr&v,int k){
	v=new ST();
	if(!u){u=new ST();return;}
	tie(v->lb,v->rb)=tie(u->lb,u->rb);
	if(u->lb+1==u->rb){
		if(!k)swap(u,v);
		return;
	}
	push(u);
	int lsz=real(u->c[0]).sz;
	if(lsz<=k)split(u->c[1],v->c[1],k-lsz);
	else{
		swap(u->c[1],v->c[1]);
		split(u->c[0],v->c[0],k);
	}
}
