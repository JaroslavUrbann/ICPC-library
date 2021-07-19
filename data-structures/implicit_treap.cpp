// treap is useless for competitive programming
// implicit treap is a segment tree but you can swap/reverse segments
// you can also insert/erase kth element

// DON'T FORGET TO MODIFY GRES() - calculating result without propagating lazy
#define NEUTRAL_DIFF 0 // the values will never be this extreme
#define NEUTRAL_SAME 0 // I will never update the tree with this
#define COMBINE_DIFF(a, b) ((a)+(b)) // combining 2 different nodes (a is data)
#define COMBINE_SAME(a, b) ((a)+(b)) // comb. 2 of the same node (b is the newer)

struct Treap;
typedef Treap* pTreap;
typedef int T;

struct Treap {
	int prior=rand(),sz=1;
	T data=NEUTRAL_DIFF,lazy=NEUTRAL_SAME,res=NEUTRAL_DIFF;
	bool rev=false;
	pTreap l=0,r=0;
	Treap(ll data=NEUTRAL_DIFF):data(data),res(data){}
	void recalc();
};
inline int gsz(pTreap u){return u?u->sz:0;}

// you can (and have to) use lazy, size, previous res, data in calculation of res
// you can assume they are all correct
// thres is different from data, If I want to know max, I ask res, -||- k-th element: data
// currently works with q:sum,u:add
T gres(pTreap u){return u?(u->lazy==NEUTRAL_SAME?u->res:u->res+gsz(u)*u->lazy):NEUTRAL_DIFF;}

// needed because of merging/splitting..
// assumes lazy is already propagated
// assumes kids are recalculated
void Treap::recalc(){
	sz=1+gsz(l)+gsz(r);
	res=COMBINE_DIFF(data,COMBINE_DIFF(gres(l),gres(r)));
}

void applylazy(pTreap u){
	if(u->lazy!=NEUTRAL_SAME){
		if(u->l)u->l->lazy=COMBINE_SAME(u->l->lazy,u->lazy);
		if(u->r)u->r->lazy=COMBINE_SAME(u->r->lazy,u->lazy);
		u->data=COMBINE_SAME(u->data,u->lazy);
		u->lazy=NEUTRAL_SAME;
		u->recalc();
	}
	if(u->rev){
		swap(u->l,u->r);
		if(u->l)u->l->rev^=1;
		if(u->r)u->r->rev^=1;
		u->rev=0;
	}
}

pTreap merge(pTreap a,pTreap b){
	if(!a)return b;
	if(!b)return a;
	applylazy(a);applylazy(b);
	if(a->prior < b->prior){
		a->r=merge(a->r,b);
		a->recalc();
		return a;
	}
	else{
		b->l=merge(a,b->l);
		b->recalc();
		return b;
	}
}

// k = how many nodes to skip
pair<pTreap,pTreap>split(pTreap u,int k) {
	if(!u)return {};
	applylazy(u);
	if(gsz(u->l)>=k){
		auto res=split(u->l,k);
		u->l=res.second;
		u->recalc();
		return {res.first,u};
	}else{
		auto res=split(u->r,k-gsz(u->l)-1);
		u->r=res.first;
		u->recalc();
		return {u,res.second};
	}
}

// 0=first, inserts v to kth position
pTreap insertkth(pTreap u,pTreap v,int k){
	auto a=split(u,k);
	return merge(a.first,merge(v,a.second));
}

// 0=first, inclusive, inclusive
pTreap erase(pTreap u,int l,int r){
	auto a=split(u,l),b=split(a.second,r-l+1);
	return merge(a.first,b.second);
}

// 0=first, inclusive, inclusive
pTreap update(pTreap u,int l,int r,T d) {
	auto a=split(u,l),b=split(a.second,r-l+1);
	b.first->lazy=COMBINE_SAME(b.first->lazy,d);
	return merge(a.first,merge(b.first,b.second));
}

// 0=first, inclusive, inclusive
pTreap query(pTreap u,int l,int r,T &res) {
	auto a=split(u,l),b=split(a.second,r-l+1);
	res=gres(b.first);
	return merge(a.first,merge(b.first,b.second));
}

// cyclical shift to the right k=0 =>same
pTreap shift(pTreap u,int k){
	auto a=split(u,gsz(u)-k);
	return merge(a.second,a.first);
}

pTreap reverse(pTreap u,int l,int r){
	auto a=split(u,l),b=split(a.second,r-l+1);
	b.first->rev=1;
	return merge(a.first,merge(b.first,b.second));
}

// returns index of the first value that is not less than val
// (only if data is sorted)
int lower_bound(pTreap u,T val,int k=0){
	if(!u)return k;
	applylazy(u);
	if(u->data<val)return lower_bound(u->r,val,k+1+gsz(u->l));
	return lower_bound(u->l,val,k);
}

// moves segment <l,r) to the last positions
pTreap moveToBack(pTreap u,int l,int r){
	auto a=split(u,l);
	auto b=split(a.second,r-l);
	return merge(a.first,merge(b.second,b.first));
}

void inorder(pTreap u){
	if(!u)return;
	applylazy(u);
	inorder(u->l);
	cout<<(u->data)<<" ";
	inorder(u->r);
}

