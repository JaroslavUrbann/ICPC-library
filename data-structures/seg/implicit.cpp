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
static const T tinf=numeric_limits<T>::max()>>1;
static const B binf=numeric_limits<T>::max()>>1;
struct ST;
typedef P<ST> ptr;

struct ST{
	array<ptr,2>c;int sz=1;
	B lb=-binf,rb=binf;
	T val=-tinf,madd=0,mset=tinf;
	ST()=default;
	ST(T val,B l=-binf,B r=binf):val(val),lb(l),rb(r){}
};

void add(ptr u,T x,B l,B r);
void setu(ptr u,T x,B l,B r);

// kind of loses its point when lazy is already applied, maybe consider using this
// lazy design with treap & other stuff as well
// has to delete lazy
ST real(ptr u){
	if(!u)return ST();
	ST res(*u);
	res.madd=0,res.mset=tinf;
	return res;
}

// assumes no lazy on both
ST uni(ST a,ST b){
	ST res;
	res.val=max(a.val,b.val);
	res.sz=a.sz+b.sz;
	return res;
}

void push(ptr u){
	if(u->lb+1<u->rb){
		if(!u->c[0]){
			B m=(u->lb+u->rb)/2;
			u->c[0]=new ST(0,u->lb,m);
			u->c[1]=new ST(0,m,u->rb);
		}
		for(ptr c:u->c){
			if(u->mset!=tinf)setu(c,u->mset,u->lb,u->rb);
			else add(c,u->madd,u->lb,u->rb);
		}
	}
	*u=real(u);
}

// assumes no lazy on u
ptr pull(ptr u){
	if(!u)return u;
	auto a=real(u->c[0]),b=real(u->c[1]);
	u->val=max(a.val,b.val);
	u->sz=a.sz+b.sz;
	return u;
}

ST query(ptr u,B l,B r){
	if(!u||r<=u->lb||u->rb<=l)return ST();
	if(l<=u->lb&&u->rb<=r)return real(u);
	push(u);
	return uni(query(u->c[0],l,r),query(u->c[1],l,r));
}

void add(ptr u,T x,B l,B r){
	if(!u||r<=u->lb||u->rb<=l)return;
	if(l<=u->lb&&u->rb<=r){
		if(u->mset!=tinf)u->mset+=x;
		else u->madd+=x;
		u->val+=x;
	}else{
		push(u);
		for(ptr c:u->c)add(c,x,l,r);
		pull(u);
	}
}

void setu(ptr u,T x,B l,B r){
	if(!u||r<=u->lb||u->rb<=l)return;
	if(l<=u->lb&&u->rb<=r)u->madd=0,u->mset=u->val=x;
	else{
		push(u);
		for(ptr c:u->c)setu(c,x,l,r);
		pull(u);
	}
}

// you can merge & split segtrees in amortized log(n)
// it's useful: https://codeforces.com/blog/entry/49446
// PAY ATTENTION TO SZ, so sz==1 only at leafs, 0 at internal nodes
// (=> what are internal nodes when using lazy? etc...)

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
