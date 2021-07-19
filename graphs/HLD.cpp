// currently doing:
// query: max
// update: set
// you have to set values to nodes/edges manually
// seg trees go from top to bottom, always following the first child
template<bool E,typename T>
struct HLD{
	int n,tim=0;
	vector<vector<int>>g;
	// parent, size of subtree, depth, position of u in memory, root of segtree
	vector<int>p,sz,d,pos,rt;
	SegmentTree<T>st;
	HLD(vector<vector<int>>g):n(g.size()),g(g),p(n),sz(n,1),d(n),pos(n),rt(n),
														st(vector<T>(n)){dfsz(0);dfshld(0);} // c?
	void dfsz(int u){
		g[u].erase(remove(g[u].begin(),g[u].end(),p[u]),g[u].end());
		for(auto&v:g[u]){
			p[v]=u,d[v]=d[u]+1;
			dfsz(v);
			sz[u]+=sz[v];
			if(sz[v]>sz[g[u][0]])swap(v,g[u][0]);
		}
	}
	void dfshld(int u){
		pos[u]=tim++;
		for(auto v:g[u]){
			rt[v]=(v==g[u][0]?rt[u]:v);
			dfshld(v);
		}
	}
	template<class X>
	void walk(int u,int v,X op){
		for(;rt[u]!=rt[v];u=p[rt[u]]){
			if(d[rt[u]]<d[rt[v]])swap(u,v);
			op(pos[rt[u]],pos[u]+1);
		}
		if(d[u]<d[v])swap(u,v);
		op(pos[v]+E,pos[u]+1);
	}
	void update(int u,int v,T val){walk(u,v,[&](int l,int r){st.update(l,r,val);});}
	T query(int u,int v){ // c
		T res=INT_MIN;
		walk(u,v,[&](int l,int r){res=max(res,st.query(l,r,res));});
		return res;
	}
	T querytree(int u){return st.query(pos[u]+E,pos[u]+sz[u]+1);}
};

