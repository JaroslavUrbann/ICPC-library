// not really tested

// CHANGE ACCORDINGLY
static char buf[650<<20];
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
 
struct Node;
typedef P<Node> ptr;
 
Node rv(ptr u,int lb,int rb);
 
// max, set
struct Node{
	typedef pair<int,int> T;
	static constexpr T D=make_pair(-1,-1),DL=D;
	ptr l=0,r=0;
	T mx=D,lz=DL;
	ptr dup(){return P<Node>(new Node(*this));}
	void push(int lb,int rb){
		if(l)l=l->dup();
		if(r)r=r->dup();
		if(lz!=DL){
			if(l)l->upd(*this);
			if(r)l->upd(*this);
			*this=rv(this,lb,rb);
		}
	}
	// assumes no lazy on either
	Node uni(Node u,Node v){
		mx=max(u.mx,v.mx);
		return *this;
	}
	void upd(Node u){lz=u.lz;}
};
 
Node rv(ptr u,int lb,int rb){
	if(!u)return Node();
	auto tmp=*u;
	if(tmp.lz!=Node::DL){
		tmp.mx=tmp.lz;
		tmp.lz=Node::DL;
	}
	return tmp;
}
 
 
struct PST{
	int n;
	vector<ptr>roots;
	PST(vector<Node>a):n(a.size()){roots.push_back(build(a,0,n));}
	ptr build(vector<Node>&a,int lb,int rb){
		if(lb>=n)return 0;
		ptr u=Node(a[lb]).dup();
		if(lb+1<rb){
			int m=(lb+rb)/2;
			u->l=build(a,lb,m);
			u->r=build(a,m,rb);
			u->uni(rv(u->l,lb,rb),rv(u->r,lb,rb));
		}
		return u;
	}
	Node query(int l,int r,int t=0){return query(l,r,0,n,roots[t]);}
	Node query(int l,int r,int lb,int rb,ptr u){
		if(!u||r<=lb||rb<=l)return Node();
		if(l<=lb&&rb<=r)return rv(u,lb,rb);
		u->push(lb,rb);
		int m=(lb+rb)/2;
		return Node().uni(query(l,r,lb,m,u->l),query(l,r,m,rb,u->r));
	}
	// gives id of the new branch, t = branch to be updated
	int update(int l,int r,Node x,int t=-1){
		roots.push_back(roots[~t?t:roots.size()-1]->dup());
		update(l,r,0,n,roots.back(),x);
		return roots.size()-1;
	}
	Node update(int l,int r,int lb,int rb,ptr u,Node x){
		if(!u||r<=lb||rb<=l)return rv(u,lb,rb);
		if(l<=lb&&rb<=r){u->upd(x);return rv(u,lb,rb);}
		u->push(lb,rb);
		int m=(lb+rb)/2;
		return u->uni(update(l,r,lb,m,u->l,x),update(l,r,m,rb,u->r,x));
	}
};
