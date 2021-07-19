// proper dsu
// random dsu is about 8s, size dsu is about 2.6s (https://codeforces.com/blog/entry/47402)
// I'm probably going to use the 2 line dsu most of the time anyway though
// not tested
struct DSU{
	vector<int>p,size;
	DSU(int n):p(n),size(n){iota(p.begin(),p.end(),0);}
	int find(int u){return p[u]==u?u:p[u]=find(p[u]);}
	bool same(int u,int v){return find(u)==find(v);}
//	void uni(int u,int v){p[find(u)]=find(v);}
	void uni(int u,int v){
		u=find(u);v=find(v);
		if(size[u]>size[v])swap(u,v);
		p[u]=p[v];
		if(u!=v)size[v]+=size[u];
	}
};
