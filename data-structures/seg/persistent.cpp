// not really tested, heap allocation might be slow
template<class T>
struct PST{
	struct Node{
		Node*l=0,*r=0;
		T data=T::D,lazy=T::DL;
		Node(T data=T::D):data(data){};
	};
	Node*dup(Node*u){return add(*u);}
	void applylazy(Node*u,int lb,int rb){
		if(u->l)u->l=dup(u->l);
		if(u->r)u->r=dup(u->r);
		if(u->lazy!=T::DL){
			u->data=T::rv(u->data,u->lazy,lb,rb);
			if(u->l)T::upd(u->l->lazy,u->lazy);
			if(u->r)T::upd(u->r->lazy,u->lazy);
			u->lazy=T::DL;
		}
	}
	int n;
	vector<Node*>roots;
	// hopefully isn't too slow, otherwise create a global array and typedef T
	Node*add(Node u){return new Node(u);}
	PST(vector<T>a):n(a.size()){roots.push_back(build(a,0,n));}
	Node*build(vector<T>&a,int lb,int rb){
		if(lb>=n)return 0;
		Node*u=add(Node(a[lb]));
		if(lb+1<rb){
			int m=(lb+rb)/2;
			u->l=build(a,lb,m);
			u->r=build(a,m,rb);
			u->data=T::uni(u->l->data,u->r->data);
		}
		return u;
	}
	T query(int l,int r,int t=0){return query(l,r,0,n,roots[t]=add(*roots[t]));}
	T query(int l,int r,int lb,int rb,Node*u){
		if(!u||r<=lb||rb<=l)return T::D;
		if(l<=lb&&rb<=r)return T::rv(u->data,u->lazy,lb,rb);
		applylazy(u,lb,rb);
		int m=(lb+rb)/2;
		return T::uni(query(l,r,lb,m,u->l),query(l,r,m,rb,u->r));
	}
	// gives id of the new branch, t = branch to be updated
	int update(int l,int r,T x,int t=-1){
		roots.push_back(add(*roots[~t?t:roots.size()-1]));
		update(l,r,0,n,roots.back(),x);
		return roots.size()-1;
	}
	T update(int l,int r,int lb,int rb,Node*u,T x){
		if(!u||r<=lb||rb<=l)return u?T::rv(u->data,u->lazy,lb,rb):T::D;
		if(l<=lb&&rb<=r)return T::rv(u->data,T::upd(u->lazy,x),lb,rb);
		applylazy(u,lb,rb);
		int m=(lb+rb)/2;
		return u->data=T::uni(update(l,r,lb,m,u->l,x),update(l,r,m,rb,u->r,x));
	}
};
