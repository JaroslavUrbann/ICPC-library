// don't yeet the treap on the heap
// ~ 470 MB, change accordingly
static char buf[450<<20];
void*operator new(size_t s){
	static size_t i=sizeof(buf);
	assert(s<i);
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

mt19937 gen(chrono::steady_clock::now().time_since_epoch().count());

struct Treap;
typedef P<Treap> ptr;

struct Treap {
	int pri=gen(),sz=0;
	array<ptr,2>c;
	ll self=0,lz=0,sub=0;
	bool flip=false;
	Treap()=default;
	Treap(ll self):sz(1),self(self),sub(self){}
};

// returns the node with applied lazy
// default treap constructor should return a default node
Treap real(ptr u){
	if(!u)return Treap();
	Treap res(*u);
	res.sub+=res.lz*res.sz;
	res.lz=0;
	if(res.flip)swap(res.c[0],res.c[1]),res.flip=0;
	return res;
}

// recalcs values from children, no nodes here have lazy
ptr pull(ptr u){
	if(!u)return 0;
	auto a=real(u->c[0]),b=real(u->c[1]);
	u->sz=1+a.sz+b.sz;
	u->sub=u->self+a.sub+b.sub;
	return u;
}

// just pushes lazy, recalc is done by real()
void push(ptr u){
	if(!u)return;
	for(auto v:u->c)if(v){ // think before overwriting
		v->lz+=u->lz;
		v->flip^=u->flip;
	}
	*u=real(u);
}

ptr merge(ptr a,ptr b){
	push(a),push(b);
	if(!a)return b;
	if(!b)return a;
	if(a->pri < b->pri){
		a->c[1]=merge(a->c[1],b);
		return pull(a);
	}
	b->c[0]=merge(a,b->c[0]);
	return pull(b);
}

int gsz(ptr u){return u?u->sz:0;}
// k = how many nodes to skip
pair<ptr,ptr>split(ptr u,int k) {
	if(!u)return {};
	push(u);
	if(gsz(u->c[0])>=k){
		auto res=split(u->c[0],k);
		u->c[0]=res.second;
		return {res.first,pull(u)};
	}
	auto res=split(u->c[1],k-gsz(u->c[0])-1);
	u->c[1]=res.first;
	return {pull(u),res.second};
}

// 0=first, inserts v to kth position
ptr insertkth(ptr u,ptr v,int k){
	auto a=split(u,k);
	return merge(a.first,merge(v,a.second));
}

// 0=first, inclusive, exclusive
ptr erase(ptr u,int l,int r){
	auto a=split(u,l),b=split(a.second,r-l);
	return merge(a.first,b.second);
}

// 0=first, inclusive, exclusive
ptr update(ptr u,int l,int r,ll d) {
	auto a=split(u,l),b=split(a.second,r-l);
	b.first->lz+=d;
	return merge(a.first,merge(b.first,b.second));
}

// 0=first, inclusive, exclusive
ptr query(ptr u,int l,int r,ll &res) {
	auto a=split(u,l),b=split(a.second,r-l);
	res=b.first->sub;
	return merge(a.first,merge(b.first,b.second));
}

// cyclical shift to the right k=0 =>same
ptr shift(ptr u,int k){
	auto a=split(u,gsz(u)-k);
	return merge(a.second,a.first);
}

ptr reverse(ptr u,int l,int r){
	auto a=split(u,l),b=split(a.second,r-l);
	b.first->flip=1;
	return merge(a.first,merge(b.first,b.second));
}

// returns index of the first value that is not less than val
// (only if data is sorted)
int lower_bound(ptr u,ll val,int k=0){
	if(!u)return k;
	push(u);
	if(u->self<val)return lower_bound(u->c[1],val,k+1+gsz(u->c[0]));
	return lower_bound(u->c[0],val,k);
}

void inorder(ptr u){
	if(!u)return;
	push(u);
	inorder(u->c[0]);
	cout<<(u->self)<<" ";
	inorder(u->c[1]);
}
