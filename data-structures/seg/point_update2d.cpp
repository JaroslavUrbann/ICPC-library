// can't do range update in a good complexity afaik,
// very slow, think about using fenwick
// not compiled
template<class O>
struct ST2D{
	using T=typename O::T;
	vector<ST>t;
	ST2D(int n,int m):n(1<<int(log2(n))),m(1<<int(log2(m))),t(2*n,ST(vector<T>(m,O::D))){}
	T query(int l1,int r1,int l2,int r2){
		T res=O::D;
		for(l1+=N,r1+=N;l1<r1;l1/=2,r1/=2){
			if(l1&1)res=O::uni(res,t[l1++].query(l2,r2));
			if(r1&1)res=O::uni(res,t[--r1].query(l2,r2));
		}
		return res;
	}
	void update(int x,int y,T v){
		for(t[x+=N].update(y,v);x/=2;){
			auto res=O::uni(t[2*x].query(y,y+1),t[2*x+1].query(y,y+1));
			// you should set t[x][y] to be equal to res, depending on your operation, for set:
			// t[x].update(y,res);
			// for add it's probably
			// t[x].update(y,res-t[x].query(y,y+1));
			assert(0);
		}
	}
};

