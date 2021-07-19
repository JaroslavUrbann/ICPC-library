// log(n) find
struct RollBackDSU{
	vector<int>e; // parent or -size if self
	vector<pair<int,int>>st;
	int c;
	RollBackDSU(int n):e(n,-1),c(n){}
	int size(int u){return -e[find(u)];}
	int find(int u){return e[u]<0?u:find(e[u]);}
	int time(){return st.size();}
	void uni(int u,int v){
		u=find(u),v=find(v);
		if(u==v)return;
		if(e[u]<e[v])swap(u,v);
		st.push_back({u,e[u]});
		st.push_back({v,e[v]});
		e[v]+=e[u];e[u]=v;--c;
	}
	void rollback(int t){
		for(int i=time();i-->t;)e[st[i].first]=st[i].second;
		c+=(time()-t)/2;
		st.resize(t);
	}
};
